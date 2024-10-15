//
// Created by qwere on 16.10.2024.
//

#include <random>
#include <algorithm>

#include "TspRandomPath.h"

namespace pea_tsp::algo {

TspRandomPath::TspRandomPath(const std::string &conf_path) : TspAlgoBase(conf_path) {}

std::vector<int> TspRandomPath::FindSolution() {
  if (!graph_) return {};

  return FindSolution(*graph_);
}

std::vector<int> TspRandomPath::FindSolution(Graph &graph) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(1, graph.GetDimension());

  auto path = std::vector<int>(graph.GetDimension());
  auto paths = std::vector<std::vector<int>>();
  std::iota(path.begin(), path.end(), 1);

  // TODO: make 3 a conf parameter
  auto max_tries = graph.GetPossiblePathCount();

  if (graph.GetDimension() >= 9) {
    max_tries /= 3;
  }
  paths.reserve(max_tries);

  auto min_travel_weight = INT_MAX;
  auto min_path = std::vector<int>();

  for (auto path_id = 0; path_id < max_tries; ++path_id) {
    auto current_path_weight = 0;

    for (auto item = 0; item < graph.GetDimension() - 1; ++item) {
      auto travel_weight = graph.GetTravelWeight(path[item], path[item + 1]);

      if (travel_weight <= 0) break;

      current_path_weight += travel_weight;
    }

    if (current_path_weight < min_travel_weight) {
      min_travel_weight = current_path_weight;
      min_path = path;
    }

    // Shuffle path
    while (std::any_of(paths.begin(), paths.end(), [&path](auto &item) {
      return std::equal(path.begin(), path.end(), item.begin(), item.end());
    })) {
      std::shuffle(path.begin(), path.end(), gen);
    }

    paths.emplace_back(path);
  }

  return min_path;
}

} // algo
// pea_tsp