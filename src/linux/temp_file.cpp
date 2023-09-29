/**
 * Temporary file with RAII resource managing.
 *
 * Author: Vincent Zhu<vincentzhu007@gmail.com>
 * Create: 2023-04-22
 */

#include "temp_file.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

namespace cppkit {
namespace linux_demo {
TempFile::TempFile() : TempFile("./", "temp") {}

TempFile::TempFile(const std::string &name) : TempFile("./", name) {}

TempFile::TempFile(const std::string &dir, const std::string &name) {
  auto absolute_dir = realpath(dir.c_str(), nullptr);
  if (absolute_dir == nullptr) {
    std::cerr <<  "TempFile ctor realpath(): " << std::string(strerror(errno)) << std::endl;
    return;
  }

  file_ = absolute_dir + std::string("/") + name + ".XXXXXX";
  free(absolute_dir); // Return string allocated by above realpath() should be freed by invoker.

  if (mkstemp(const_cast<char *>(file_.c_str())) == -1) {
    std::cerr <<  "TempFile ctor mkstemp(): " << std::string(strerror(errno)) << std::endl;
    return;
  }
  is_good_ = true;
}

TempFile::~TempFile() {
  if (!is_good_) {
    return;
  }
  if(unlink(file_.c_str()) == -1) {
    std::cerr <<  "TempFile dtor unlink(): " << std::string(strerror(errno));
  }
}
}
}