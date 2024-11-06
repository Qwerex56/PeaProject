//
// Created by qwere on 04.11.2024.
//

#include <chrono>
#include <stack>
#include "TspBabDfs.h"

namespace pea_tsp::algo {

TspBabDfs::TspBabDfs(const std::string &conf_path) : TspAlgoBase(conf_path) {
  bound_algo = new TspRandomPath(conf_path);
}

std::vector<int> TspBabDfs::FindSolution() {
  if (graph_ == nullptr) return {};

  auto path_weight = CalculateBound();
  auto path_tour = std::vector<int>{};

  if (path_weight < 0) return {};

  const auto start{std::chrono::steady_clock::now()};

  for (auto start_point = 1; start_point <= graph_->GetDimension(); ++start_point) {
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
          [current_path](const auto &n_item) -> bool {
            auto result = std::any_of(
                current_path.begin(), current_path.end(),
                [&n_item](const auto &pair_item) {
                  return n_item == pair_item;
                }
            );
            return result;
          }
      ), neighbours.end());

      for (auto const &neighbour : neighbours) {
        auto travel_weight = graph_->GetTravelWeight(current_path.back(), neighbour);

        if (travel_weight <= 0) continue;

        auto next_path_weight = GetPathWeight(current_path) + travel_weight;
        if (next_path_weight >= path_weight) continue;

        path_stack.emplace(neighbour, current_depth);
      }

      if (current_depth > graph_->GetDimension()) {
        current_path.emplace_back(start_point);

        if (!IsPathTraversable(current_path)) continue;

        int current_path_weight = GetPathWeight(current_path);

        if (current_path_weight < path_weight) {
          path_weight = current_path_weight;
          path_tour = current_path;
        }
      }
    }
  }

  const auto end {std::chrono::steady_clock::now()};
  std::chrono::duration<double> elapsed_seconds{end - start};

  SaveToFile(path_tour, path_weight, elapsed_seconds.count(), "TspBabDfs.csv");

  return path_tour;
}

int TspBabDfs::CalculateBound() const {
  if (bound_algo == nullptr) return -1;

  return GetPathWeight(bound_algo->FindSolutionWithTries(3));
}

} // algo
// pea_tsp