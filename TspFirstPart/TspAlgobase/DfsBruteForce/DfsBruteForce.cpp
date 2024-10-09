//
// Created by qwere on 09.10.2024.
//

#include <stack>
#include <algorithm>
#include "DfsBruteForce.h"

namespace pea_tsp::algo {
std::vector<int> DfsBruteForce::FindSolution(Graph &graph) {

  for (auto start_point = 1; start_point <= graph.GetDimension(); ++start_point) {
    std::stack<int> path_stack{};

    std::vector<int> current_path{start_point};
    int current_path_weight = 0;

    path_stack.push(start_point);

    while (!path_stack.empty()) {
      auto current_point = path_stack.top();
      path_stack.pop();

      if (current_path.size() > 1) {
        auto travel_weight = std::get<1>(graph.GetPoint(current_path.back()))[current_point];
        current_path_weight += travel_weight;
      }

      auto neighbours = std::get<1>(graph.GetPoint(current_point));

      // erase vertex from neighbours if it was visited
      neighbours.erase(std::remove_if(neighbours.begin(), neighbours.end(),
                                      [&current_path](auto const &item) -> bool {
                                        auto result = std::any_of(current_path.begin(),
                                                                  current_path.end(),
                                                                  [&item](const auto &i) {
                                                                    return i == item;
                                                                  });

                                        return result;
                                      }), neighbours.end());

      for (auto const &neighbour : neighbours) {
        path_stack.push(neighbour);
      }
    }
  }

  return std::vector<int>();
}
} // algo
// pea_tsp