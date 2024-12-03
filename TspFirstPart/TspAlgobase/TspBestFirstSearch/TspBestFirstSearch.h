//
// Created by qwere on 13.11.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_TSPBESTFIRSTSEARCH_TSPBESTFIRSTSEARCH_H_
#define TSPFIRSTPART_TSPALGOBASE_TSPBESTFIRSTSEARCH_TSPBESTFIRSTSEARCH_H_

#include "../TspAlgoBase.h"
#include "../NearestNeighbour/TspNearestNeighbour.h"
namespace pea_tsp::algo {

class TspBestFirstSearch : public TspAlgoBase {
 public:
  TspBestFirstSearch() = default;
  [[maybe_unused]] explicit TspBestFirstSearch(const std::string &conf_path, const std::string &graph_conf_path = "");

  std::vector<int> FindSolution() final;

 private:
  TspNearestNeighbour *bound_algo = nullptr;

  [[nodiscard]] int CalculateBound() const;
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_TSPBESTFIRSTSEARCH_TSPBESTFIRSTSEARCH_H_
