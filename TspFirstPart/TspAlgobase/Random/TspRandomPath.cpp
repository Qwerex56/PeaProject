//
// Created by qwere on 16.10.2024.
//

#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <fstream>

#include "TspRandomPath.h"

namespace pea_tsp::algo {

TspRandomPath::TspRandomPath(const std::string &conf_path, const std::string &graph_conf_path) : TspAlgoBase(conf_path, graph_conf_path) { }

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

  auto found_optimal_solution = min_travel_weight == optimal_solution_;

  do {
    // Close path
    path.emplace_back(path[0]);

    if (!IsPathTraversable(path)) {
      path.pop_back();
      std::shuffle(path.begin(), path.end(), gen);
      continue;
    }

    ++tries;
    auto current_path_weight = GetPathWeight(path);

    if (current_path_weight < min_travel_weight) {
      min_travel_weight = current_path_weight;
      min_path = path;

      found_optimal_solution = min_travel_weight == optimal_solution_;
    }

    // delete duplicate vertex
    path.pop_back();
    std::shuffle(path.begin(), path.end(), gen);

    current_time = std::chrono::steady_clock::now();

    if (found_optimal_solution) {
      std::cout << "Found optimal solution\n";
      break;
    }

    if (do_show_progress_
        && std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() % 5000 == 0) {
      std::cout << "Elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count()
                << "s / " << max_time.count() << "s\n";
    }

  } while (std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() < max_time.count());

  const auto end{std::chrono::steady_clock::now()};
  const std::chrono::duration<double> elapsed_seconds{end - start_time};

  if (min_path.empty()) {
    best_found_solution = -1;
  } else best_found_solution = GetPathWeight(min_path);

  SaveToFile(min_path,
             min_travel_weight,
             elapsed_seconds.count(),
             "TspRand");
  return min_path;
}

} // algo
// pea_tsp