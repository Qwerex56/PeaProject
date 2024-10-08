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

int const Graph::GetDimension() {
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
} // pea_tsp