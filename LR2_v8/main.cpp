#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <queue>
#include <algorithm>

/*
 * TODO:
 *  1. Повторяющиеся ребра
 *
 */

using namespace std;
using Matrix = vector<vector<unsigned>>;
using Edge    = pair<unsigned, unsigned>;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 engine(seed);

void MatrixOutput(const Matrix &M, ostream& stream) {
    for(auto r: M){
        for(auto c: r)
            stream << c << " ";
        stream << endl;
    }
}


vector<Edge> GenerateEdgesOfConnectedGraph(const unsigned &V) {
    uniform_int_distribution<unsigned> dist(0, V-1);
    vector<Edge> edges(V - 1);
    vector<uint8_t> involved(V);
    Edge e(dist(engine), dist(engine));
    involved[e.first ] = 1;
    involved[e.second] = 1;
    edges[0] = e;
    for(size_t i = 1; i < V - 1; i++) {
        do {
            e = Edge(dist(engine), dist(engine));
        } while (e.first == e.second && involved[e.first] == involved[e.second]);
        edges[i] = e;
        involved[e.first] = involved[e.second] = 1;
    };
    for(auto &e: edges) {
        cout << "[" << e.first << ";" << e.second << "]" << " ,";
    }
    cout << endl;
}
Matrix GenerateConnectedIMatrix(const unsigned &V, const unsigned &R) {
    uniform_int_distribution<unsigned> dist(0, V-1);
    vector<uint8_t> isInvolved(V);
    Matrix result(V, vector<unsigned>(R));
    unsigned first  = dist(engine);
    unsigned second = dist(engine);
    result[first ][0] = 1;
    result[second][0] = 1;
    for(size_t i = 1; i < V - 1; i++) {
        do {
            first  = dist(engine);
            second = dist(engine);
        } while (first == second && (isInvolved[first] == isInvolved[second]));
        result[first][i]  = 1;
        result[second][i] = 1;
    }
    MatrixOutput(result, cout);
    return result;
}
//генерировать множество неповторяющихся edges, заполнить им матрицу
Matrix GenerateIMatrix() {
    uniform_int_distribution<unsigned> dist(20, 30);
    const unsigned V = 5;//dist(engine);
    const unsigned R = 5;//(V * (V - 1) / 2) / 2;

    Matrix result;//s = GenerateConnectedIMatrix(V, R);

    vector<Edge> edges(R - (V - 1));

    dist.param(std::uniform_int_distribution<unsigned >::param_type(0, V - 1));
    for(auto &edge: edges) {
        Edge genEdge;
        do {
            genEdge = Edge(dist(engine), dist(engine));
        } while (find(edges.begin(), edges.end(), genEdge) != edges.end());
        edge = genEdge;
    }

    for(auto &e: edges) {
        cout << "[" << e.first << ";" << e.second << "]" << " ,";
    }
    cout << endl;


    for(size_t i = V - 1; i < R; i++) {
        unsigned first = dist(engine);
        unsigned second;
        do {
            second = dist(engine);
        } while (first == second);
        result[ first  ][i] = 1;
        result[ second ][i] = 1;
    }
    cout << endl;
    MatrixOutput(result, cout);
    return result;
}

//void IMatrixBFS(const Matrix &incMatrix) {
//    bool *visited = new bool[incMatrix.size()];
//    for(auto &x: visited)
//        x = false;
//
//    //queue<unsigned>
//}

//vector<vector<unsigned>> TransposeMatrix()

Matrix AMatrixFromIMatrix(const Matrix& I) {
    unsigned V = I.size();
    unsigned R = I[0].size();
    Matrix result(V, vector<unsigned>(V));
    for(size_t j = 0; j < R; j++) {
        int foundedCounter = 0;
        int i = 0;
        size_t a, b;
        while(I[i][j] == 0) i++;
        a = i++;
        while(I[i][j] == 0) i++;
        b = i;
        result[a][b] = 1;
        result[b][a] = 1;
    }
    return result;
}

int main() {
    GenerateEdgesOfConnectedGraph(5);
    //GenerateConnectedIMatrix(5, 10);
    //auto AM = AMatrixFromIMatrix(GenerateIMatrix());
    //cout << endl;
    //MatrixOutput(AM, cout);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}