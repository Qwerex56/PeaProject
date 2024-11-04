//
// Created by qwere on 03.10.2024.
//

#include "Graph.h"

#include <stdexcept>

namespace pea_tsp {
std::string Graph::GetName() const {
  return name_;
}

std::string Graph::GetComment() const {
  return comment_;
}

int Graph::GetDimension() const {
  return dimension_;
}

int Graph::GetTravelWeight(int from_id, int to_id) const {
  if (from_id == to_id) return -1;
  if (from_id <= 0 || to_id <= 0) return -1;
  if (from_id > GetDimension() || to_id > GetDimension()) return -1;

  return std::get<1>(GetPoint(from_id))[to_id - 1];
}

int Graph::GetPossiblePathCount() const {
  auto fact = [](int n){
    if (n <= 0) return 1;

    auto result = 1;
    while (n > 0) {
      result *= n--;
    }

    return result;
  };

  return fact(GetDimension());
}
} // pea_tsp