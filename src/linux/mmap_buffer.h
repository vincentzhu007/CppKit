/**
 * MMap based file buffer with RAII resource managing.
 *
 * Author: Vincent Zhu<vincentzhu007@gmail.com>
 * Create: 2023-04-22
 */

#ifndef CPPKIT_SRC_LINUX_MMAPBUFFER_H_
#define CPPKIT_SRC_LINUX_MMAPBUFFER_H_

#include <string>

namespace cppkit {
namespace linux {
class MmapBuffer {
 public:
  explicit MmapBuffer(const std::string &file);
  ~MmapBuffer();

  bool is_good() const { return is_good_; }
  void *address() const { return address_; }
  size_t size() const { return size_; }
  const std::string &file() const { return file_; }

 private:
  std::string file_; // Mapped file name.
  void *address_; // Buffer head address.
  size_t size_; // Buffer size.
  bool is_good_ = false; // Indicate whether buffer is constructed correctly.
};
} // linux
} // cppkit


#endif //CPPKIT_SRC_LINUX_MMAPBUFFER_H_
