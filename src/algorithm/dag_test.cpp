//
// Created by zgd on 2023/7/15.
//

#include "dag.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <gtest/gtest.h>

struct TestParam {
  std::string graph;
  bool expect;
};

class DAGTest : public ::testing::TestWithParam<TestParam> {
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

namespace {
/**
 * Generate the graph map with one string.
 * Input format:
 *  "0:1,2; 1:3; 2:3;"
 *
 *  1. Node MUST be represent as an integer.
 *  2. Total linkages of the node is seperated by ';'.
 *  3. Echo linked node index is seperated by ','.
 *  4. Any ' ', '\t' and '\n' is ignored.
 *
 * @param input String description.
 *
 * @return A map describes the node and its linkage.
 */
std::map<int, std::vector<int>> GenerateGraphFromString(const std::string &input) {
  std::map<int, std::vector<int>> graph;

  // Firstly, remove all spaces.
  std::string s = input;
  s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

  // Next, read node linkages.
  std::stringstream ss(s);
  std::string t;
  while (std::getline(ss, t, ';')) {
    auto n = t.find_first_of(':');
    if (n == std::string::npos) {
      continue; // Not found.
    }
    int node = std::stoi(t.substr(0, n));

    std::stringstream sub_ss(t.substr(n + 1));
    std::string v;
    std::vector<int> linked_nodes;
    while (std::getline(sub_ss, v, ',')) {
      linked_nodes.push_back(std::stoi(v));
    }
    graph.emplace(node, linked_nodes);
  }

  return graph;
}

void PrintGraph(const std::map<int, std::vector<int>> &graph) {
  // Print result graph
  std::cout << "{ ";
  for (const auto &g: graph) {
    std::cout << "{ " << g.first << " : ";
    for (auto i: g.second) {
      std::cout << i << " ";
    }
    std::cout << "}, ";
  }
  std::cout << "}" << std::endl;
}
}

TEST_P(DAGTest, IsValid) {
  auto input = GetParam();
  auto graph = GenerateGraphFromString(input.graph);
  PrintGraph(graph);

  DAG dag(graph);
  ASSERT_EQ(dag.IsValid(), input.expect);
}

INSTANTIATE_TEST_SUITE_P(ValidGraphs, DAGTest,
  testing::Values<TestParam>(
    TestParam { "", true },
    TestParam { "1:2", true},
    TestParam { "1:2;2:3;3:4", true },
    TestParam { "0:1,2; 1:3; 2:3;", true },
    TestParam { "0:1;", true },
    TestParam { "0:; 1:2;", true },
    TestParam { "0:1; 1:2,3;", true }
 )
);

INSTANTIATE_TEST_SUITE_P(InvalidGraphs, DAGTest,
  testing::Values<TestParam>(
    TestParam { "0:1;1:0", false },
    TestParam { "0:1; 1:2; 2:0", false }
  )
);

