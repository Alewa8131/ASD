// Copyright 2026 Alewa8131

#ifndef LIB_GRAPH_TYPES_GRAPH_TYPES_H_
#define LIB_GRAPH_TYPES_GRAPH_TYPES_H_
#pragma once

#include <utility>
#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include "../lib_matrix/matrix.h"

const int INT_INF = 2147483647;

template <class T>
struct Vertex {
    T _value;
    size_t _index;

    Vertex(T val, size_t idx) : _value(val), _index(idx) {}

    bool operator==(const Vertex& other) const {
        return _index == other._index;
    }
};

template <class T>
struct Edge {
    Vertex<T>* _target;
    int _weight;

    Edge(Vertex<T>* t, int w = 0) : _target(t), _weight(w) {}
};


template <class T>
class AdjacencyLists {
    TVector<Vertex<T>*> _vertices;
    TVector<List<Edge<T>>> _data;

    bool _is_oriented;
    bool _is_weighted;

public:
    AdjacencyLists(bool oriented = false, bool weighted = false);
    AdjacencyLists(TVector<std::pair<std::pair<T, T>, size_t>> init_data, 
        bool oriented = false, bool weighted = false);
    ~AdjacencyLists();

    size_t get_vertices_count() const;
    const List<Edge<T>>& get_edges_list(size_t idx) const;
    Vertex<T>* get_vertex_by_idx(size_t idx) const;
    Vertex<T>* find_vertex(T val);

    void add_edge(T from, T to, int weight = 1);
    void delete_edge(T v1, T v2);
    void delete_vertex(T v);
    void print();

protected:
    Vertex<T>* find_main(T val);
    Vertex<T>* get_or_create(T val);
};

template<class T>
AdjacencyLists<T>::
AdjacencyLists(bool oriented, bool weighted)
    : _is_oriented(oriented), _is_weighted(weighted) {}

template<class T>
AdjacencyLists<T>::
AdjacencyLists(TVector<std::pair<std::pair<T, T>, size_t>> init_data,
    bool oriented, bool weighted)
    : _is_oriented(oriented), _is_weighted(weighted) {
    for (size_t i = 0; i < init_data.size(); ++i) {
        add_edge(init_data[i].first.first, init_data[i].first.second, 
            init_data[i].second);
    }
}

template<class T>
AdjacencyLists<T>::
~AdjacencyLists() {
    for (size_t i = 0; i < _vertices.size(); ++i) {
        delete _vertices[i];
    }
}

template<class T>
size_t AdjacencyLists<T>::
get_vertices_count() const {
    return _vertices.size();
}

template<class T>
const List<Edge<T>>& AdjacencyLists<T>::
get_edges_list(size_t idx) const {
    return _data[idx];
}

template<class T>
Vertex<T>* AdjacencyLists<T>::
get_vertex_by_idx(size_t idx) const {
    return _vertices[idx];
}

template<class T>
Vertex<T>* AdjacencyLists<T>::
find_vertex(T val) {
    return find_main(val);
}


template<class T>
void AdjacencyLists<T>::
add_edge(T from, T to, int weight) {
    Vertex<T>* main1 = get_or_create(from);
    Vertex<T>* main2 = get_or_create(to);

    if (!main1 || !main2) return;

    int actual_weight = _is_weighted ? weight : 1;

    // edge from -> to
    _data[main1->_index].push_back(Edge<T>(main2, actual_weight));

    // edge to -> from
    if (!_is_oriented) {
        _data[main2->_index].push_back(Edge<T>(main1, actual_weight));
    }
}

template<class T>
void AdjacencyLists<T>::
delete_edge(T v1, T v2) {
    Vertex<T>* main1 = find_main(v1);
    Vertex<T>* main2 = find_main(v2);
    if (!main1 || !main2) return;

    // del from list v1 -> v2
    auto* curr = _data[main1->_index].head();
    auto* prev = curr;
    if (curr) curr = curr->_next;

    while (curr != nullptr) {
        if (curr->_value._target == main2) {
            prev->_next = curr->_next;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->_next;
    }

    // del from list v2 -> v1
    if (!_is_oriented) {
        curr = _data[main2->_index].head();
        prev = curr;
        if (curr) curr = curr->_next;

        while (curr != nullptr) {
            if (curr->_value._target == main1) {
                prev->_next = curr->_next;
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->_next;
        }
    }
}

template<class T>
void AdjacencyLists<T>::
delete_vertex(T v) {
    Vertex<T>* target_main = find_main(v);
    if (!target_main) return;

    size_t target_idx = target_main->_index;
    size_t last_idx = _vertices.size() - 1;

    // clear all targets
    for (size_t i = 0; i < _data.size(); ++i) {
        auto* curr = _data[i].head();
        auto* prev = curr;
        if (curr) curr = curr->_next;

        while (curr != nullptr) {
            if (curr->_value._target == target_main) {
                prev->_next = curr->_next;
                auto* to_delete = curr;
                curr = curr->_next;
                delete to_delete;
            } else {
                prev = curr;
                curr = curr->_next;
            }
        }
    }

    // Swap and Pop
    if (target_idx != last_idx) {
        delete _vertices[target_idx];

        _vertices[target_idx] = _vertices[last_idx];

        _vertices[target_idx]->_index = target_idx;

        _data[target_idx] = _data[last_idx];
    }
    else {
        delete _vertices[target_idx];
    }

    _vertices.pop_back();
    _data.pop_back();
}

template<class T>
void AdjacencyLists<T>::
print() {
    for (size_t i = 0; i < _data.size(); ++i) {
        auto* curr = _data[i].head();
        if (curr) {
            std::cout << "idx:" << curr->_value._target->_index << " | " << curr->_value._target->_value;
            curr = curr->_next;
        }
        while (curr != nullptr) {
            std::cout << " -> (" << curr->_value._target->_value << ", w: " << curr->_value._weight << ")";
            curr = curr->_next;
        }
        std::cout << std::endl;
    }
}


template<class T>
Vertex<T>* AdjacencyLists<T>::
find_main(T val) {
    for (size_t i = 0; i < _vertices.size(); ++i) {
        if (_vertices[i]->_value == val) {
            return _vertices[i];
        }
    }
    return nullptr;
}

template<class T>
Vertex<T>* AdjacencyLists<T>::
get_or_create(T val) {
    Vertex<T>* main = find_main(val);
    if (main != nullptr) return main;

    size_t new_idx = _vertices.size();
    main = new Vertex<T>(val, new_idx);
    _vertices.push_back(main);

    List<Edge<T>> new_list;

    new_list.push_back(Edge<T>(main, 0));
    _data.push_back(new_list);

    return main;
}



template <class T>
class AdjacencyMatrix {
    TVector<Vertex<T>*> _vertices;
    Matrix<int> _matrix;

    bool _is_oriented;
    bool _is_weighted;

public:
    AdjacencyMatrix(bool oriented = false, bool weighted = false);
    AdjacencyMatrix(TVector<std::pair<std::pair<T, T>, size_t>> init_data,
        bool oriented = false, bool weighted = false);
    ~AdjacencyMatrix();

    void add_edge(T from, T to, int weight = 1);
    void delete_edge(T v1, T v2);
    void delete_vertex(T v);
    void print();

protected:
    Vertex<T>* find_main(T val);
    Vertex<T>* get_or_create(T val);
};

template<class T>
AdjacencyMatrix<T>::
AdjacencyMatrix(bool oriented, bool weighted)
    : _is_oriented(oriented), _is_weighted(weighted), _matrix(0, 0) {}

template<class T>
AdjacencyMatrix<T>::
AdjacencyMatrix(TVector<std::pair<std::pair<T, T>, size_t>> init_data, 
    bool oriented, bool weighted)
    : _is_oriented(oriented), _is_weighted(weighted), _matrix(0, 0) {

    for (size_t i = 0; i < init_data.size(); ++i) {
        get_or_create(init_data[i].first.first);
        get_or_create(init_data[i].first.second);
    }

    size_t n = _vertices.size();
    _matrix = Matrix<int>(n, n);
    int default_val = _is_weighted ? INT_INF : 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            _matrix[i][j] = (i == j) ? 0 : default_val;
        }
    }

    for (size_t i = 0; i < init_data.size(); ++i) {
        add_edge(init_data[i].first.first, init_data[i].first.second, init_data[i].second);
    }
}

template<class T>
AdjacencyMatrix<T>::
~AdjacencyMatrix() {
    for (size_t i = 0; i < _vertices.size(); ++i) {
        delete _vertices[i];
    }
}

template<class T>
void AdjacencyMatrix<T>::
add_edge(T from, T to, int weight) {
    Vertex<T>* main1 = find_main(from);
    Vertex<T>* main2 = find_main(to);

    if (!main1 || !main2) return;

    int actual_weight = _is_weighted ? weight : 1;

    // edge from -> to
    _matrix[main1->_index][main2->_index] = actual_weight;

    // edge to -> from
    if (!_is_oriented) {
        _matrix[main2->_index][main1->_index] = actual_weight;
    }
}

template<class T>
void AdjacencyMatrix<T>::
delete_edge(T v1, T v2) {
    Vertex<T>* main1 = find_main(v1);
    Vertex<T>* main2 = find_main(v2);
    if (!main1 || !main2) return;

    int empty_val = _is_weighted ? INT_INF : 0;

    if (_matrix[main1->_index][main2->_index] != empty_val) {
        _matrix[main1->_index][main2->_index] = empty_val;
    }

    if (!_is_oriented && _matrix[main2->_index][main1->_index] != empty_val) {
        _matrix[main2->_index][main1->_index] = empty_val;
    }
}

template<class T>
void AdjacencyMatrix<T>::
delete_vertex(T v) {
    Vertex<T>* target_main = find_main(v);
    if (!target_main) return;

    size_t idx = target_main->_index;
    int empty_val = _is_weighted ? INT_INF : 0;

    // clear all targets
    for (size_t i = 0; i < _vertices.size(); ++i) {
        _matrix[idx][i] = (i == idx) ? 0 : empty_val;
        _matrix[i][idx] = (i == idx) ? 0 : empty_val;
    }
}

template<class T>
void AdjacencyMatrix<T>::
print() {
    std::cout << "   ";
    for (size_t i = 0; i < _vertices.size(); ++i) {
        std::cout << _vertices[i]->_value << " ";
    }
    std::cout << "\n";

    for (size_t i = 0; i < _vertices.size(); ++i) {
        std::cout << _vertices[i]->_value << " ";
        for (size_t j = 0; j < _vertices.size(); ++j) {
            if (_matrix[i][j] == INT_INF) {
                std::cout << " & ";
            }
            else {
                std::cout << " " << _matrix[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}


template<class T>
Vertex<T>* AdjacencyMatrix<T>::
find_main(T val) {
    for (size_t i = 0; i < _vertices.size(); ++i) {
        if (_vertices[i]->_value == val) {
            return _vertices[i];
        }
    }
    return nullptr;
}

template<class T>
Vertex<T>* AdjacencyMatrix<T>::
get_or_create(T val) {
    Vertex<T>* main = find_main(val);
    if (main != nullptr) return main;

    size_t new_idx = _vertices.size();
    main = new Vertex<T>(val, new_idx);
    _vertices.push_back(main);
    return main;
}



template <class T>
class Graph {
    AdjacencyLists<T> _adj_lists;
    AdjacencyMatrix<T> _adj_matrix;

public:
    Graph(bool oriented = false, bool weighted = false);
    Graph(TVector<std::pair<std::pair<T, T>, size_t>> init_data,
        bool oriented = false, bool weighted = false);
    ~Graph() = default;

    void add_edge(T from, T to, int weight = 1);
    void delete_edge(T v1, T v2);
    void delete_vertex(T v);
    void print();

    const AdjacencyLists<T>& get_lists() const;
    const AdjacencyMatrix<T>& get_matrix() const;
};

template <class T>
Graph<T>::
Graph(bool oriented, bool weighted)
    : _adj_lists(oriented, weighted), _adj_matrix(oriented, weighted) {}

template <class T>
Graph<T>::
Graph(TVector<std::pair<std::pair<T, T>, size_t>> init_data,
    bool oriented, bool weighted)
    : _adj_lists(init_data, oriented, weighted),
    _adj_matrix(init_data, oriented, weighted) {}

template <class T>
void Graph<T>::
add_edge(T from, T to, int weight) {
    _adj_lists.add_edge(from, to, weight);
    _adj_matrix.add_edge(from, to, weight);
}

template <class T>
void Graph<T>::
delete_edge(T v1, T v2) {
    _adj_lists.delete_edge(v1, v2);
    _adj_matrix.delete_edge(v1, v2);
}

template <class T>
void Graph<T>::
delete_vertex(T v) {
    _adj_lists.delete_vertex(v);
    _adj_matrix.delete_vertex(v);
}

template <class T>
void Graph<T>::
print() {
    std::cout << "--- Adjacency Lists Representation ---\n";
    _adj_lists.print();
    std::cout << "\n--- Adjacency Matrix Representation ---\n";
    _adj_matrix.print();
    std::cout << "---------------------------------------\n";
}


template<class T>
const AdjacencyLists<T>& Graph<T>::
get_lists() const { return _adj_lists; }

template <class T>
const AdjacencyMatrix<T>& Graph<T>::
get_matrix() const { return _adj_matrix; }

#endif // LIB_GRAPH_TYPES_GRAPH_TYPES_H_
