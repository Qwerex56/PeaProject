#include <iostream>

#include "./Graph/SymmetricalGraph.h"
#include "TspAlgobase/BruteForce/TspBruteForce.h"
#include "TspAlgobase/DfsBruteForce/DfsBruteForce.h"
#include "TspAlgobase/NearestNeighbour/TspNearestNeighbour.h"
#include "TspAlgobase/Random/TspRandomPath.h"
#include "TspAlgobase/TspBabDfs/TspBabDfs.h"

int main() {
  auto dfs_bb = pea_tsp::algo::TspBabDfs(R"(E:\C-Projects\PeaProject\config.txt)");

  auto solution = dfs_bb.FindSolution();

  return 0;
}
