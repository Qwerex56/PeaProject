//
// Created by qwere on 03.10.2024.
//

#ifndef TSPFIRSTPART_GRAPH_H
#define TSPFIRSTPART_GRAPH_H

#include <string>
#include <vector>

namespace pea_tsp {

    class Graph {
    public:
        virtual ~Graph() = 0;

        virtual Graph& AddPoint(int point_id, int to_point_id, int weight) = 0;
        virtual Graph& RemovePoint(int point_id) = 0;

        virtual Graph& ClearGraph() = 0;

        std::string GetName();
        std::string GetComment();
        virtual int GetDimension() = 0;
        virtual std::tuple<int, std::vector<int>> GetPoint() = 0;

    protected:
        std::string name;
        std::string comment;

    private:
        virtual void ReadGraphFromFile(std::string path) = 0;
        virtual void ReadGraphFromFile(std::fstream file_path) = 0;
    };

} // pea_tsp

#endif //TSPFIRSTPART_GRAPH_H
