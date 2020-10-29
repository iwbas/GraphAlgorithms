#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <list>
#include "windows.h"

#define infinity 10000

using namespace std;

using Row = vector<uint8_t>;
using Matrix = vector<Row>;
using AList = vector<list<pair<unsigned,unsigned>>>;


auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 eng(seed);

/* TODO
    + Сгенерировать количество вершин и рёбер, сгенерировать остальные данные
    + Сгеренировать случайные веса ребер в матрице смежности.
    + Вывести сгенерированное представление в текстовый файл Graph
    + Реализовать алгоритм Дейкстры на матрице, задав случайным образом начальную и конечную вершины; вывести маршрут в файл PathD
    + Преобразовать матрицу смежности в список смежных вершин;
    + Реализовать алгоритм Дейкстры на списке задав случайным образом начальную и конечную вершины; вывести маршрут в файл PathDL
    + Реализовать алгоритм Беллмана-Форда на матрице смежности; вывести результат в файл PathBF.
    + Реализовать алгоритм Флойда –Уоршелла на матрице смежности; вывести результат в файл PathFW
    + Удалить веса и вычислить диаметр графа
*/

unsigned UGen(const unsigned &left, const unsigned &right) {
    return uniform_int_distribution<unsigned>(left, right)(eng);
}

void MatrixOutput(const Matrix &m, ostream&& stream) {
    for(auto &row: m) {
        for(auto &element: row)
            stream << (int)element << " ";
        stream << endl;
    }
}

/// Генерация случайного связного неориентированного графа в виде матрицы смежности
Matrix GenerateConnectedGraph(const size_t &V) {
    Matrix result(V, Row(V));
    for(size_t i = 0; i < V-1; i++) {
        size_t adjacent = UGen(i+1, V-1);
        result[i][adjacent] = result[adjacent][i] = 1;
    }
    return result;
}


Matrix GenerateAdjacencyMatrix(const size_t &V, const size_t &R) {
    if (R > V*(V-1)/2)
        throw std::runtime_error("The number of ribs exceeds the maximum");
    Matrix result = GenerateConnectedGraph(V);
    size_t ribsLeft = R - (V - 1);
    for(size_t i = 0; i < ribsLeft; i++) {
        size_t first, second;
        do {
            first  = UGen(0, V-1);
            second = UGen(0, V-1);
        } while(first == second || result[first][second] == 1 || result[second][first] == 1);
        result[first][second] = result[second][first] = 1;
    }
    return result;
}

void RandomlyWeight(Matrix &graph) {
    const unsigned V = graph.size();
    for(size_t i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if(graph[i][j] == 1)
                graph[i][j] = graph[j][i] = UGen(1, 10);
}

int MinDistance(const vector<unsigned> &distances, const vector<uint8_t> &mark) {
    int min = infinity, min_index;
    for (size_t v = 0; v < distances.size(); v++)
        if (mark[v] == 0 && distances[v] <= min)
            min = distances[v], min_index = v;
    return min_index;
}

vector<unsigned> Dijkstra(const Matrix &adj, const unsigned &start) {
    const unsigned V = adj.size();
    vector<unsigned> distances(V, infinity);
    distances[start] = 0;
    vector<uint8_t> mark(V);
    for(size_t i = 0; i < V; i++) {
        //выбираем минимальный вес из непосещенных вершин
        size_t u = MinDistance(distances, mark);
        mark[u] = 1;
        for (int v = 0; v < V; v++)
            if (!mark[v] && adj[u][v] && distances[u] != infinity
                && distances[u] + adj[u][v] < distances[v])
                distances[v] = distances[u] + adj[u][v];
    }
    return distances;
}

vector<unsigned> ShortestPath(const Matrix &adj, const unsigned &from, const unsigned &to) {
    vector<unsigned> result{to};
    vector<unsigned> shortestDistances = Dijkstra(adj, from);

    unsigned v = to;
    unsigned weight = shortestDistances[to];

    while(v != from) {
        for(size_t i = 0; i < adj.size(); i++) {
            if(adj[i][v] != 0) {
                int w = weight - adj[i][v];
                if(w == shortestDistances[i]) {
                    result.push_back(i);
                    weight = w;
                    v = i;
                }
            }
        }
    }
    return result;
}

AList AMatrixToAList(const Matrix &m) {
    const unsigned V = m.size();
    AList result(V);
    for(size_t i = 0; i < V; i++)
        for(size_t j = 0; j < V; j++)
            if(m[i][j] != 0) {
                result[i].push_back(make_pair(j, m[i][j]));
            }
    return result;
}

vector<unsigned> Dijkstra(const AList &a, const unsigned &start) {
    const unsigned V = a.size();
    vector<unsigned> distances(V, infinity);
    distances[start] = 0;
    vector<uint8_t> mark(V);
    for(size_t i = 0; i < V - 1; i++) {
        const unsigned vertex = MinDistance(distances, mark);
        mark[vertex] = 1;
        for(auto &u: a[vertex])
            if(distances[u.first] > distances[vertex] + u.second)
                distances[u.first] = distances[vertex] + u.second;

    }
    return distances;
}

vector<unsigned> BellmanFord(const Matrix &adj, const unsigned &start) {
    const unsigned V = adj.size();
    vector<unsigned> distances(V, infinity);
    distances[start] = 0;
    for (int i = 0; i < V - 1; ++i)
    for(size_t u = 0; u < V; u++)
        for(size_t v = 0; v < V ; v++)
            if(adj[u][v] > 0 && distances[v] > distances[u] + adj[u][v])
                distances[v] = distances[u] + adj[u][v];
    return distances;
}

Matrix FloydWarshall(Matrix adj) {
    const unsigned V = adj.size();
    for(size_t i = 0; i < V; i++)
        for (int j = 0; j < V; ++j)
            if (i != j && adj[i][j] == 0)
                adj[i][j] = 100;
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            for (int k = 0; k < V; ++k)
                if(adj[j][k] > adj[j][i] + adj[i][k])
                    adj[j][k] = adj[j][i] + adj[i][k];

    return adj;
}

void DeleteWeight(Matrix &adj) {
    for (auto &row: adj)
        for (auto &e: row)
            if (e > 0) e = 1;
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // + Сгенерировать количество вершин и рёбер, сгенерировать остальные данные
    size_t V = 10;//5;//UGen(20, 30);
    size_t R = 35;//UGen(V-1, V*(V-1)/2);
    cout << "Vertices amount: " << V << endl;
    cout << "Ribs amount: "   << R << endl;
    Matrix graph = GenerateAdjacencyMatrix(V, R);
    cout << "+ Сгеренировать случайные веса ребер в матрице смежности." << endl;
    RandomlyWeight(graph);

    cout << "+ Вывести сгенерированное представление в текстовый файл Graph" << endl;
    MatrixOutput(graph, move(cout));
    MatrixOutput(graph, ofstream("Graph.txt"));
    cout << endl << endl;
    cout << "+ Реализовать алгоритм Дейкстры на матрице, задав случайным образом начальную и конечную вершины" << endl;
    for(auto &vertex: ShortestPath(graph, 0, 4))
        cout << vertex << " ";
    cout << endl;


    cout << "+ Преобразовать матрицу смежности в список смежных вершин;" << endl;
    cout << "+ Реализовать алгоритм Дейкстры на списке задав случайным образом начальную и конечную вершины;" << endl;
    for(auto &k: Dijkstra(AMatrixToAList(graph), 0))
        cout << k << " ";
    cout << endl;
    cout << "+ Реализовать алгоритм Беллмана-Форда на матрице смежности;" << endl;
    for(auto &k: BellmanFord(graph, 0)) {
        cout << k << " ";
    }

    cout << "+ Реализовать алгоритм Флойда –Уоршелла на матрице смежности;" << endl;
    MatrixOutput(FloydWarshall(graph), move(cout));

    //+ Удалить веса и вычислить диаметр графа
    DeleteWeight(graph);

    MatrixOutput(graph, move(cout));

    Matrix shortestDistances = FloydWarshall(graph);
    uint8_t max = 0;
    for(auto &row: shortestDistances)
        for(auto &e: row)
            if(max < e) max = e;

    cout << (int)max << endl;

    cout << endl;cout << endl;cout << endl;
    return 0;
}