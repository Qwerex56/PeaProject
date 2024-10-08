//
// Created by qwere on 08.10.2024.
//

#include "TspNearestNeighbour.h"

#include <algorithm>

namespace pea_tsp::algo {
std::vector<int> TspNearestNeighbour::FindSolution(Graph &graph) {
  auto min_path_weight = upper_bound_;
  std::vector<int> min_path_tour = {};

  auto path_counter = 1;
  auto possible_paths_count = graph.GetDimension();

  for (auto start_point = 1; start_point <= graph.GetDimension(); ++start_point) {
    auto current_path = std::vector<int>{start_point};
    auto current_path_weight = 0;

    // Add all unvisited vertices
    auto vertices = std::vector<int>{};
    for (auto v = 1; v <= graph.GetDimension(); ++v) {
      if (v == start_point) continue;
      vertices.emplace_back(v);
    }

    do {
      auto connections = std::get<1>(graph.GetPoint(current_path.back()));
      auto min_connection_id = MinElementId(connections, current_path);

      current_path.emplace_back(min_connection_id);
      vertices.erase(std::remove_if(vertices.begin(), vertices.end(), [&](const auto &item) {
        return item == min_connection_id;
      }), vertices.end());

    } while (!vertices.empty());

    current_path.emplace_back(start_point);
    auto last_id = start_point;
    for (auto const &vertex_id : current_path) {
      current_path_weight += std::get<1>(graph.GetPoint(last_id))[vertex_id - 1];
      last_id = vertex_id;
    }

    if (current_path_weight < min_path_weight) {
      min_path_weight = current_path_weight;
      min_path_tour = current_path;
    }
  }

  return std::vector<int>();
}

const size_t TspNearestNeighbour::MinElementId(const std::vector<int> &elements, const std::vector<int> &visited) {
  if (elements.begin() == elements.end()) return *elements.begin();

  auto smallest = INT_MAX;
  auto point_id = 0;

  for (auto i = 0; i < elements.size(); ++i) {
    if (elements[i] <= 0) continue;
    if (elements[i] > smallest) continue;
    if (std::any_of(visited.begin(), visited.end(),
                    [&i](const int &item){return item == (i + 1);}))
      continue;

    smallest = elements[i];
    point_id = i + 1;
  }

  return point_id;
}
} // algo
// pea_tsp