//
// Created by zgd on 2023/4/22.
//

#include <iostream>
#include <gtest/gtest.h>
#include <filesystem>
#include "linux/temp_file.h"

using cppkit::linux_demo::TempFile;

const std::string kTestDir = "temp_file_test_dir";

class TempFileTest : public ::testing::Test {
 public:
  static void SetUpTestCase() {
    std::cout << "Set up TempFile test case." << std::endl;
    std::filesystem::remove_all(kTestDir);
    std::filesystem::create_directories(kTestDir);
  }

  static void TearDownTestCase() {
    std::cout << "Tear down TempFile test case." << std::endl;
    std::filesystem::remove_all(kTestDir);
  }
};

TEST_F(TempFileTest, NewInstance) {
  TempFile a_file;
  ASSERT_TRUE(a_file.is_good());

  std::cout << "temp file: " << a_file.file();
  ASSERT_TRUE(!a_file.file().empty());
}

TEST_F(TempFileTest, NewInstanceWithName) {
  std::string name = "temp_file_test";

  TempFile a_file(name);
  ASSERT_TRUE(a_file.is_good());

  std::cout << "temp file: " << a_file.file();
  std::string file_path = a_file.file();
  ASSERT_TRUE(file_path.find(name) != std::string::npos);
}

TEST_F(TempFileTest, NewInstanceWithNameAndDir) {
  std::string name = "temp_file_test";

  TempFile a_file(kTestDir, name);
  ASSERT_TRUE(a_file.is_good());

  std::cout << "temp file: " << a_file.file();
  std::string file_path = a_file.file();
  ASSERT_TRUE(file_path.find(kTestDir + "/" + name) != std::string::npos);
}