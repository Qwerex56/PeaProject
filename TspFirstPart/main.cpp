#include <iostream>

#include "./Graph/SymmetricalGraph.h"
#include "Graph/AsymmetricalGraph.h"
#include "TspAlgobase/BruteForce/TspBruteForce.h"
#include "TspAlgobase/NearestNeighbour/TspNearestNeighbour.h"

int main() {
  auto graph = pea_tsp::SymmetricalGraph{R"(E:\C-Projects\PeaProject\att4.tsp)"};
  auto agraph = pea_tsp::AsymmetricalGraph(R"(E:\C-Projects\PeaProject\br4.atsp)");

  auto bf = pea_tsp::algo::TspBruteForce();
  auto nn = pea_tsp::algo::TspNearestNeighbour();

  auto solution = nn.FindSolution(agraph);

  for (auto const &point : solution) {
    std::cout << point << " -> ";
  }
  std::cout << solution[0];

  return 0;
}
