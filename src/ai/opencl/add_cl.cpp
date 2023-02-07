//
// Implement Add Operator with OpenCL
// Created by zgd on 2/5/23.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include "CL/cl2.hpp"
#include "ai/utils/TimeElapse.h"

using namespace std;
using namespace cppkit::ai::utils;

std::string FloatVectorToString(const std::vector<float> &data) {
  stringstream ss;
  ss << "[ ";
  for (int i = 0; i < data.size(); i++) {
    ss << data[i] << (i != data.size() - 1 ? ", ": "");
  }
  ss << " ]";
  return ss.str();
}

constexpr int ARRAY_SIZE = 1000000;

int main() {
  //  vector<float> a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
//  vector<float> b_data = {1.5, 2.5, 3.5, 4.5, 5.5};
//  vector<float> out_data(a_data.size(), 0.0);

  vector<float> a_data(ARRAY_SIZE, 2.0);
  vector<float> b_data(ARRAY_SIZE, 3.14);;
  vector<float> out_data(a_data.size(), 0.0);

  TimeElapse time_elapse;

  cout << "=== Step 1: Query available platforms and devices..." << endl;

  // Query available platforms
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);
  cout << "--- Number of platforms: " << platforms.size() << endl;
  cout << "--- platform list: [" << endl;
  for (const auto &platform: platforms) {
    cout << "--- * " << platform.getInfo<CL_PLATFORM_NAME>()<< endl;
  }
  cout << "--- ]" << endl;

  // Create context of first platform with GPU type devices
  cl_context_properties context_properties[] = {
      CL_CONTEXT_PLATFORM,
      (cl_context_properties)(platforms[0])(),
      0
  };
  cl::Context context(CL_DEVICE_TYPE_GPU, context_properties);

  // Query devices of context
  auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
  cout << "--- Number of devices: " << devices.size() << endl;
  cout << "--- Device list: [" << endl;
  for (const auto &device: devices) {
    cout << "--- * " << device.getInfo<CL_DEVICE_NAME>()<< endl;
  }
  cout << "--- ]" << endl;

  // Create command queue on first device in context.
  cl::CommandQueue command_queue(context, devices[0]);

  cout << "--- " << time_elapse.ToString() << endl;
  cout << endl;

  cout << "=== Step 2: Build program..." << endl;
  const std::string add_source_code = R"(
    __kernel void add(__global const float *in_0, __global const float *in_1, __global float *out_0)
    {
      int i = get_global_id(0);
      out_0[i] = in_0[i] + in_1[i];
    }
  )";

  // Create program adn kernel
  cl::Program program(context, {add_source_code});
  auto error = program.build(devices);
  if (error != CL_SUCCESS) {
    cout << "--- Failed to build program." << endl;
    auto log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]);
    cout << log << endl;
    cout << "--- Abort." << endl;
    return -1;
  }
  cout << "--- Build program success." << endl;
  cl::Kernel kernel(program, "add");

  cout << "--- " << time_elapse.ToString() << endl;
  cout << endl;

  cout << "=== Step 3: Prepare memory object and run kernel..." << endl;
  // Create memory objects
  cl::Buffer a_buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                      a_data.size() * sizeof(float), reinterpret_cast<void *>(a_data.data()));
  cl::Buffer b_buffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                      a_data.size() * sizeof(float), reinterpret_cast<void *>(b_data.data()));

  cl::Buffer out_buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR,
                        out_data.size() * sizeof(float), reinterpret_cast<void *>(out_data.data()));

  cout << "--- Done memory preparation. " << time_elapse.ToString() << endl;

  // Execute kernel and get result
  kernel.setArg(0, a_buffer);
  kernel.setArg(1, b_buffer);
  kernel.setArg(2, out_buffer);

  cl::NDRange global = {out_data.size()};
  command_queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, cl::NullRange);
  command_queue.finish();

  float *output = (float *)command_queue.enqueueMapBuffer(out_buffer, CL_TRUE,
                                                            CL_MAP_READ, 0,
                                                            sizeof(float) * out_data.size());

  std::vector<float> tmp(output, output + out_data.size());

  cout << "--- Done kernel computation. " << time_elapse.ToString() << endl;
  cout << endl;

//  cout << "in_0 : " << FloatVectorToString(a_data) << endl;
//  cout << "in_1 : " << FloatVectorToString(b_data) << endl;
//  cout << "out_0: " << FloatVectorToString(tmp) << endl;

  command_queue.enqueueUnmapMemObject(out_buffer, output);
}

