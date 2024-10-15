//
// Created by qwere on 08.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_BRUTEFORCE_TSPBRUTEFORCE_H_
#define TSPFIRSTPART_TSPALGOBASE_BRUTEFORCE_TSPBRUTEFORCE_H_

#include "../TspAlgoBase.h"
namespace pea_tsp::algo {

class [[maybe_unused]] TspBruteForce : public TspAlgoBase {
 public:
  TspBruteForce() = default;
  [[maybe_unused]] explicit TspBruteForce(const std::string &conf_path);

  std::vector<int> FindSolution() final {
    if (!graph_) return {};

    return FindSolution(*graph_);
  }

  std::vector<int> FindSolution(Graph &graph) final;
};
} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_BRUTEFORCE_TSPBRUTEFORCE_H_
