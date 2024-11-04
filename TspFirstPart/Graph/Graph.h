//
// Created by qwere on 03.10.2024.
//

#ifndef TSPFIRSTPART_GRAPH_H
#define TSPFIRSTPART_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

namespace pea_tsp {

class Graph {
 public:
  virtual ~Graph() = default;

  virtual Graph &AddPoint(int, int, int) = 0;

  [[nodiscard]] std::string GetName() const;
  [[nodiscard]] std::string GetComment() const;
  [[nodiscard]] int GetDimension() const;

  [[nodiscard]] virtual std::tuple<int, std::vector<int>> GetPoint(const int &point_id) const = 0;
  [[nodiscard]] int GetTravelWeight(int from_id, int to_id) const;
  [[nodiscard]] int GetPossiblePathCount() const;

 protected:

  std::string name_;
  std::string comment_;
  int dimension_;
};

} // pea_tsp

#endif //TSPFIRSTPART_GRAPH_H
