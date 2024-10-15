//
// Created by qwere on 16.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_RANDOM_TSPRANDOMPATH_H_
#define TSPFIRSTPART_TSPALGOBASE_RANDOM_TSPRANDOMPATH_H_

#include "../TspAlgoBase.h"

namespace pea_tsp::algo {

class TspRandomPath : public pea_tsp::algo::TspAlgoBase {
 public:
  TspRandomPath() = default;
  explicit TspRandomPath(const std::string &conf_path);

  std::vector<int> FindSolution() final;
  std::vector<int> FindSolution(Graph &graph) final;
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_RANDOM_TSPRANDOMPATH_H_
