//
// Created by qwere on 07.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_
#define TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_

#include <vector>
#include <map>
#include "../Graph/Graph.h"
namespace pea_tsp::algo {

class TspAlgoBase {
 public:
  virtual std::vector<int> FindSolution(Graph &graph) = 0;

 protected:
  std::map<std::string, std::string> conf_;

  int upper_bound_ = INT_MAX;
  int repeat_ = -1; // -1 = runs until best solution

  bool do_show_progress = true;
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_
