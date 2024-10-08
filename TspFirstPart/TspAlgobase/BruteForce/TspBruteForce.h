//
// Created by qwere on 08.10.2024.
//

#ifndef TSPFIRSTPART_TSPALGOBASE_BRUTEFORCE_TSPBRUTEFORCE_H_
#define TSPFIRSTPART_TSPALGOBASE_BRUTEFORCE_TSPBRUTEFORCE_H_

#include "../TspAlgoBase.h"
namespace pea_tsp::algo {

class TspBruteForce : public TspAlgoBase {
 public:
  TspBruteForce() = default;

//  TspBruteForce(std::map<std::string, std::string> conf);
//  TspBruteForce(const std::string &confFilePath);

  std::vector<int> FindSolution(Graph &graph) final;

 private:
};
} // algo
// pea_tsp

#endif //TSPFIRSTPART_TSPALGOBASE_BRUTEFORCE_TSPBRUTEFORCE_H_
