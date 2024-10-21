//
// Created by qwere on 09.10.2024.
//

#include <stack>
#include <algorithm>
#include <iostream>
#include <chrono>

#include "DfsBruteForce.h"

namespace pea_tsp::algo {
DfsBruteForce::DfsBruteForce(const std::string &conf_path) : TspAlgoBase(conf_path) {}

std::vector<int> DfsBruteForce::FindSolution(Graph &graph) {
  auto path_id = 1;
  auto path_weight = INT_MAX;
  auto path_tour = std::vector<int>{};

  const auto start{std::chrono::steady_clock::now()};

  for (auto start_point = 1; start_point <= graph.GetDimension(); ++start_point) {
    // stack of pairs <point_id, depth>
    // depth defines how deep node should be in path
    std::stack<std::pair<int, int>> path_stack{};

    int current_depth = 1;
    std::vector<int> current_path{};

    path_stack.emplace(start_point, current_depth++);

    while (!path_stack.empty()) {
      auto current_point = path_stack.top();
      path_stack.pop();

      if (current_path.size() > current_point.second) {
        current_path.erase(current_path.begin() + (current_point.second - 1), current_path.end());
        current_depth = current_point.second + 1;
      }

      current_path.emplace_back(current_point.first);

      auto neighbours =
          CreateVerticesVector(std::get<1>(graph.GetPoint(current_point.first)).size(),
                               current_point.first);

      neighbours.erase(std::remove_if(
          neighbours.begin(), neighbours.end(),
          [&current_path](const auto &n_item) -> bool {
            auto result = std::any_of(
                current_path.begin(), current_path.end(),
                [&n_item](const auto &pair_item) {
                  return n_item == pair_item;
                });
            return result;
          }
      ), neighbours.end());

      for (auto const &neighbour : neighbours) {
        path_stack.emplace(neighbour, current_depth);
      }

      ++current_depth;

      if (current_depth >= graph.GetDimension() + 2) {
        current_path.emplace_back(start_point);

        if (!IsPathTraversable(current_path, graph)) break;

        int current_path_weight = CalcPathTravelCost(graph, current_path);

        if (current_path_weight < path_weight && current_path_weight > 0) {
          path_weight = current_path_weight;
          path_tour = current_path;
        }
      }
    }
  }

  const auto end{std::chrono::steady_clock::now()};
  const std::chrono::duration<double> elapsed_seconds{end - start};

  SaveToFile(path_tour, path_weight, elapsed_seconds.count(), "Result.csv");
  return path_tour;
}

int DfsBruteForce::CalcPathTravelCost(Graph &graph, const std::vector<int> &current_path) {
  auto path_weight = 0;
  for (auto item = 0; item < current_path.size() - 1; ++item) {
    auto travel_weight = graph.GetTravelWeight(current_path[item], current_path[item + 1]);
    path_weight += travel_weight;
  }

  return path_weight;
}
} // algo
// pea_tsp