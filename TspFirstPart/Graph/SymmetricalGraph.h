//
// Created by qwere on 03.10.2024.
//

#ifndef TSPFIRSTPART_SYMMETRICALGRAPH_H
#define TSPFIRSTPART_SYMMETRICALGRAPH_H

#include "Graph.h"

namespace pea_tsp {

    class SymmetricalGraph : public pea_tsp::Graph {
    public:
        Graph& AddPoint(int point_id, int to_point_id, int weight) override;
        Graph& RemovePoint(int point_id) override;

        Graph& ClearGraph() override;

        int GetDimension() override;
        std::tuple<int, std::vector<int>> GetPoint() override;
    private:
        virtual void ReadGraphFromFile(std::string path) override;
        virtual void ReadGraphFromFile(std::fstream file_path) override;
    };

} // pea_tsp

#endif //TSPFIRSTPART_SYMMETRICALGRAPH_H
