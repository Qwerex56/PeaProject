//
// Created by qwere on 08.10.2024.
//

#include <algorithm>
#include <iostream>

#include "TspBruteForce.h"

namespace pea_tsp::algo {
std::vector<int> TspBruteForce::FindSolution(Graph &graph) {
  auto min_path_weight = upper_bound_;
  std::vector<int> min_path_tour = {};

  std::vector<int> vertices;
  vertices.reserve(graph.GetDimension());

  auto path_counter = 1;
  auto possible_paths_count = 1;
  for (auto j = 1; j <= graph.GetDimension(); ++j) possible_paths_count *= j;

  for (auto start_point = 1; start_point <= graph.GetDimension(); ++start_point) {
    vertices = {};
    auto current_path_weight = 0;

    // Create list of vertices
    for (auto i = 1; i <= graph.GetDimension(); ++i) {
      if (i == start_point) continue;
      vertices.emplace_back(i);
    }

    do {
      auto current = start_point;
      vertices.emplace_back(start_point);

      for (const auto &vertex : vertices) {

        auto travel_weight = std::get<1>(graph.GetPoint(current))[vertex - 1];

        if (travel_weight == -1) {
          current_path_weight = -1;
          break;
        }

        current = vertex;
        current_path_weight += travel_weight;

        if (current_path_weight >= min_path_weight) break;
      }

      if (current_path_weight != -1 && min_path_weight > current_path_weight) {
        min_path_weight = current_path_weight;
        min_path_tour = vertices;
      }

      current_path_weight = 0;

      vertices.pop_back();

      if (do_show_progress) {
        std::cout << "Done path: " << path_counter++ << "\t of: " << possible_paths_count << std::endl;
      }
    } while (std::next_permutation(vertices.begin(), vertices.end()));

  }

  return min_path_tour;
}
} // algo
// pea_tsp