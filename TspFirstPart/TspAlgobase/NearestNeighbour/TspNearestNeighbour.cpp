//
// Created by qwere on 08.10.2024.
//

#include "TspNearestNeighbour.h"

#include <algorithm>
#include <stack>

namespace pea_tsp::algo {
[[maybe_unused]] TspNearestNeighbour::TspNearestNeighbour(const std::string &conf_path) : TspAlgoBase(conf_path) { }

std::vector<int> TspNearestNeighbour::FindSolution(Graph &graph) {
  auto path_weight = INT_MAX;
  auto path_tour = std::vector<int>{};

  for (auto start_point = 1; start_point <= graph.GetDimension(); ++start_point) {
    std::stack<std::pair<int, int>> path_stack{};

    int current_depth = 1;
    std::vector<int> current_path{};

    path_stack.emplace(start_point, current_depth);

    while (!path_stack.empty()) {
      auto current_point = path_stack.top();
      path_stack.pop();

      // Check depth
      if (current_path.size() > current_point.second) {
        current_path.erase(current_path.begin() + (current_point.second - 1), current_path.end());
        current_depth = current_point.second + 1;
      }

      current_path.emplace_back(current_point.first);

      auto nearest_neighbours = MinElementIds(
          std::get<1>(graph.GetPoint(current_point.first)),
          current_path);

      for (auto const &neighbour : nearest_neighbours) {
        path_stack.emplace(neighbour, current_depth);
      }

      ++current_depth;

      if (current_depth >= graph.GetDimension() + 2) {
        current_path.emplace_back(start_point);

        auto current_path_weight = 0;
        for (auto item = 0; item < current_path.size() - 1; ++item) {
          auto travel_weight = graph.GetTravelWeight(current_path[item], current_path[item + 1]);

          current_path_weight += travel_weight;

          if (travel_weight <= 0) {
            current_path_weight = INT_MAX;
            break;
          }
        }

        if (current_path_weight < path_weight) {
          path_weight = current_path_weight;
          path_tour = current_path;
        }
      }
    }
  }

  return path_tour;
}

[[maybe_unused]] size_t TspNearestNeighbour::MinElementId(const std::vector<int> &elements, const std::vector<int> &visited) {
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
  if (elements.begin() == elements.end()) return {elements.front()};

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
    points_ids = {};
  }

  return points_ids;
}
} // algo
// pea_tsp