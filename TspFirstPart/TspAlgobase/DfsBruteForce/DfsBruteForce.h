//
// Created by qwere on 09.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_DFSBRUTEFORCE_DFSBRUTEFORCE_H_
#define TSPFIRSTPART_TSPALGOBASE_DFSBRUTEFORCE_DFSBRUTEFORCE_H_

#include "../TspAlgoBase.h"
namespace pea_tsp::algo {

class DfsBruteForce : public TspAlgoBase {
 public:
  DfsBruteForce() = default;
  explicit DfsBruteForce(const std::string &conf_path, const std::string &graph_conf_path = "");

  std::vector<int> FindSolution() final;
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_DFSBRUTEFORCE_DFSBRUTEFORCE_H_
