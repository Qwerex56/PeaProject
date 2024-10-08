//
// Created by qwere on 07.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_
#define TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_

#include <vector>
#include "../Graph/Graph.h"
namespace pea_tsp::algo {

class TspAlgoBase {
 public:
  virtual std::vector<int> FindSolution(const Graph &graph) = 0;

 protected:
  int upper_bound_ = 9999;
  int repeat_ = -1; // -1 = runs until best solution
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_
