//
// Created by qwere on 04.11.2024.
//

#include <chrono>
#include <stack>
#include <iostream>
#include <algorithm>
#include "TspBabDfs.h"

namespace pea_tsp::algo {

TspBabDfs::TspBabDfs(const std::string &conf_path, const std::string &graph_conf_path) : TspAlgoBase(conf_path,
                                                                                                     graph_conf_path) {
  bound_algo = new TspNearestNeighbour(conf_path, false, graph_conf_path);
}

std::vector<int> TspBabDfs::FindSolution() {
  if (graph_ == nullptr) return {};

  auto path_weight = CalculateBound();
  auto path_tour = std::vector<int>{};

  if (path_weight < 0) return {};

  const auto start{std::chrono::steady_clock::now()};
  auto current_time{std::chrono::steady_clock::now()};

  auto found_optimal_solution = path_weight == optimal_solution_;

  for (auto start_point = 1; start_point <= graph_->GetDimension(); ++start_point) {
    const auto start_iteration{std::chrono::steady_clock::now()};

    std::stack<std::pair<int, int>> path_stack{};

    std::vector<int> current_path{};
    int current_depth = 1;

    if (do_show_progress_) {
      std::cout << "Start Point: " << start_point << "\n\tCurrent depth: " << current_depth << "/"
                << graph_->GetDimension() + 1 << "\n\n";
    }

    path_stack.emplace(start_point, current_depth);

    while (!path_stack.empty()) {
      auto current_point = path_stack.top();
      path_stack.pop();

      if (current_path.size() > current_point.second || current_point.second != current_depth) {
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

        if (current_path_weight <= path_weight) {
          path_weight = current_path_weight;
          path_tour = current_path;

          found_optimal_solution = path_weight == optimal_solution_;
        }
      }

      current_time = std::chrono::steady_clock::now();

      if (std::chrono::duration_cast<std::chrono::seconds>(current_time - start_iteration).count()
          >= max_time.count() / graph_->GetDimension())
        break;
    }
    if (do_show_progress_)
      std::cout << start_point << std::endl;

    if (found_optimal_solution) {
      std::cout << "Found optimal solution\n";
      break;
    }
  }

  const auto end{std::chrono::steady_clock::now()};
  std::chrono::duration<double> elapsed_seconds{end - start};

  if (path_tour.empty()) {
    best_found_solution = -1;
  } else best_found_solution = GetPathWeight(path_tour);

  SaveToFile(path_tour, path_weight, elapsed_seconds.count(), "TspBabDfs");

  return path_tour;
}

int TspBabDfs::CalculateBound() const {
  if (bound_algo == nullptr) return -1;

  return GetPathWeight(bound_algo->FindSolution());
}

} // algo
// pea_tsp