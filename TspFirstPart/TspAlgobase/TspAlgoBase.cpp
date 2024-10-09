//
// Created by qwere on 07.10.2024.
//

#include <algorithm>
#include <numeric>

#include "TspAlgoBase.h"

namespace pea_tsp::algo {
std::vector<int> TspAlgoBase::CreateVerticesVector(const int vertices_count, const int start_point) {
  std::vector<int> vertices = {};
  vertices.reserve(vertices_count);

  for (auto i = 1; i <= vertices_count; ++i) {
    if (i == start_point) continue;
    vertices.emplace_back(i);
  }

  return vertices;
}
bool TspAlgoBase::IsPathTraversable(const std::vector<int> &path, Graph &graph) const {
  auto result = true;
  for (auto node = 0; node < path.size() - 1; ++node) {
    auto weight = std::get<1>(graph.GetPoint(path[node]))[node + 1];
    if (weight <= 0) {
      result = false;
    }
  }

  return result;
}
} // algo
// pea_tsp