//
// Created by qwere on 07.10.2024.
//

#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

#include "TspAlgoBase.h"
#include "../Graph/SymmetricalGraph.h"
#include "../Graph/AsymmetricalGraph.h"

namespace pea_tsp::algo {
TspAlgoBase::TspAlgoBase(const std::string &conf_path, const std::string &graph_conf_path) {
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
      } else if (tokens[0] == "is_symmetrical") {
        is_symmetrical_ = std::stoi(tokens[1]);
      } else if (tokens[0] == "graph_config") {
        graph_config = tokens[1];
      } else if (tokens[0] == "max_work_time") {
        max_time = std::chrono::seconds{std::stoi(tokens[1])};
      } else if (tokens[0] == "optimal_solution") {
        optimal_solution_ = std::stoi(tokens[1]);
      }
    }

    if (!graph_conf_path.empty()) {
      graph_config = graph_conf_path;
    }

    if (is_symmetrical_) {
      graph_ = new pea_tsp::SymmetricalGraph(graph_path_);
    } else {
      std::cout << graph_path_;
      graph_ = new pea_tsp::AsymmetricalGraph(graph_path_);
    }
  }
}

std::vector<int> TspAlgoBase::CreateVerticesVector(const int vertices_count, const int start_point) {
  std::vector<int> vertices(vertices_count);
  std::iota(vertices.begin(), vertices.end(), 1);

  std::erase_if(vertices, [&start_point](const int &item) {
    return item == start_point;
  });

  return vertices;
}

bool TspAlgoBase::IsPathTraversable(const std::vector<int> &path) const {
  auto last = path.cbegin();

  return !std::any_of(path.cbegin() + 1, path.cend(), [&](const auto &item) {
    auto travel_weight = graph_->GetTravelWeight(*last, item);
    ++last;

    return travel_weight <= 0;
  });
}

void TspAlgoBase::SaveToFile(const std::vector<int> &path,
                             const int travel_weight,
                             double elapsed_seconds,
                             const std::string &algorithm) const {
  std::ofstream file(".\\TspResults.csv", std::fstream::app);

  for (const auto &node : path) file << node << " ";

  file << ";" << travel_weight << ";" << elapsed_seconds << ";" << best_found_solution << ";" << GetPercentDeviation()
       << ";" << algorithm << "\n";
}

int TspAlgoBase::GetPathWeight(const std::vector<int> &path) const {
  auto path_weight = 0;

  for (auto item = 0; item < path.size() - 1; ++item) {
    auto travel_weight = graph_->GetTravelWeight(path[item], path[item + 1]);

    path_weight += travel_weight;
  }

  return path_weight;
}

} // algo
// pea_tsp