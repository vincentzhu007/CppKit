//
// Created by zgd on 2023/4/22.
//

#include "linux/temp_file.h"
#include "linux/mmap_buffer.h"
#include "linux/temp_file.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include "gtest/gtest.h"

using cppkit::linux_demo::TempFile;
using cppkit::linux_demo::MmapBuffer;

constexpr size_t kBlockSize = 1024 * 1024; // 1MB per block
constexpr size_t kFileSize_1MB = kBlockSize;
constexpr size_t kFileSize_1GB = kBlockSize * 1024;

namespace {
bool FillFile(const std::string &file, size_t size) {
  std::ofstream ofs(file);
  if (!ofs.is_open()) {
    return false;
  }
  std::vector<char> block_data(kBlockSize, 'a');
  size_t num_block = size / kBlockSize;
  size_t byte_remained = size - kBlockSize * num_block;
  for (size_t i = 0; i < num_block; i++) {
    ofs.write(block_data.data(), block_data.size());
  }
  ofs.write(block_data.data(), byte_remained);
  return true;
}
}

class MmapBufferTest : public ::testing::Test {
 public:
  static void BuildTempFile(size_t size, std::unique_ptr<TempFile> &result) {
    TempFile *a_file = new TempFile;
    ASSERT_TRUE(a_file != nullptr);
    ASSERT_TRUE(a_file->is_good());
    ASSERT_TRUE(FillFile(a_file->file(), size));
    result.reset(a_file);
  }
};

TEST_F(MmapBufferTest, NewInstance) {
  std::unique_ptr<TempFile> a_file;
  BuildTempFile(kFileSize_1MB, a_file);
  std::string file = a_file->file();

  MmapBuffer a_buffer(file);
  ASSERT_TRUE(a_buffer.is_good());
  ASSERT_EQ(a_buffer.file(), file);
  ASSERT_NE(a_buffer.address(), nullptr);
  ASSERT_EQ(a_buffer.size(), kFileSize_1MB);
}

TEST_F(MmapBufferTest, NewInstanceWithEmptyFile) {
  std::unique_ptr<TempFile> a_file;
  BuildTempFile(0, a_file);
  std::string file = a_file->file();

  MmapBuffer a_buffer(file);
  ASSERT_FALSE(a_buffer.is_good());
}

TEST_F(MmapBufferTest, NewInstanceWithNotExistFile) {
  std::string file = "./not_exist_file";

  MmapBuffer a_buffer(file);
  ASSERT_FALSE(a_buffer.is_good());
}


