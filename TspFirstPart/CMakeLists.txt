cmake_minimum_required(VERSION 3.29)
project(TspFirstPart)

set(CMAKE_CXX_STANDARD 23)

add_executable(TspFirstPart main.cpp
        Graph/Graph.cpp
        Graph/Graph.h
        Graph/SymmetricalGraph.cpp
        Graph/SymmetricalGraph.h
        Graph/AsymmetricalGraph.cpp
        Graph/AsymmetricalGraph.h
        TspAlgobase/TspAlgoBase.cpp
        TspAlgobase/TspAlgoBase.h
        TspAlgobase/NearestNeighbour/TspNearestNeighbour.cpp
        TspAlgobase/NearestNeighbour/TspNearestNeighbour.h
        TspAlgobase/DfsBruteForce/DfsBruteForce.cpp
        TspAlgobase/DfsBruteForce/DfsBruteForce.h
        TspAlgobase/Random/TspRandomPath.cpp
        TspAlgobase/Random/TspRandomPath.h
        TspAlgobase/TspBabDfs/TspBabDfs.cpp
        TspAlgobase/TspBabDfs/TspBabDfs.h
        TspAlgobase/TspBreadthFirstSearch/TspBreadthFirstSearch.cpp
        TspAlgobase/TspBreadthFirstSearch/TspBreadthFirstSearch.h
        TspAlgobase/TspBestFirstSearch/TspBestFirstSearch.cpp
        TspAlgobase/TspBestFirstSearch/TspBestFirstSearch.h)
