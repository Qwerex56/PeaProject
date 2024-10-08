#include <iostream>

#include "./Graph/SymmetricalGraph.h"

int main() {
  auto graph = pea_tsp::SymmetricalGraph{R"(D:\dev\PeaProject\att48.tsp)"};

  graph.GetPoint(12);

  std::cout << graph;
  return 0;
}
