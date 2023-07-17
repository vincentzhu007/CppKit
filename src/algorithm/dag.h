//
// Created by zgd on 2023/7/15.
//

#ifndef CPPKIT_SRC_ALGORITHM_DAG_H_
#define CPPKIT_SRC_ALGORITHM_DAG_H_

#include <vector>
#include <map>

/**
 * DAG 有向无环图(Directed Acyclic Graph)
 */

class DAG {
 public:
  DAG(const std::map<int, std::vector<int>> &graph) : graph_(graph) {}
  bool IsValid() const;
 private:
  std::map<int, std::vector<int>> graph_;
};

#endif //CPPKIT_SRC_ALGORITHM_DAG_H_
