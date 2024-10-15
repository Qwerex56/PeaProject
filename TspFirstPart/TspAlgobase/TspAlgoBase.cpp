//
// Created by qwere on 07.10.2024.
//

#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>

#include "TspAlgoBase.h"
#include "../Graph/SymmetricalGraph.h"
#include "../Graph/AsymmetricalGraph.h"

namespace pea_tsp::algo {
TspAlgoBase::TspAlgoBase(const std::string &conf_path) {
  auto file = std::fstream{conf_path};

  if (!file.is_open()) {
    std::cout << "Could not open config file\n";
  } else {
    std::string line;
    std::string graph_config;

    while (!file.eof()) {
      std::getline(file, line);

      std::stringstream str_stream{line};
      std::string token;
      std::vector<std::string> tokens;

      while (std::getline(str_stream, token, '=')) {
        tokens.emplace_back(token);
      }

      if (tokens[0] == "show_progress") {
        do_show_progress_ = std::stoi(tokens[1]);
      } else if (tokens[0] == "graph_path") {
        graph_path_ = tokens[1];
      } else if(tokens[0] == "is_symmetrical") {
        is_symmetrical_ = std::stoi(tokens[1]);
      } else if (tokens[0] == "graph_config") {
        graph_config = tokens[1];
      }
    }

    if (is_symmetrical_) {
      graph_ = new pea_tsp::SymmetricalGraph(graph_config);
    } else {
      graph_ = new pea_tsp::AsymmetricalGraph(graph_config);
    }
  }
}

std::vector<int> TspAlgoBase::CreateVerticesVector(const int vertices_count, const int start_point) {
  std::vector<int> vertices = {};
  vertices.reserve(vertices_count);

  for (auto i = 1; i <= vertices_count; ++i) {
    if (i == start_point) continue;
    vertices.emplace_back(i);
  }

  return vertices;
}

bool TspAlgoBase::IsPathTraversable(const std::vector<int> &path, Graph &graph) {
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