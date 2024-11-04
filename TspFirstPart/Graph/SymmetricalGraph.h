//
// Created by qwere on 03.10.2024.
//

#ifndef TSPFIRSTPART_SYMMETRICALGRAPH_H
#define TSPFIRSTPART_SYMMETRICALGRAPH_H

#include <map>

#include "Graph.h"

namespace pea_tsp {
class SymmetricalGraph final : public Graph {
 public:
  SymmetricalGraph() = default;
  explicit SymmetricalGraph(const std::string &path);

  ~SymmetricalGraph() override = default;

  Graph &AddPoint(int point_id, int coordinate_x, int coordinate_y) override;

  [[nodiscard]] std::tuple<int, std::vector<int> > GetPoint(const int &point_id) const override;

  friend std::ostream &operator<<(std::ostream &os, SymmetricalGraph &g);
 private:
  std::map<int, std::vector<int>> points;
};
} // pea_tsp

#endif //TSPFIRSTPART_SYMMETRICALGRAPH_H
