//
// Created by qwere on 13.11.2024.
//

#include <queue>
#include <iostream>
#include "TspBestFirstSearch.h"

namespace pea_tsp::algo {
TspBestFirstSearch::TspBestFirstSearch(const std::string &conf_path, const std::string &graph_conf_path) : TspAlgoBase(
    conf_path,
    graph_conf_path) {
  bound_algo = new TspNearestNeighbour(conf_path, false, graph_conf_path);
}

std::vector<int> TspBestFirstSearch::FindSolution() {
  if (graph_ == nullptr) return {};

  auto path_weight = CalculateBound();
  auto path_tour = std::vector<int>{};

  if (path_weight < 0) return {};

  const auto start{std::chrono::steady_clock::now()};
  auto current_time{std::chrono::steady_clock::now()};

  auto found_optimal_solution = path_weight == optimal_solution_;

  struct Node {
    int current_point;
    std::vector<int> path;

    // added to satisfy pq
    int travel_cost;

    bool operator>(const Node &other) const {
      return this->travel_cost > other.travel_cost;
    }
  };

  for (auto start_point = 1; start_point <= graph_->GetDimension(); ++start_point) {
    const auto start_iteration{std::chrono::steady_clock::now()};

    std::priority_queue<Node, std::vector<Node>, std::greater<>> path_queue{};
    path_queue.emplace(start_point, std::vector<int>{start_point}, graph_->GetTravelWeight(start_point, start_point));

    while (!path_queue.empty()) {
      auto current_node = path_queue.top();
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
        path_queue.emplace(neighbour, current_path, travel_weight);
        current_path.pop_back();
      }

      if (current_path.size() >= graph_->GetDimension()) {
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

  SaveToFile(path_tour, path_weight, elapsed_seconds.count(), "TspBabBestFs");

  return path_tour;
}

int TspBestFirstSearch::CalculateBound() const {
  if (bound_algo == nullptr) return -1;

  return GetPathWeight(bound_algo->FindSolution());
}
} // algo
// pea_tsp