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

  virtual Graph &AddPoint(int point_id, int to_point_id, int weight) = 0;

  std::string GetName() const;
  std::string GetComment() const;
  int GetDimension() const;

  virtual std::tuple<int, std::vector<int>> GetPoint(const int &point_id) const = 0;
  int GetTravelWeight(int from_id, int to_id) const;
  int GetPossiblePathCount() const;
 protected:
  std::unordered_map<std::string, std::string> conf_;

  void SetName(const std::string &name);
  void SetComment(const std::string &comment);
  void SetDimension(int dimension);
  void SetDimension(const std::string &dimension);
};

} // pea_tsp

#endif //TSPFIRSTPART_GRAPH_H
