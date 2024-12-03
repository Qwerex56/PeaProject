//
// Created by qwere on 08.10.2024.
//

#include "TspNearestNeighbour.h"

#include <algorithm>
#include <stack>
#include <chrono>
#include <iostream>

namespace pea_tsp::algo {
[[maybe_unused]] TspNearestNeighbour::TspNearestNeighbour(const std::string &conf_path,
                                                          bool create_log,
                                                          const std::string &graph_conf_path)
    : TspAlgoBase(conf_path, graph_conf_path) {
  do_crete_log = create_log;
}

std::vector<int> TspNearestNeighbour::FindSolution() {
  if (graph_ == nullptr) {
    return {};
  }

  auto path_weight = INT_MAX;
  auto path_tour = std::vector<int>{};

  const auto start{std::chrono::steady_clock::now()};
  auto current_time{std::chrono::steady_clock::now()};

  auto found_optimal_solution = path_weight == optimal_solution_;

  for (auto start_point = 1; start_point <= graph_->GetDimension(); ++start_point) {
    const auto start_iteration{std::chrono::steady_clock::now()};

    std::stack<std::pair<int, int>> path_stack{};

    std::vector<int> current_path{};
    auto current_depth = 1;

    path_stack.emplace(start_point, current_depth);

    while (!path_stack.empty()) {
      auto current_point = path_stack.top();
      path_stack.pop();

      // Check depth
      if (current_path.size() > current_point.second) {
        current_path.erase(current_path.begin() + (current_point.second - 1), current_path.end());
        current_depth = current_point.second;
      }

      current_path.emplace_back(current_point.first);
      ++current_depth;

      auto nearest_neighbours = MinElementIds(
          std::get<1>(graph_->GetPoint(current_point.first)),
          current_path);

      for (auto const &neighbour : nearest_neighbours) {
        path_stack.emplace(neighbour, current_depth);
      }

      if (current_depth > graph_->GetDimension()) {
        current_path.emplace_back(start_point);

        if (!IsPathTraversable(current_path)) continue;

        auto current_path_weight = GetPathWeight(current_path);

        if (current_path_weight < path_weight) {
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
  const std::chrono::duration<double> elapsed_seconds{end - start};

  if (path_tour.empty()) {
    best_found_solution = -1;
  } else best_found_solution = GetPathWeight(path_tour);

  if (do_crete_log) {
    SaveToFile(path_tour,
               path_weight,
               elapsed_seconds.count(),
               "TspNN");
  }
  return path_tour;
}

[[maybe_unused]] size_t TspNearestNeighbour::MinElementId(const std::vector<int> &elements,
                                                          const std::vector<int> &visited) {
  if (elements.begin() == elements.end()) return *elements.begin();

  auto smallest = INT_MAX;
  auto point_id = -1;

  for (auto i = 0; i < elements.size(); ++i) {
    if (elements[i] <= 0) continue;
    if (elements[i] >= smallest) continue;
    if (std::any_of(visited.begin(), visited.end(),
                    [&i](const auto &item) { return item == (i + 1); }))
      continue;

    smallest = elements[i];
    point_id = i + 1;
  }

  return point_id;
}

std::vector<int> TspNearestNeighbour::MinElementIds(const std::vector<int> &elements,
                                                    const std::vector<int> &visited) {
  auto smallest = INT_MAX;
  auto points_ids = std::vector<int>{};

  for (auto i = 0; i < elements.size(); ++i) {
    if (elements[i] <= 0) continue;
    if (elements[i] > smallest) continue;
    if (std::any_of(visited.begin(), visited.end(),
                    [&i](const auto &item) { return item == (i + 1); }))
      continue;

    if (elements[i] == smallest) {
      points_ids.emplace_back(i + 1);

      continue;
    }

    smallest = elements[i];
    points_ids = {i + 1};
  }

  return points_ids;
}
} // algo
// pea_tsp