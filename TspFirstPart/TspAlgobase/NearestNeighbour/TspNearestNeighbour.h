//
// Created by qwere on 08.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_NEARESTNEIGHBOUR_TSPNEARESTNEIGHBOUR_H_
#define TSPFIRSTPART_TSPALGOBASE_NEARESTNEIGHBOUR_TSPNEARESTNEIGHBOUR_H_

#include "../TspAlgoBase.h"

namespace pea_tsp::algo {

class [[maybe_unused]] TspNearestNeighbour : public TspAlgoBase {
 public:
  TspNearestNeighbour() = default;
  [[maybe_unused]] explicit TspNearestNeighbour(const std::string &conf_path, bool create_log = true);

  std::vector<int> FindSolution() final;

 private:
  bool do_crete_log = true;

  // returns id of the minimum element, not value
  [[maybe_unused]] static size_t MinElementId(const std::vector<int> &elements, const std::vector<int> &visited);

  // returns ids of the minimum elements
  static std::vector<int> MinElementIds(const std::vector<int> &elements, const std::vector<int> &visited);
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_NEARESTNEIGHBOUR_TSPNEARESTNEIGHBOUR_H_
