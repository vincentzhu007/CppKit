//
// Created by zgd on 2024/11/20.
//

#include <iostream>
#include <vector>
#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/opencl.hpp>

// Compute c = a + b.
static std::string source = R"(
kernel void add(
  int n,
  global const float *a,
  global const float *b,
  global float *c) {
  size_t i = get_global_id(0);
  if (i >= n) {
    return;
  }
  c[i] = a[i] + b[i];
}
)";

int main() {
  const size_t N = 1 << 20;

  try {
    // Get list of OpenCL platforms.
    std::vector<cl::Platform> platform;
    cl::Platform::get(&platform);

    if (platform.empty()) {
      std::cerr << "OpenCL platforms not found." << std::endl;
      return 1;
    }

    // Get first available GPU device which supports double precision.
    cl::Context context;
    std::vector<cl::Device> device;
    for(auto p = platform.begin(); device.empty() && p != platform.end(); p++) {
      std::vector<cl::Device> pldev;

      try {
        p->getDevices(CL_DEVICE_TYPE_GPU, &pldev);

        for(auto d = pldev.begin(); device.empty() && d != pldev.end(); d++) {
          if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;
          device.push_back(*d);
          context = cl::Context(device);
        }
      } catch(...) {
        device.clear();
      }
    }

    if (device.empty()) {
      std::cerr << "GPUs with double precision not found." << std::endl;
      return 1;
    }

    std::cout << device[0].getInfo<CL_DEVICE_NAME>() << std::endl;

    // Create command queue.
    cl::CommandQueue queue(context, device[0]);

    // Compile OpenCL program for found device.
    cl::Program program(context, cl::Program::Sources(
        1, {std::string(source)})
    );

    try {
      program.build(device);
    } catch (const cl::Error&) {
      std::cerr
          << "OpenCL compilation error" << std::endl
          << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device[0])
          << std::endl;
      return 1;
    }

    cl::Kernel add(program, "add");

    // Prepare input data.
    std::vector<float> a(N, 1);
    std::vector<float> b(N, 2);
    std::vector<float> c(N);

    // Allocate device buffers and transfer input data to device.
    cl::Buffer A(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                 a.size() * sizeof(float), a.data());

    cl::Buffer B(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                 b.size() * sizeof(float), b.data());

    cl::Buffer C(context, CL_MEM_READ_WRITE,
                 c.size() * sizeof(float));

    // Set kernel parameters.
    add.setArg(0, static_cast<int>(N));
    add.setArg(1, A);
    add.setArg(2, B);
    add.setArg(3, C);

    // Launch kernel on the compute device.
    queue.enqueueNDRangeKernel(add, cl::NullRange, N, cl::NullRange);

    // Get result back to host.
    queue.enqueueReadBuffer(C, CL_TRUE, 0, c.size() * sizeof(float), c.data());

    // Should get '3' here.
    std::cout << c[42] << std::endl;
  } catch (const cl::Error &err) {
    std::cerr
        << "OpenCL error: "
        << err.what() << "(" << err.err() << ")"
        << std::endl;
    return 1;
  }
}