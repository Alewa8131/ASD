// Copyright 2025 Alewa8131

#ifndef LIB_DSU_DSU_H_
#define LIB_DSU_DSU_H_
#pragma once
#include <stdexcept>

class DSU {
    int* _parent, *_rank; 
    size_t _size;
public:
    DSU(size_t size);
    ~DSU();
    void uni0n(int x, int y);
    int find(int x);
    int find_rec(int x);
};

DSU::DSU(size_t size) : _size(size) {
    if (size == 0) throw std::invalid_argument("Size of DSU cannot be zero.");
    _parent = new int[size];
    _rank = new int[size];

    for (size_t i = 0; i < size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

DSU::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

void DSU::uni0n(int x, int y) {
    if (x == y) return;
    if (x >= _size || x < 0 || y >= _size || y < 0) {
        throw std::out_of_range("Union arguments out of bounds size.");
    }

    int parent_x = find(x);
    int parent_y = find(y);
    if (parent_x == parent_y) return;

    if (_rank[parent_x] < _rank[parent_y]) {
        _parent[parent_x] = parent_y;
    } else {
        _parent[parent_y] = parent_x;

        if (_rank[parent_x] == _rank[parent_y]) {
            _rank[parent_x]++;
        }
    }

}

int DSU::find_rec(int x) {
    if (_parent[x] == x) return x;
    return _parent[x] = find_rec(_parent[x]);
}

int DSU::find(int x) {
    if (x >= _size || x < 0) {
        throw std::out_of_range("Find argument out of bounds size.");
    }

    int root = x;
    while (root != _parent[root]) {
        root = _parent[root];
    }

    // Убираем посредников
    while (x != root) {
        int next = _parent[x];
        _parent[x] = root;
        x = next;
    }

    return root;
}

template <int R, int C>
int count_islands(int(&grid)[R][C]) {
    DSU dsu(R * C);

    // Объединяем острова
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] != 1) continue;

            int cur = r * C + c;

            // ->
            if (c + 1 < C && grid[r][c + 1] == 1) {
                dsu.uni0n(cur, r * C + (c + 1));
            }

            // v
            if (r + 1 < R && grid[r + 1][c] == 1) {
                dsu.uni0n(cur, (r + 1) * C + c);
            }
        }
    }

    // Считаем объединения
    int count = 0;

    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == 1) {
                int root = dsu.find(r * C + c);
                if (root == r * C + c) {
                    count++;
                }
            }
        }
    }

    return count;
}

#endif LIB_DSU_DSU_H_
