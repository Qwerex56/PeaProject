#include <iostream>

#include "./Graph/SymmetricalGraph.h"
#include "TspAlgobase/DfsBruteForce/DfsBruteForce.h"
#include "TspAlgobase/NearestNeighbour/TspNearestNeighbour.h"
#include "TspAlgobase/Random/TspRandomPath.h"
#include "TspAlgobase/TspBabDfs/TspBabDfs.h"
#include "TspAlgobase/TspBreadthFirstSearch/TspBreadthFirstSearch.h"
#include "TspAlgobase/TspBestFirstSearch/TspBestFirstSearch.h"

int main() {
  const auto conf_path = R"(.\config.txt)";

  std::cout << "Starting algorithm\n";
  pea_tsp::algo::TspBestFirstSearch(conf_path).FindSolution();

  return 0;
}
