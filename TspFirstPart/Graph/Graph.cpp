//
// Created by qwere on 03.10.2024.
//

#include "Graph.h"

#include <utility>
#include <stdexcept>

namespace pea_tsp {
std::string Graph::GetName() const {
  std::string ret;
  try {
    ret = conf_.at("NAME");
  } catch (std::out_of_range &otr) { }

  return ret;
}

std::string Graph::GetComment() const {
  std::string ret;
  try {
    ret = conf_.at("COMMENT");
  } catch (std::out_of_range &otr) { }

  return ret;
}

int Graph::GetDimension() const {
  std::string ret;
  try {
    ret = conf_.at("DIMENSION");
  } catch (std::out_of_range &otr) { }

  return std::stoi(ret);
}

void Graph::SetName(const std::string &name) {
  conf_["NAME"] = name;
}

void Graph::SetComment(const std::string &comment) {
  conf_["COMMENT"] = comment;
}

void Graph::SetDimension(int dimension) {
  conf_["DIMENSION"] = std::to_string(dimension);
}

void Graph::SetDimension(const std::string &dimension) {
  conf_["DIMENSION"] = dimension;
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