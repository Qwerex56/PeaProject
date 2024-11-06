//
// Created by qwere on 16.10.2024.
//

#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <fstream>

#include "TspRandomPath.h"

namespace pea_tsp::algo {

TspRandomPath::TspRandomPath(const std::string &conf_path) : TspAlgoBase(conf_path) {
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

      if (tokens[0] == "max_work_time") {
        max_time = std::chrono::seconds{std::stoi(tokens[1])};
      }
    }
  }
}

std::vector<int> TspRandomPath::FindSolution() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(1, graph_->GetDimension());

  const auto start_time{std::chrono::steady_clock::now()};
  auto current_time{std::chrono::steady_clock::now()};

  auto path = std::vector<int>(graph_->GetDimension());
  std::iota(path.begin(), path.end(), 1);
  auto tries = 0;

  auto min_travel_weight = INT_MAX;
  auto min_path = std::vector<int>();

  do {
    // Close path
    path.emplace_back(path[0]);

    if (!IsPathTraversable(path)) continue;
    ++tries;
    auto current_path_weight = GetPathWeight(path);

    if (current_path_weight < min_travel_weight) {
      min_travel_weight = current_path_weight;
      min_path = path;

      if (tries >= max_tries) break;
    }

    // delete duplicate vertex
    path.pop_back();
    std::shuffle(path.begin(), path.end(), gen);

    current_time = std::chrono::steady_clock::now();

    if (do_show_progress_
        && std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() % 5000 == 0) {
      std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count()
                << "s / " << max_time.count() << "s\n";
    }

  } while (std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() < max_time.count());

  const auto end{std::chrono::steady_clock::now()};
  const std::chrono::duration<double> elapsed_seconds{end - start_time};

  SaveToFile(min_path,
             min_travel_weight,
             elapsed_seconds.count(),
             "TspRand-result.csv");
  return min_path;
}

std::vector<int> TspRandomPath::FindSolutionWithTries(int tries) {
  auto save_conf_tries = max_tries;

  max_tries = tries;
  auto result = FindSolution();
  max_tries = save_conf_tries;

  return result;
}

} // algo
// pea_tsp