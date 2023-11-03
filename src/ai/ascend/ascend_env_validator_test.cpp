#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ascend_env_validator.h"

using testing::Return;

class AscendEnvValidatorTest : public ::testing::Test {
 public:
  static void SetUpTestcases()
  {
  }
  static void TearDownTestcases()
  {
  }
  void SetUp()
  {
  }
  void TearDown()
  {
  }
};

TEST_F(AscendEnvValidatorTest, Hello) {
  auto validator = AscendEnvValidator();
  ASSERT_TRUE(validator.Verify());
}

class MockAscendEnvValidator : public AscendEnvValidator {
 public:
  MOCK_METHOD(std::string, ReadVersion, (), (const, override));
};

TEST_F(AscendEnvValidatorTest, VerifyVersionGood) {
  auto validator = MockAscendEnvValidator();
  EXPECT_CALL(validator, ReadVersion()).Times(1).WillOnce(Return("7.0"));
  ASSERT_TRUE(validator.VerifyVersion());
}

TEST_F(AscendEnvValidatorTest, VerifyVersionBad) {
  auto validator = MockAscendEnvValidator();
  EXPECT_CALL(validator, ReadVersion()).Times(1).WillOnce(Return("7.1"));
  ASSERT_FALSE(validator.VerifyVersion());
}

std::string CreateTempFileWithContent(const std::string &content) {
  char path[] = "/tmp/ascend_version_test_XXXXXX";
  auto fd = mkstemp(path);
  if (fd == -1) {
    std::cerr << "make temp file failed: " << strerror(errno);
    return "";
  }
  int n = write(fd, content.c_str(), content.length());
  if (n != content.length()) {
    std::cerr << "write temp file failed: " << strerror(errno);
    unlink(path);
    return "";
  }
  system((std::string("cat ") + path).c_str());
  close(fd);
  return path;
}

TEST_F(AscendEnvValidatorTest, ReadVersionFromGoodFile) {
  std::string good_version = "Version=7.0.0.5.242\nversion_dir=CANN-7.0\n";
  auto version_path = CreateTempFileWithContent(good_version);
  ASSERT_FALSE(version_path.empty());
  auto result = AscendEnvValidator::ReadVersionFromFile(version_path);
  EXPECT_EQ(result, "7.0");
  unlink(version_path.c_str());
}

TEST_F(AscendEnvValidatorTest, ReadVersionFromNotExistedFile) {
  auto result = AscendEnvValidator::ReadVersionFromFile("not_exist_version_file");
  EXPECT_EQ(result, "");
}