//
// Created by Vincent Zhu on 2023/4/19.
//

#include <iostream>
#include <string>
#include <random>
#include "tensor_with_mmap_generated.h"

using namespace std;
using namespace demo;

constexpr size_t kNumTensor = 100;
constexpr size_t kRow = 1024;
constexpr size_t kCol = 100;

void GenerateRandomBuffer(void *buffer, size_t size) {
  uint8_t *byte_buffer = reinterpret_cast<uint8_t *>(buffer);
  for (size_t i = 0; i < size; i++) {
    byte_buffer[i] = rand() % 256;
  }
}

void WriteModelToFile(const std::string &path) {
  // 创建flatbuffer的建造器，设置初始大小为1024，后续自动按需扩容
  flatbuffers::FlatBufferBuilder builder(1024);

  std::vector<flatbuffers::Offset<Tensor>> tensors;
  std::vector<flatbuffers::Offset<Buffer>> buffers;
  for (int i = 0; i < kNumTensor; i++) {
    int shape_value[] = {kRow, kCol};
    auto shape = builder.CreateVector(shape_value, 2);
    auto tensor = CreateTensor(builder, shape, i);
    tensors.push_back(tensor);

    uint8_t * data_buffer = new uint8_t[kRow * kCol];
    GenerateRandomBuffer(data_buffer, kRow * kCol);
    auto data = builder.CreateVector(data_buffer, kRow * kCol);
    auto buffer = CreateBuffer(builder, data);
    buffers.push_back(buffer);
    delete[] data_buffer;
  }

  auto model = CreateModel(builder, builder.CreateVector(tensors), builder.CreateVector(buffers));
  builder.Finish(model);

  auto file_buffer = builder.GetBufferPointer();
  auto file_size = builder.GetSize();

  printf("file_buffer: %p\n", file_buffer);
  printf("file_size: %d\n", file_size);

  FILE *fp = fopen(path.c_str(), "wb");
  auto cnt = fwrite(file_buffer, file_size, 1, fp);
  if (cnt != 1) {
    fprintf(stderr, "Write model file failed, cnt: %d, error: %d\n", cnt, ferror(fp));
    fclose(fp);
    return;
  }
  fclose(fp);
  fprintf(stdout, "Save model ok!\n");
}

int main(int argc, const char *argv[]) {
  std::string path = "./demo.model";
  WriteModelToFile(path);
}