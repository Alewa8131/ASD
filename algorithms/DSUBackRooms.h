// Copyright 2025 Alewa8131

#pragma once
#include <iostream>
#include <cstdlib>
#include "../lib_dsu/dsu.h"
#include "../lib_matrix/matrix.h"
#include "../lib_graph_types/graph_types.h"
#include "../algorithms/dijkstra.h"

Matrix<bool> generate(int S, int F, int N, int M) {
    if (S == F) throw std::out_of_range("Start and finish cannot be in the same place");
    if (S < 1 || S > N * M ||
        (S > N && S <= N * (M - 1) && (S - 1) % N != 0 && S % N != 0)) {
        throw std::out_of_range("Start should be at the outer wall of the maze");
    }
    if (F < 1 || F > N * M ||
        (F > N && F <= N * (M - 1) && (F - 1) % N != 0 && F % N != 0)) {
        throw std::out_of_range("Finish should be at the outer wall of the maze");
    }

    int rows = 2 * N + 1;
    int cols = 2 * M + 1;

    Matrix<bool> lab(rows, cols);

    // всё заполнено
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            lab[i][j] = true;

    // открываем комнаты
    for (int r = 0; r < N; r++)
        for (int c = 0; c < M; c++)
            lab[2 * r + 1][2 * c + 1] = false;

    DSU dsu(N * M);

    int connected = 1;

    while (connected < N * M) {

        int cell = rand() % (N * M);

        int r = cell / M;
        int c = cell % M;

        int dir = rand() % 2;

        if (dir == 0 && c + 1 < M) {  // вправо

            int neigh = cell + 1;

            if (dsu.find(cell) != dsu.find(neigh)) {
                dsu.uni0n(cell, neigh);
                lab[2 * r + 1][2 * c + 2] = false;
                connected++;
            }
        }

        if (dir == 1 && r + 1 < N) {  // вниз

            int neigh = cell + M;

            if (dsu.find(cell) != dsu.find(neigh)) {
                dsu.uni0n(cell, neigh);
                lab[2 * r + 2][2 * c + 1] = false;
                connected++;
            }
        }
    }

    // вход
    int sr = (S - 1) / M;
    int sc = (S - 1) % M;

    if (sr == 0) lab[0][2 * sc + 1] = false;
    else if (sr == N - 1) lab[2 * N][2 * sc + 1] = false;
    else if (sc == 0) lab[2 * sr + 1][0] = false;
    else if (sc == M - 1) lab[2 * sr + 1][2 * M] = false;

    // выход
    int fr = (F - 1) / M;
    int fc = (F - 1) % M;

    if (fr == 0) lab[0][2 * fc + 1] = false;
    else if (fr == N - 1) lab[2 * N][2 * fc + 1] = false;
    else if (fc == 0) lab[2 * fr + 1][0] = false;
    else if (fc == M - 1) lab[2 * fr + 1][2 * M] = false;

    return lab;
}

int pos_to_idx(int r, int c, int cols) {
    return r * cols + c;
}

void print_way(Matrix<bool>& lab) {
    int rows = lab.get_N();
    int cols = lab.get_M();
    Graph<int> maze_graph(false, true);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (lab[r][c] == false) {
                int u = pos_to_idx(r, c, cols);

                int dr[] = { 0, 1 };
                int dc[] = { 1, 0 };
                for (int i = 0; i < 2; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr < rows && nc < cols && lab[nr][nc] == false) {
                        int v = pos_to_idx(nr, nc, cols);
                        maze_graph.add_edge(u, v, 1);
                    }
                }
            }
        }
    }

    int start_val = -1, finish_val = -1;

    for (int r = 0; r < rows; ++r) {
        if (!lab[r][0]) {
            if (start_val == -1) start_val = pos_to_idx(r, 0, cols);
            else if (start_val != pos_to_idx(r, 0, cols)) finish_val = pos_to_idx(r, 0, cols);
        }
        if (!lab[r][cols - 1]) {
            if (start_val == -1) start_val = pos_to_idx(r, cols - 1, cols);
            else if (start_val != pos_to_idx(r, cols - 1, cols)) finish_val = pos_to_idx(r, cols - 1, cols);
        }
    }
    for (int c = 0; c < cols; ++c) {
        if (!lab[0][c]) {
            if (start_val == -1) start_val = pos_to_idx(0, c, cols);
            else if (start_val != pos_to_idx(0, c, cols)) finish_val = pos_to_idx(0, c, cols);
        }
        if (!lab[rows - 1][c]) {
            if (start_val == -1) start_val = pos_to_idx(rows - 1, c, cols);
            else if (start_val != pos_to_idx(rows - 1, c, cols)) finish_val = pos_to_idx(rows - 1, c, cols);
        }
    }


    DijkstraResult res = dijkstra<int>(start_val, maze_graph);
    auto& lists = maze_graph.get_lists();

    Vertex<int>* start_vertex = const_cast<AdjacencyLists<int>&>(lists).find_vertex(start_val);
    Vertex<int>* finish_vertex = const_cast<AdjacencyLists<int>&>(lists).find_vertex(finish_val);

    if (!start_vertex || !finish_vertex || res.dist[finish_vertex->_index] == INT_INF) {
        std::cout << "No path found!" << std::endl;
        return;
    }

    TVector<int> path_values;
    int curr_idx = finish_vertex->_index;
    while (curr_idx != -1) {
        int val = lists.get_vertex_by_idx(curr_idx)->_value;
        path_values.push_back(val);
        curr_idx = res.parent[curr_idx];
    }

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            bool is_path = false;
            int idx = pos_to_idx(r, c, cols);

            for (size_t i = 0; i < path_values.size(); ++i) {
                if (path_values[i] == idx) {
                    is_path = true;
                    break;
                }
            }

            if (is_path) std::cout << "^";
            else if (lab[r][c]) std::cout << "0";
            else std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void print(Matrix<bool> lab) {
    for (int i = 0; i < lab.get_N(); i++) {
        for (int j = 0; j < lab.get_M(); j++) {

            if (lab[i][j])
                std::cout << "0";
            else
                std::cout << " ";
        }
        std::cout << "\n";
    }
}
