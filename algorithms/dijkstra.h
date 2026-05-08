// Copyright 2026 Alewa8131

#pragma once
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include "../lib_graph_types/graph_types.h"

struct DijkstraResult {
    TVector<int> dist;
    TVector<int> parent;
};

template <class T>
DijkstraResult dijkstra(T start_val, Graph<T>& graph) {
    auto& lists = graph.get_lists();
    size_t n = lists.get_vertices_count();

    Vertex<T>* start_vertex = const_cast<AdjacencyLists<T>&>(lists).find_vertex(start_val);

    DijkstraResult res;
    if (!start_vertex) {
        return res;
    }
    size_t start_idx = start_vertex->_index;

    TVector<bool> visited;

    for (size_t i = 0; i < n; ++i) {
        res.dist.push_back(INT_INF);
        res.parent.push_back(-1);
        visited.push_back(false);
    }

    res.dist[start_idx] = 0;

    for (size_t count = 0; count < n; ++count) {
        int u = -1;

        for (size_t v = 0; v < n; ++v) {
            if (!visited[v] && (u == -1 || res.dist[v] < res.dist[u])) {
                u = v;
            }
        }

        if (u == -1 || res.dist[u] == INT_INF) break;
        visited[u] = true;

        auto* curr = lists.get_edges_list(u).head();

        if (curr) curr = curr->_next;

        while (curr != nullptr) {
            const Edge<T>& e = curr->_value;
            size_t to_idx = e._target->_index;
            int weight = e._weight;

            if (res.dist[u] != INT_INF && res.dist[u] + weight < res.dist[to_idx]) {
                res.dist[to_idx] = res.dist[u] + weight;
                res.parent[to_idx] = u;
            }
            curr = curr->_next;
        }
    }

    return res;
}
