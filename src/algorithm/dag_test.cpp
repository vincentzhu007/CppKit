//
// Created by zgd on 2023/7/15.
//

#include <gtest/gtest.h>
#include "dag.h"

class DAGTest : public ::testing::Test {
 public:
  static void SetUpTestcases() {
  }
  static void TearDownTestcases() {
  }
  void SetUp() {
  }
  void TearDown() {
  }
};

TEST_F(DAGTest, IsValid) {
  std::map<int, std::vector<int>> graph;
  graph.emplace(0, std::vector<int>({1, 2})); // node 0
  graph.emplace(1, std::vector<int>({3})); // node 1
  graph.emplace(2, std::vector<int>({3})); // node 2

  DAG dag(graph);
  ASSERT_TRUE(dag.IsValid());
}

TEST_F(DAGTest, IsValidFalse) {
  std::map<int, std::vector<int>> graph;
  graph.emplace(0, std::vector<int>({1, 2})); // node 0
  graph.emplace(1, std::vector<int>({3})); // node 1
  graph.emplace(2, std::vector<int>({0})); // node 2

  DAG dag(graph);
  ASSERT_FALSE(dag.IsValid());
}
