//
// Created by qwere on 03.10.2024.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include "AsymmetricalGraph.h"

namespace pea_tsp {
AsymmetricalGraph::AsymmetricalGraph(const std::string &path) {
  auto file = std::fstream{path};

  if (!file.is_open()) {
    std::cout << "Failed to open\n";

    name_ = "";
    comment_ = "";
    dimension_ = -1;
  } else {
    std::string line;

    while (line != "EDGE_WEIGHT_SECTION") {
      std::getline(file, line);

      std::stringstream str_stream{line};
      std::string token;
      std::vector<std::string> tokens;
      tokens.reserve(4);

      while (std::getline(str_stream, token, ':')) {
        tokens.emplace_back(token);
      }

      if (tokens[0] == "NAME") {
        name_ = tokens[1];
      } else if (tokens[0] == "COMMENT") {
        comment_ = tokens[1];
      } else if (tokens[0] == "DIMENSION") {
        dimension_ = std::stoi(tokens[1]);
      }
    }

    std::string token;
    std::vector<std::string> tokens;

    tokens.reserve(GetDimension() + 1);

    for (auto i = 1; i <= GetDimension();) {
      std::getline(file, line);

      std::stringstream str_stream{line};

      while (std::getline(str_stream, token, ' ')) {
        if (token.empty()) continue;
        tokens.emplace_back(token);
      }

      if (tokens.size() < GetDimension()) {
        continue;
      } else {
        for (int j = 1; j <= tokens.size(); ++j) {
          AddPoint(i, j, std::stoi(tokens[j - 1]));
        }

        ++i;
        tokens = {};
        tokens.reserve(GetDimension());
      }
    }
  }
}

Graph &AsymmetricalGraph::AddPoint(int point_id, int to_point, int weight) {
  if (!points.contains(point_id)) {
    points[point_id] = {};
    points[point_id].reserve(GetDimension() + 1);
  }

  if (point_id == to_point || weight == -1 || weight >= 9999 || weight == 0) {
    weight = -1;
  }

  points[point_id].emplace_back(weight);

  return *this;
}

std::tuple<int, std::vector<int>> AsymmetricalGraph::GetPoint(const int &point_id) const {
  if (!points.contains(point_id)) {
    return {-1, {}};
  }

  return {point_id, points.at(point_id)};
}

std::ostream &operator<<(std::ostream &os, AsymmetricalGraph &g) {


  return os;
}
} // pea_tsp