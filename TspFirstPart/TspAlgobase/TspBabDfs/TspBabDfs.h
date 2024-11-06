//
// Created by qwere on 04.11.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_TSPBABDFS_TSPBABDFS_H_
#define TSPFIRSTPART_TSPALGOBASE_TSPBABDFS_TSPBABDFS_H_

#include "../TspAlgoBase.h"
#include "../Random/TspRandomPath.h"
namespace pea_tsp::algo {

class TspBabDfs : public TspAlgoBase {
 public:
  TspBabDfs() = default;
  explicit TspBabDfs(const std::string &conf_path);

  std::vector<int> FindSolution() final;

 protected:
  TspRandomPath *bound_algo = nullptr;

  [[nodiscard]] int CalculateBound() const;
};

} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_TSPBABDFS_TSPBABDFS_H_
