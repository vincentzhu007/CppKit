/**
 * Temporary file with RAII resource managing.
 *
 * Author: Vincent Zhu<vincentzhu007@gmail.com>
 * Create: 2023-04-22
 */

#ifndef CPPKIT_SRC_LINUX_TEMP_FILE_H_
#define CPPKIT_SRC_LINUX_TEMP_FILE_H_

#include <string>

namespace cppkit {
namespace linux {
/**
 * Temporary file used by process, will be unlinked by destructor.
 * Note: Invoker should keep instance alive when manipulate temporary file.
 */
class TempFile {
 public:
  /**
   * Create temporary file.
   *
   * @param name File name prefix
   */
  TempFile();

  /**
   * Create temporary file with the name prefix.
   * The result file name is 'name.XXXXXX', where 'XXXXXX' is a alphabet-digit
   * random sequence with the length of 6.
   *
   * @param name File name prefix
   */
  TempFile(const std::string &name);

  /**
   * Create temporary file with the name prefix.
   * The result file path is 'dir/name.XXXXXX', where 'XXXXXX' is a alphabet-digit
   * random sequence with the length of 6.
   *
   * @param dir in which directory which file created, it's MUST be existed, or an
   *    exception would be thrown.
   * @param name File name prefix
   */
  TempFile(const std::string &dir, const std::string &name);

  bool is_good() const { return is_good_; }

  const std::string &file() const { return file_; }

  ~TempFile();

 private:
  std::string file_ = "";
  bool is_good_ = false;
};
}
}

#endif //CPPKIT_SRC_LINUX_TEMP_FILE_H_
