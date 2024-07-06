#pragma once

#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees) {
    // TODO store the indegree for each vertex in the graph in the indegrees map
    for(auto i = graph.begin(); i != graph.end(); i++)// may need to do vertex = vertex->next
    {
        T vertex = i->first;
        indegrees[vertex] = 0;
    }

    T src_vertex;
    T dst_vertex;
    for(auto[src_vertex, adj_list]: graph)
    {
        for(auto[dst_vertex, weight]: adj_list)
        {
            indegrees[dst_vertex] += 1;
        }
    }
}
