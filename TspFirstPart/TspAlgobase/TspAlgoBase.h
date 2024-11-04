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

 protected:
  std::string graph_path_;
  bool do_show_progress_ = true;
  bool is_symmetrical_ = false;
  int optimal_solution_ = -1;
  Graph *graph_ = nullptr;

  int best_found_solution = -1;

  [[nodiscard]] inline int GetResultDeviation() const noexcept {
    return abs(optimal_solution_ - best_found_solution);
  }

  [[nodiscard]] inline float GetPercentDeviation() const noexcept {
    return ((float) GetResultDeviation() / (float) optimal_solution_) * 100.0f;
  }

  static std::vector<int> CreateVerticesVector(int vertices_count, int start_point);

  // Test for all point connectivity
  [[nodiscard]] bool IsPathTraversable(const std::vector<int> &path) const;
  [[nodiscard]] int GetPathWeight(const std::vector<int> &path) const;

  void SaveToFile(const std::vector<int> &path,
                         int travel_weight,
                         double elapsed_seconds,
                         const std::string &file_name = "Result.txt") const;
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_TSPALGOBASE_H_
