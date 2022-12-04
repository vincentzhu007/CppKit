/**
 * Error is a basic error code class. When an error happens, it can take the error code and detail message to the caller.
 * it's designed to severed for two purposes:
 *     1. providing a human-friend error message string for software activity log;
 *     2. providing an error code check functions for error code check.
 */

#ifndef CPPKIT_SRC_ERROR_ERROR_H_
#define CPPKIT_SRC_ERROR_ERROR_H_

#include <string>
#include <memory>

namespace cppkit {
enum class ErrorCode : int {
  kOk = 0,
  kError = 1,
  kNullPoint = 2,
  kBadFuncParm = 3,
  kNoPermission = 4,
};

class Error {
 public:
  Error() {};
  Error(ErrorCode code) : error_code_(code) {}
  Error(ErrorCode code, const std::string &message): error_code_(code) {
    message_ = std::make_shared<std::string>(message);
  }
  bool &operator==(const Error &) = delete;

  bool IsOk() { return error_code_ == ErrorCode::kOk; }
  bool IsError() { return error_code_ == ErrorCode::kError; }
  bool IsNullPoint() { return error_code_ == ErrorCode::kNullPoint; }
  bool EqualCode(ErrorCode code) { return error_code_ == code; }
  std::string Message() { return (message_ != nullptr) ? (*message_) : ""; }

 private:
  ErrorCode error_code_ = ErrorCode::kOk;
  std::shared_ptr<std::string> message_ = nullptr;
};
}

#endif //CPPKIT_SRC_ERROR_ERROR_H_
