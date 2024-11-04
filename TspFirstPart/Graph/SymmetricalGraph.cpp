//
// Created by qwere on 03.10.2024.
//

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <valarray>

#include "SymmetricalGraph.h"

namespace pea_tsp {
SymmetricalGraph::SymmetricalGraph(const std::string &path) {
  auto file = std::fstream{path};

  if (!file.is_open()) {
    std::cout << "Failed to open\n";

    name_ = "";
    comment_ = "";
    dimension_ = -1;
  } else {
    std::string line;

    while (!file.eof()) {
      std::getline(file, line);
      if (line == "EOF") break;
      if (line == "NODE_COORD_SECTION") break;

      std::stringstream str_stream(line);
      std::string token;
      std::vector<std::string> tokens;
      tokens.reserve(2);

      while (std::getline(str_stream, token, ':')) {
        if (token.starts_with(" ")) {
          token = token.substr(1, token.length() - 1);
        }

        if (token.ends_with(" ")) {
          token = token.substr(0, token.length() - 1);
        }

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

    points = {};

    while (!file.eof()) {
      std::getline(file, line);
      if (line == "EOF") break;

      std::stringstream str_stream(line);
      std::string token;
      std::vector<int> tokens;
      tokens.reserve(3);

      while (std::getline(str_stream, token, ' ')) {
        if (token.starts_with(" ")) {
          token = token.substr(1, token.length() - 1);
        }

        if (token.ends_with(" ")) {
          token = token.substr(0, token.length() - 1);
        }

        tokens.emplace_back(std::stoi(token));
      }

      AddPoint(tokens[0], tokens[1], tokens[2]);
    }
  }
}

Graph &SymmetricalGraph::AddPoint(int point_id, int coordinate_x, int coordinate_y) {
  points[point_id] = {coordinate_x, coordinate_y};

  return *this;
}

std::tuple<int, std::vector<int>> SymmetricalGraph::GetPoint(const int &point_id) const {
  if (!points.contains(point_id)) {
    return {-1, {}};
  }

  auto point_x = points.at(point_id)[0];
  auto point_y = points.at(point_id)[1];
  auto arr = std::vector<int>(GetDimension());

  for (int i = 1; i <= points.size(); ++i) {
    if (point_id == i) {
      arr.emplace_back(-1);
      continue;
    }

    auto neighbour_x = points.at(i)[0];
    auto neighbour_y = points.at(i)[1];

    auto length = std::sqrt(std::pow(neighbour_x - point_x, 2) + std::pow(neighbour_y - point_y, 2));
    arr.emplace_back(static_cast<int>(length));
  }

  return {point_id, arr};
}

std::ostream &operator<<(std::ostream &os, SymmetricalGraph &g) {
  os << "Name: " << g.GetName() << std::endl;
  os << "Comment: " << g.GetComment() << std::endl;
  os << "Dimension: " << g.GetDimension() << std::endl;

  for (const auto &point : g.points) {
    std::cout << point.first << ": " << point.second[0] << " " << point.second[1] << std::endl;
  }

  return os;
}
} // pea_tsp