//
// Created by zgd on 2023/10/26.
//

#ifndef CPPKIT_SRC_AI_ASCEND_ASCEND_ENV_VALIDATOR_H_
#define CPPKIT_SRC_AI_ASCEND_ASCEND_ENV_VALIDATOR_H_

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <map>

std::set<std::string> kValidVersions = {"7.0"};
std::string kVersionSubPath = "/latest/compiler/version.info";

class AscendEnvValidator {
 public:
  AscendEnvValidator() {
  }

  bool Verify() {
    return true;
  }

  bool VerifyEnv() const {
    const std::map<std::string, std::string> env_checklist = {
        // Check if env 'Path' consists compiler bin path.
        {"PATH", "/compiler/ccec_compiler/bin"},
        // Check if env 'PYTHONPATH' consists tbe operator path.
        {"PYTHONPATH", "opp/built-in/op_impl/ai_core/tbe"},
        // Check if env 'LD_LIBRARY_PATH' consists tbe fwk lib path.
        {"LD_LIBRARY_PATH", "/lib64"},
        {"LD_LIBRARY_PATH", "/add-ons"},
        {"ASCEND_OPP_PATH", "/op"}
    };
    for (auto iter: env_checklist) {
      auto found = VerifyItemInEnv(iter.first, iter.second);
      if (!found) {
        return false;
      }
    }
    return true;
  }

  bool VerifyItemInEnv(const std::string &env_name, const std::string & target_content) const {
    char *var = getenv(env_name.c_str());
    if (var == nullptr) {
      std::cout << "Found no env named " << env_name;
      return false;
    }
    
    return true;
  }

  bool VerifyVersion() const {
    auto currentVersion = ReadVersion();
    return kValidVersions.find(currentVersion) != kValidVersions.end();
  }

  static std::string ReadVersionFromFile(const std::string &version_path) {
    const int kLineMax = 256;
    const int kVersionLength = 3;
    const std::string kVersionTag= "Version=";
    std::ifstream ifs(version_path);
    if (!ifs.good()) {
      std::cerr << "Can not read CANN version path"; // TODO: print more detail error message.
      return "";
    }

    char line_buf[kLineMax];
    std::string version_str = "";
    while(!ifs.eof()) {
      ifs.getline(line_buf, kLineMax);
      // Find line starts with "Version=", for example: "Version=7.0.0.5.242".
      if (strncmp(line_buf, kVersionTag.c_str(), kVersionTag.length()) == 0) {
        version_str = std::string(line_buf).substr(kVersionTag.length(), kVersionLength);
        break;
      }
    }
    return version_str;
  }
 private:
  virtual std::string ReadVersion() const {
    return ReadVersionFromFile(version_path_);
  }

  std::string version_path_; // the file path stores version info.
};

#endif //CPPKIT_SRC_AI_ASCEND_ASCEND_ENV_VALIDATOR_H_
