#include <iostream>

#include "./Graph/SymmetricalGraph.h"
#include "TspAlgobase/BruteForce/TspBruteForce.h"
#include "TspAlgobase/DfsBruteForce/DfsBruteForce.h"
#include "TspAlgobase/NearestNeighbour/TspNearestNeighbour.h"
#include "TspAlgobase/Random/TspRandomPath.h"
#include "TspAlgobase/TspBabDfs/TspBabDfs.h"
#include "TspAlgobase/TspBreadthFirstSearch/TspBreadthFirstSearch.h"
#include "TspAlgobase/TspBestFirstSearch/TspBestFirstSearch.h"

int main() {
  const auto conf_path = R"(E:\C-Projects\PeaProject\config.txt)";

  std::cout << "BF1\n";
  pea_tsp::algo::TspBruteForce(conf_path).FindSolution();

  std::cout << "BF2\n";
  pea_tsp::algo::DfsBruteForce(conf_path).FindSolution();

  std::cout << "NN\n";
  pea_tsp::algo::TspNearestNeighbour(conf_path).FindSolution();

  std::cout << "RP\n";
  pea_tsp::algo::TspRandomPath(conf_path).FindSolution();

  std::cout << "BabBF\n";
  pea_tsp::algo::TspBabDfs(conf_path).FindSolution();

  std::cout << "BaBBfs\n";
  pea_tsp::algo::TspBreadthFirstSearch(conf_path).FindSolution();

  std::cout << "BaBBestFs\n";
  pea_tsp::algo::TspBestFirstSearch(conf_path).FindSolution();

  return 0;
}
