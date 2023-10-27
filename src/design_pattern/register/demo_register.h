//
// Created by zgd on 2023/10/27.
//

#ifndef CPPKIT_SRC_DESIGN_PATTERN_REGISTER_DEMO_REGISTER_H_
#define CPPKIT_SRC_DESIGN_PATTERN_REGISTER_DEMO_REGISTER_H_

#include <string>
#include <map>
#include <any>
#include <functional>

using DemoCreator = std::function<std::any ()>;

class DemoRegistry {
 public:
  static DemoRegistry &GetInstance() {
    static DemoRegistry instance;
    return instance;
  }

  DemoCreator GetCreator(const std::string key) const {
    auto iter = registry_.find(key);
    if (iter == registry_.end()) {
      return nullptr;
    }
    return iter->second;
  }

  void Clear() {
    registry_ = {};
  }

 protected:
  bool Register(std::string key, DemoCreator creator) {
    registry_.emplace(key, creator);
  }

 private:
  DemoRegistry() = default;
  ~DemoRegistry() = default;

  friend class DemoRegistrar;

  std::map<std::string, DemoCreator> registry_;
};

class DemoRegistrar {
 public:
  DemoRegistrar(std::string key, DemoCreator creator) {
    (void)DemoRegistry::GetInstance().Register(key, creator);
  }
};

#define REG_DEMO(key, creator) \
  static DemoRegistrar kDemoRegistrar##key##creator(key, creator)

#endif //CPPKIT_SRC_DESIGN_PATTERN_REGISTER_DEMO_REGISTER_H_
