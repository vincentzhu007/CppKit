/**
 * MMap based file buffer with RAII resource managing.
 *
 * Author: Vincent Zhu<vincentzhu007@gmail.com>
 * Create: 2023-04-22
 */

#include "mmap_buffer.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>

namespace cppkit {
namespace linux_demo {
MmapBuffer::MmapBuffer(const std::string &file) : file_(file) {
  int fd = open(file.c_str(), O_RDWR);
  if (fd < 0) {
    std::cerr << "MmapBuffer ctor open: " << strerror(errno) << std::endl;
    return;
  }

  struct stat a_stat;
  if (fstat(fd, &a_stat) < 0) {
    std::cerr << "MmapBuffer ctor fstat: " << strerror(errno) << std::endl;
    close(fd);
    return;
  }
  size_ = static_cast<size_t>(a_stat.st_size);
  if (size_ == 0) {
    std::cerr << "MmapBuffer ctor: mapped file size is 0" << std::endl;
    close(fd);
    return;
  }

  address_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd); // fd can be closed intermediately after mmap, see man mmap for details.
  if (address_ == nullptr) {
    std::cerr << "MmapBuffer ctor mmap: " << strerror(errno) << std::endl;
    return;
  }
  is_good_ = true;
}

MmapBuffer::~MmapBuffer() {
  if (!is_good_) {
    return;
  }
  if (munmap(address_, size_) < 0) {
    std::cerr << "MmapBuffer ctor munmap: " << strerror(errno) << std::endl;
  }
}
}
}
