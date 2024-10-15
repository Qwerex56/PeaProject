//
// Created by qwere on 07.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_
#define TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_

#include <vector>
#include <map>
#include "../Graph/Graph.h"
namespace pea_tsp::algo {

class TspAlgoBase {
 public:
  TspAlgoBase() = default;
  explicit TspAlgoBase(const std::string &conf_path);

  virtual std::vector<int> FindSolution() = 0;
  virtual std::vector<int> FindSolution(Graph &graph) = 0;

 protected:
  std::string graph_path_;
  bool do_show_progress_ = true;
  // Should be an enum
  bool is_symmetrical_ = false;

  Graph *graph_ = nullptr;

  static std::vector<int> CreateVerticesVector(int vertices_count, int start_point);

  // Test for all point connectivity
  static bool IsPathTraversable(const std::vector<int> &path, Graph &graph) ;
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_
