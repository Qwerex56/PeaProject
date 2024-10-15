//
// Created by qwere on 03.10.2024.
//

#include "Graph.h"

#include <utility>

namespace pea_tsp {
std::string Graph::GetName() {
  return conf_["NAME"];
}

std::string Graph::GetComment() {
  return conf_["COMMENT"];
}

int Graph::GetDimension() {
  return std::stoi(conf_["DIMENSION"]);
}

void Graph::SetName(std::string name) {
  conf_["NAME"] = std::move(name);
}

void Graph::SetComment(std::string comment) {
  conf_["COMMENT"] = std::move(comment);
}

void Graph::SetDimension(int dimension) {
  conf_["DIMENSION"] = std::to_string(dimension);
}

void Graph::SetDimension(std::string dimension) {
  conf_["DIMENSION"] = std::move(dimension);
}

int Graph::GetTravelWeight(int from_id, int to_id) {
  if (from_id == to_id) return -1;
  if (from_id <= 0 || to_id <= 0) return -1;
  if (from_id > GetDimension() || to_id > GetDimension()) return -1;

  return std::get<1>(GetPoint(from_id))[to_id];
}
} // pea_tsp