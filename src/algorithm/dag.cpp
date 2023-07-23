//
// Created by zgd on 2023/7/15.
//

#include "dag.h"
#include <set>

/**
 * 判断是否为DAG。
 *
 * 算法思路：
 * 1、从图中找出入度为0的节点，放到一个map中；
 * 2、循环操作步骤1，如果能够完全找完，说明是DAG；因为存在环的情况下，有一批节点的入度至少为1.
 *
 * 实现思路：
 * 1、用一个map A保存邻接表的所有被连接节点，已经被连接的次数；
 * 2、用另外一个set B保存所有出现过的节点；
 * 3、遍历B中元素，判断是否在A中，如果不在，表示入度为0；从B中移除此阶段，
 *    从A中将此节点所连接的其它节点的被连接次数减1，如果减到0则删除它。
 * 4、重复3操作，直到B为空或者B中所有节点都在A中。
 *
 * 说明：空的图是合法的，对应的拓扑排序也为空。
 *
 * @return true: 是DAG； false: 不是DAG。
 */
bool DAG::IsValid() const {
  std::set<int> all_nodes; // node_id
  std::map<int, int> all_linked_nodes; // node_id: linked_count

  // 1. Init link info.
  for (const auto &node_links: graph_) {
    int node_id = node_links.first;
    const auto &linked_nodes = node_links.second;
    all_nodes.emplace(node_id);

    for (auto node: linked_nodes) {
      all_nodes.emplace(node);
      auto iter = all_linked_nodes.find(node);
      if (iter == all_linked_nodes.end()) {
        // not exist, initialize link_count as 1;
        all_linked_nodes.emplace(node, 1);
      } else {
        // found node, increase its link_count.
        iter->second++;
      }
    }
  }

  // 2. Run algorithm.
  while(!all_nodes.empty()) {
    bool found = false;
    int node_id;

    for (auto node: all_nodes) {
      if (all_linked_nodes.find(node) == all_linked_nodes.end()) {
        // This node is not linked by others, it can be removed.
        node_id = node;
        found = true;
        break;
      }
    }

    if (!found) {
      // There are still some nodes, which can not be removed.
      return false;
    }

    // Remove the node.
    all_nodes.erase(node_id);

    auto iter = graph_.find(node_id);
    if (iter == graph_.end()) {
      // This node does not link to any other nodes.
      continue;
    }

    const auto &linked_nodes = iter->second;
    for (auto &linked_node: linked_nodes) {
      auto iter = all_linked_nodes.find(linked_node);

      assert(iter != all_linked_nodes.end());

      auto &link_count = iter->second;
      link_count--;
      if (link_count <= 0) {
        all_linked_nodes.erase(linked_node);
      }
    }
  }

  return true;
}


