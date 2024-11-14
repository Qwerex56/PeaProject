//
// Created by qwere on 12.11.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_TSPBREADTHFIRSTSEARCH_TSPBREADTHFIRSTSEARCH_H_
#define TSPFIRSTPART_TSPALGOBASE_TSPBREADTHFIRSTSEARCH_TSPBREADTHFIRSTSEARCH_H_

#include "../TspAlgoBase.h"
#include "../NearestNeighbour/TspNearestNeighbour.h"

namespace pea_tsp::algo {

class TspBreadthFirstSearch : public TspAlgoBase {
 public:
  TspBreadthFirstSearch() = default;
  [[maybe_unused]] explicit TspBreadthFirstSearch(const std::string &conf_path);

  std::vector<int> FindSolution() final;

 private:
  TspNearestNeighbour *bound_algo = nullptr;

  [[nodiscard]] int CalculateBound() const;
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_TSPBREADTHFIRSTSEARCH_TSPBREADTHFIRSTSEARCH_H_
