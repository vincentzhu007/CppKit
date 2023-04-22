//
// Created by Vincent Zhu on 2023/4/19.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "tensor_with_mmap_generated.h"
#include "ai/utils/TimeElapse.h"

using namespace std;
using namespace demo;
using cppkit::ai::utils::TimeElapse;

class MMapBuffer {
 public:
  MMapBuffer(const std::string &path) : path_(path) {
    fd_ = open(path.c_str(), O_RDONLY);
    if (fd_ < 0) {
      fprintf(stderr, "open file failed, %s\n", strerror(errno));
      return;
    }
    size_ = lseek(fd_, 0, SEEK_END);
    (void) lseek(fd_, 0, SEEK_SET);

    addr_ = mmap(NULL, size_, PROT_READ, MAP_SHARED, fd_, 0);
    if (addr_ == NULL) {
      fprintf(stderr, "mmap file failed, %s\n", strerror(errno));
      return;
    }
    is_valid_ = true;
  }

  ~MMapBuffer() {
    if (!is_valid_) {
      return;
    }
    (void)munmap(addr_, size_);
    close(fd_);
  }

  void PrintStat() {
    printf("--- mmap buffer stat ---\n");
    printf("* file: %s\n", path_.c_str());
    printf("* fd_: %d\n", fd_);
    printf("* addr_: %p\n", addr_);
    printf("* size_: %d\n", size_);
  }

  void *addr() const { return addr_; }
  int size() const { return size_; }

 private:
  bool is_valid_ = false;
  std::string path_;
  int fd_;
  void *addr_;
  int size_;
};

class FileBuffer {
 public:
  FileBuffer(const std::string &path) :path_(path) {
    fd_ = open(path.c_str(), O_RDONLY);
    if (fd_ < 0) {
      fprintf(stderr, "open file failed, %s\n", strerror(errno));
      return;
    }
    size_ = lseek(fd_, 0, SEEK_END);
    (void) lseek(fd_, 0, SEEK_SET);

    addr_ = malloc(size_);
    if (addr_ == NULL) {
      fprintf(stderr, "malloc file buffer failed, %s\n", strerror(errno));
      return;
    }
    auto ret = read(fd_, addr_, size_);
    if (ret == -1) {
      fprintf(stderr, "read file buffer failed, %s\n", strerror(errno));
      return;
    }
    is_valid_ = true;
  }

  ~FileBuffer() {
    if (!is_valid_) {
      return;
    }
    (void)free(addr_);
    close(fd_);
  }

  void PrintStat() {
    printf("--- file buffer stat ---\n");
    printf("* file: %s\n", path_.c_str());
    printf("* fd_: %d\n", fd_);
    printf("* addr_: %p\n", addr_);
    printf("* size_: %d\n", size_);
  }

  void *addr() const { return addr_; }
  int size() const { return size_; }

 private:
  bool is_valid_ = false;
  std::string path_;
  int fd_;
  void *addr_;
  int size_;
};

constexpr size_t kRow = 1024;
constexpr size_t kCol = 100;

void GenerateRandomBuffer(void *buffer, size_t size) {
  uint8_t *byte_buffer = reinterpret_cast<uint8_t *>(buffer);
  for (size_t i = 0; i < size; i++) {
    byte_buffer[i] = rand() % 256;
  }
}

void ArithmeticMul(uint8_t *in_0, uint8_t *in_1, uint8_t *out, size_t size) {
  for (size_t i = 0; i < size; i++) {
    out[i] = in_0[i] * in_1[i];
  }
}

void RunTensors(void *model_buffer) {
  auto model = GetModel(model_buffer);
  auto buffers = model->buffers();

  std::vector<uint8_t *> tensor_data_array(buffers->size(), NULL);
  for (size_t i = 0; i < buffers->size(); i++) {
    tensor_data_array[i] = (uint8_t *) buffers[i].data();
  }

  uint8_t *input_tensor = new uint8_t[kRow * kCol];
  uint8_t *output_tensor = new uint8_t[kRow * kCol];
  GenerateRandomBuffer(input_tensor, kRow * kCol);

  uint8_t *tmp_tensor = input_tensor;
  for (size_t i = 0; i < tensor_data_array.size(); i++) {
    ArithmeticMul(tmp_tensor, tensor_data_array[i], output_tensor, kRow * kCol);
    tmp_tensor = output_tensor;
  }
  delete[] input_tensor;
  delete[] output_tensor;
}

int main() {
  {
    TimeElapse te;
    // 加载模型
    MMapBuffer model("./demo.model");
    model.PrintStat();
    printf("Loaded model elapsed: %ld us\n", te.ElapsedInUs());

    // 执行Tensor计算
    RunTensors(model.addr());
    printf("Run tensors elapsed: %ld us\n", te.ElapsedInUs());
  }

  {
    TimeElapse te;
    // 加载模型
    FileBuffer model("./demo_dup.model");
    model.PrintStat();
    printf("Loaded model elapsed: %ld us\n", te.ElapsedInUs());

    // 执行Tensor计算
    RunTensors(model.addr());
    printf("Run tensors elapsed: %ld us\n", te.ElapsedInUs());
  }

}