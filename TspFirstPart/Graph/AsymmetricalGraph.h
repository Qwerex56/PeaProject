//
// Created by qwere on 03.10.2024.
//

#ifndef TSPFIRSTPART_ASYMMETRICALGRAPH_H
#define TSPFIRSTPART_ASYMMETRICALGRAPH_H

#include <map>
#include "Graph.h"

namespace pea_tsp {

class AsymmetricalGraph : public pea_tsp::Graph {
 public:
  AsymmetricalGraph() = default;
  explicit AsymmetricalGraph(const std::string &path);

  ~AsymmetricalGraph() override = default;

  Graph &AddPoint(int point_id, int to_point, int weight) final;

  [[nodiscard]] std::tuple<int, std::vector<int>> GetPoint(const int &point_id) const final;

  friend std::ostream &operator<<(std::ostream &os, AsymmetricalGraph &g);
 private:
  std::map<int, std::vector<int>> points;
};

} // pea_tsp

#endif //TSPFIRSTPART_ASYMMETRICALGRAPH_H
