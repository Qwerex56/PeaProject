//
// Created by qwere on 09.10.2024.
//

#include <stack>
#include <algorithm>
#include <chrono>

#include "DfsBruteForce.h"

namespace pea_tsp::algo {
DfsBruteForce::DfsBruteForce(const std::string &conf_path) : TspAlgoBase(conf_path) {}

std::vector<int> DfsBruteForce::FindSolution() {
  auto path_weight = INT_MAX;
  auto path_tour = std::vector<int>{};

  const auto start{std::chrono::steady_clock::now()};
  auto current_time{std::chrono::steady_clock::now()};

  for (auto start_point = 1; start_point <= graph_->GetDimension(); ++start_point) {
    // stack of pairs <point_id, depth>
    // depth defines how deep node should be in path
    std::stack<std::pair<int, int>> path_stack{};

    std::vector<int> current_path{};
    int current_depth = 1;

    path_stack.emplace(start_point, current_depth);

    while (!path_stack.empty()) {
      auto current_point = path_stack.top();
      path_stack.pop();

      if (current_path.size() > current_point.second) {
        current_path.erase(current_path.begin() + (current_point.second - 1), current_path.end());
        current_depth = current_point.second;
      }

      current_path.emplace_back(current_point.first);
      ++current_depth;

      auto neighbours =
          CreateVerticesVector(std::get<1>(graph_->GetPoint(current_point.first)).size(),
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

      if (current_depth > graph_->GetDimension()) {
        current_path.emplace_back(start_point);

        if (!IsPathTraversable(current_path)) continue;

        int current_path_weight = GetPathWeight(current_path);

        if (current_path_weight < path_weight && current_path_weight > 0) {
          path_weight = current_path_weight;
          path_tour = current_path;
        }
      }

      current_time = std::chrono::steady_clock::now();

      if (std::chrono::duration_cast<std::chrono::seconds>(current_time - start).count()
          >= max_time.count() / graph_->GetDimension())
        break;
    }
  }

  const auto end{std::chrono::steady_clock::now()};
  const std::chrono::duration<double> elapsed_seconds{end - start};

  if (path_tour.empty()) {
    best_found_solution = -1;
  } else best_found_solution = GetPathWeight(path_tour);

  SaveToFile(path_tour, path_weight, elapsed_seconds.count(), "DfsBruteForce");
  return path_tour;
}
} // algo
// pea_tsp