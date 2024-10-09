//
// Created by qwere on 08.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_NEARESTNEIGHBOUR_TSPNEARESTNEIGHBOUR_H_
#define TSPFIRSTPART_TSPALGOBASE_NEARESTNEIGHBOUR_TSPNEARESTNEIGHBOUR_H_

#include "../TspAlgoBase.h"
namespace pea_tsp::algo {

class TspNearestNeighbour : public TspAlgoBase {
 public:
  std::vector<int> FindSolution(Graph &graph) final;

 protected:

 private:
  // returns id of the minimum element, not value
  static size_t MinElementId(const std::vector<int> &elements, const std::vector<int> &visited);
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_NEARESTNEIGHBOUR_TSPNEARESTNEIGHBOUR_H_
