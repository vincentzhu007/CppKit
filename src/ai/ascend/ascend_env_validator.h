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


std::string kVersionSubPath = "/latest/compiler/version.info";

class AscendEnvValidator {
 public:
  AscendEnvValidator() {
  }


  bool Verify() {
    return true;
  }

  bool VerifyVersion() {
    std::set<std::string> kValidVersions = {"7.0", "6.4" };
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
  virtual std::string ReadVersion() {
    return ReadVersionFromFile(version_path_);
  }

  bool VerifyCannInstallDir() {
    return false;
  }

  std::string version_path_; // the file path stores version info.
};

#endif //CPPKIT_SRC_AI_ASCEND_ASCEND_ENV_VALIDATOR_H_
