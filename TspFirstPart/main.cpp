#include <iostream>

#include "./Graph/SymmetricalGraph.h"
#include "TspAlgobase/BruteForce/TspBruteForce.h"
#include "TspAlgobase/DfsBruteForce/DfsBruteForce.h"

int main() {
  auto dfs_bb = pea_tsp::algo::DfsBruteForce(R"(E:\C-Projects\PeaProject\config.txt)");

  auto solution = dfs_bb.FindSolution();

  for (auto const &point : solution) {
    std::cout << point << " -> ";
  }
  std::cout << solution[0];

  return 0;
}
