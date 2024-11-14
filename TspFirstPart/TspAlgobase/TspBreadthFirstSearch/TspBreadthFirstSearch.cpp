//
// Created by qwere on 12.11.2024.
//

#include <queue>
#include <iostream>
#include "TspBreadthFirstSearch.h"

namespace pea_tsp::algo {

[[maybe_unused]] TspBreadthFirstSearch::TspBreadthFirstSearch(const std::string &conf_path) : TspAlgoBase(conf_path) {
  bound_algo = new TspNearestNeighbour(conf_path, false);
}

std::vector<int> TspBreadthFirstSearch::FindSolution() {
  if (graph_ == nullptr) return {};

  auto path_weight = CalculateBound();
  auto path_tour = std::vector<int>{};

  if (path_weight < 0) return {};

  const auto start{std::chrono::steady_clock::now()};
  auto current_time{std::chrono::steady_clock::now()};
  auto has_time_passed = false;

  struct Node {
    int current_point;
    std::vector<int> path;
  };

  for (auto start_point = 1; start_point <= graph_->GetDimension(); ++start_point) {
    std::queue<Node> path_queue{};
    path_queue.emplace(start_point, std::vector<int>{start_point});

    while (!path_queue.empty()) {
      auto current_node = path_queue.front();
      path_queue.pop();

      auto neighbours = CreateVerticesVector(graph_->GetDimension(), current_node.current_point);

      auto current_path = current_node.path;

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

      for (const auto neighbour : neighbours) {
        auto travel_weight = graph_->GetTravelWeight(current_path.back(), neighbour);

        if (travel_weight <= 0) continue;

        auto next_path_weight = GetPathWeight(current_path) + travel_weight;
        if (next_path_weight >= path_weight) continue;

        current_path.emplace_back(neighbour);
        path_queue.emplace(neighbour, current_path);
        current_path.pop_back();
      }

      if (current_path.size() >= graph_->GetDimension()) {
        current_path.emplace_back(start_point);

        if (!IsPathTraversable(current_path)) continue;

        int current_path_weight = GetPathWeight(current_path);

        if (current_path_weight <= path_weight) {
          path_weight = current_path_weight;
          path_tour = current_path;
        }
      }

      current_time = std::chrono::steady_clock::now();
      has_time_passed =
          std::chrono::duration_cast<std::chrono::seconds>(current_time - start).count() >= max_time.count();

      if (std::chrono::duration_cast<std::chrono::seconds>(current_time - start).count()
          >= max_time.count() / graph_->GetDimension())
        break;
    }

    if (has_time_passed) break;
  }

  const auto end{std::chrono::steady_clock::now()};
  std::chrono::duration<double> elapsed_seconds{end - start};

  if (path_tour.empty()) {
    best_found_solution = -1;
  } else best_found_solution = GetPathWeight(path_tour);

  SaveToFile(path_tour, path_weight, elapsed_seconds.count(), "TspBabBfs");

  return path_tour;
}

int TspBreadthFirstSearch::CalculateBound() const {
  if (bound_algo == nullptr) return -1;

  return GetPathWeight(bound_algo->FindSolution());
}

} // algo
// pea_tsp