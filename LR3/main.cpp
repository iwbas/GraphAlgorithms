#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <random>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

using Row = vector<uint8_t>;
using Matrix = vector<Row>;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 eng(seed);

/* TODO задания
    + Сгенерировать количество вершин и рёбер, сгенерировать остальные данные
    + Вывести сгенерированное представление в текстовый файл Graph
    + Вычислить матрицу достижимости обходом в ширину; вывести матрицу в файл GraphD
    + Вычислить матрицу контрдостижимости обходом в ширину; вывести матрицу в файл GraphKD
    + Вычислить компоненты сильной связности по матрицам достижимости и контрдостижимости
    + Вычислить матрицу транзитивного замыкания по алгоритму Флойда-Уоршелла;
      вывести матрицу в файл GraphTZU
    + Вычислить матрицу транзитивного замыкания обходом в глубину;
      вывести матрицу в файл GraphTZG
    + Преобразовать ориентированный граф в неориентированный (преобразовать матрицу смежности), сделать его несвязным (удаление нескольких ребер).
    + Найти компоненты связности обходом в ширину. Вывести компоненты в файл GraphS
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

// СВЯЗНОСТЬ????????
/// Генерация случайного связного ориентированного графа в виде матрицы смежности
Matrix GenerateConnectedGraph(const size_t &V) {
    Matrix result(V, Row(V));
    for(size_t i = 0; i < V-1; i++) {
        size_t adjacent = UGen(i+1, V-1);
        result[i][adjacent] = 1;
    }
    return result;
}


Matrix GenerateAdjacencyMatrix(const size_t &V, const size_t &R) {
    if (R > V*(V-1)/2)
        throw std::runtime_error("The number of ribs exceeds the maximum");
    Matrix result = GenerateConnectedGraph(V);
    size_t ribsLeft = R - (V - 1);
    cout << ribsLeft << endl;
    for(size_t i = 0; i < ribsLeft; i++) {
        size_t first, second;
        do {
            first  = UGen(0, V-1);
            second = UGen(0, V-1);
        } while(first == second || result[first][second] == 1 || result[second][first] == 1);
        result[first][second] = 1;
    }
    return result;
}

vector<unsigned> BFS(const Matrix &m, const unsigned &start) {
    const size_t V = m[0].size();
    vector<uint8_t > mark(V);
    queue<unsigned> q;
    q.push(start);
    mark[start] = 1;
    vector<unsigned> reachableVertices;
    while(!q.empty()) {
        unsigned v = q.front();
        q.pop();
        reachableVertices.push_back(v);
        for(unsigned j = 0; j < V; j++) {
            if(m[v][j] == 1 && mark[j] == 0) {
                q.push(j);
                mark[j] = 1;
            }
        }
    }
    return reachableVertices;
}

Matrix CreateReachabilityMatrix(const Matrix &m) {
    const size_t V = m.size();
    Matrix result(V, Row(V));
    for(size_t i = 0; i < V; i++) {
        vector<unsigned> adjacentVertices = BFS(m, i);
        for(auto &j: adjacentVertices)
            result[i][j] = 1;
    }
    return result;
}

Matrix CreateCounterreachabilityMatrix(const Matrix &m) {
    const size_t V = m.size();
    Matrix result(V, Row(V, 0));
    for(size_t i = 0; i < V; i++) {
        vector<unsigned> adjacentVertices = BFS(m, i);
        for(auto &j: adjacentVertices)
            result[j][i] = 1;
    }
    return result;
}

Matrix MultiplyElements(Matrix l, const Matrix &r) {
    if (l.size() != r.size() || l[0].size() != r[0].size())
        throw std::runtime_error("Multiplication of matrices of different sizes");
    for (size_t i = 0; i < l.size(); ++i)
        for (size_t j = 0; j < l[0].size(); ++j)
            l[i][j] *= r[i][j];
    return l;
}

void CalculateSCC(const Matrix &reach, const Matrix &counterReach) {
    unsigned V = reach.size();
    Matrix strongConnection = MultiplyElements(reach, counterReach);
    MatrixOutput(strongConnection, move(cout));
    cout << endl << endl;
    vector<unsigned> strongComponents;
    for(size_t i = 0; i < V; i++) {
        cout << "Component:";
        size_t j = i;
        while(j < V && strongConnection[i][j] == 1) {
            cout << " " << j;
            j++;
        }
        cout << endl;
        i = j-1;
    }
}

Matrix CreateTransitiveClosureMatrixWarshall(Matrix adj) {
    const unsigned V = adj.size();
    for(size_t i = 0; i < V; i++)
        for(size_t j = 0; j < V; j++)
            if(i != j && adj[i][j] == 1)
                for(size_t k = 0; k < V; k++)
                    adj[i][k] |= adj[j][k];
    return adj;
}

vector<uint8_t> DFS(const Matrix &adj, const unsigned start) {
    const unsigned V = adj.size();
    stack<unsigned> s;
    s.push(start);
    vector<uint8_t> visited(V);
    visited[start] = 1;
    while(!s.empty()) {
        unsigned v = s.top();
        s.pop();
        for(size_t j = 0; j < V; j++) {
            if(adj[v][j] == 1 && visited[j] == 0) {
                s.push(j);
                visited[j] = 1;
            }
        }
    }
    return visited;
}

Matrix CreateTransitiveClosureMatrixDFS(const Matrix &adj) {
    const unsigned V = adj.size();
    Matrix result(V);
    for(size_t i = 0; i < V; i++)
        result[i] = DFS(adj, i);
    return result;
}

Matrix OrientedToNot(Matrix adj) {
    const unsigned V = adj.size();
    for(size_t i = 0; i < V; i++)
        for(size_t j = 0; j < V; j++)
            if(adj[i][j] == 1)
                adj[j][i] = 1;
    return adj;
}

void UntieVertex(Matrix &adj, const unsigned &v) {
    const unsigned V = adj.size();
    adj[v] = Row(V);
    for(size_t i = 0; i < V; i++)
        adj[i][v] = 0;
}

void ConnectivityComponents(const Matrix &adj) {
    const unsigned V = adj.size();
    vector<uint8_t> visited(V);
    for(size_t i = 0; i < V; i++) {
        if(visited[i] == 0) {
            cout << "Component: ";
            auto reachable = BFS(adj, i);
            for(auto &v: reachable) {
                cout << " " << v;
                visited[v] = 1;
            }
            cout << endl;
        }
    }
}

int main() {
    // Генерация
    size_t V = UGen(20, 30);
    size_t R = UGen(V-1, V*(V-1)/2);
    cout << "Vertices amount: " << V << endl;
    cout << "Ribs amount: "   << R << endl;
    Matrix graph = GenerateAdjacencyMatrix(V, R);

    //Вывод в файл и на экран
    MatrixOutput(graph, move(cout));
    MatrixOutput(graph, ofstream("Graph.txt"));
    cout << endl << endl;

    //Матрица достижимости обходом в ширину
    Matrix reachability = CreateReachabilityMatrix(graph);
    MatrixOutput(reachability, move(cout));
    MatrixOutput(reachability, ofstream("GraphD"));
    cout << endl << endl;

    //Матрица контрдостижимости обходом в ширину
    Matrix counterreachability = CreateCounterreachabilityMatrix(graph);
    MatrixOutput(counterreachability, ofstream("GraphKD"));
    cout << endl << endl;

    CalculateSCC(reachability, counterreachability);
    cout << endl << endl;

    //Матрица транзитивного замыкания по Уоршеллу
    MatrixOutput(CreateTransitiveClosureMatrixWarshall(graph), move(cout));
    MatrixOutput(CreateTransitiveClosureMatrixWarshall(graph), ofstream("GraphTZU"));
    cout << endl << endl;

    //Матрица транзитивного замыкания обходом в глубину
    MatrixOutput(CreateTransitiveClosureMatrixDFS(graph), move(cout));
    MatrixOutput(CreateTransitiveClosureMatrixDFS(graph), ofstream("GraphTZG"));
    cout << endl << endl;

    //Ориентированный в неориентированный
    Matrix notOriented = OrientedToNot(graph);
    MatrixOutput(notOriented, move(cout));
    cout << endl << endl;

    //Делаем неориентированный граф несвязным
    UntieVertex(notOriented, UGen(0, V-1));
    MatrixOutput(notOriented, move(cout));
    cout << endl << endl;

    ConnectivityComponents(notOriented);
    return 0;
}