//
// Created by qwere on 09.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_DFSBRUTEFORCE_DFSBRUTEFORCE_H_
#define TSPFIRSTPART_TSPALGOBASE_DFSBRUTEFORCE_DFSBRUTEFORCE_H_

#include "../TspAlgoBase.h"
namespace pea_tsp::algo {

class DfsBruteForce : public TspAlgoBase {
 public:
  std::vector<int> FindSolution(Graph &graph) final;

 private:

};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_DFSBRUTEFORCE_DFSBRUTEFORCE_H_
