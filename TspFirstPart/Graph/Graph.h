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

enum class GraphConf {
  Name,
  Comment,
  Type,
  Dimension,
  EdgeWeightType,
};

enum class GraphType {
  TSP = 1 << 0,
  ATSP = 1 << 1,
  TOUR = 1 << 2,
  UNKNOWN = 1 << 31
};

class Graph {
 public:
  virtual ~Graph() = default;

  virtual Graph &AddPoint(int point_id, int to_point_id, int weight) = 0;
  virtual Graph &ClearGraph() = 0;

//  virtual Graph &RemovePoint(int point_id) = 0;

  std::string GetName();
  std::string GetComment();
  int GetDimension();

  virtual std::tuple<int, std::vector<int>> GetPoint(const int &point_id) = 0;

 protected:
  std::unordered_map<std::string, std::string> conf_;
  GraphType type_ = GraphType::UNKNOWN;

  void SetName(std::string name);
  void SetComment(std::string comment);
  void SetDimension(int dimension);
  void SetDimension(std::string dimension);
};

} // pea_tsp

#endif //TSPFIRSTPART_GRAPH_H
