#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include <stack>

using namespace std;
using Matrix = vector<vector<uint8_t>>;
using Edge = pair<unsigned, unsigned>;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 eng(seed);

void MatrixOutput(const Matrix &M, ostream& stream) {
    for(auto r: M){
        for(auto c: r)
            stream << (int)c << " ";
        stream << endl;
    }
}

unsigned UGen(const unsigned &left, const unsigned &right) {
    return uniform_int_distribution<unsigned>(left, right)(eng);
}

Edge GenerateEdge(const unsigned &left, const unsigned &right) {
    Edge e;
    do {
        e = Edge(UGen(left, right), UGen(left, right));
    } while (e.first == e.second);
    return e;
}

//генерация множества ребер минимально связного графа
vector<Edge> GenerateConnectedEdges(const unsigned &V) {
    vector<uint8_t> involved(V);    //Хранит информацию есть ли у вершины связь
    const unsigned R = V - 1;       //Минимальное количество ребер связного графа
    vector<Edge> edges(R);

    Edge e = GenerateEdge(0, V - 1);
    edges[0] = e;
    involved[e.first]  = 1;
    involved[e.second] = 1;
    for(size_t i = 1; i < R; i++) {
        do {
            e = GenerateEdge(0, V - 1);
        } while (involved[e.first] == involved[e.second]);
        if(involved[e.first] == 0) involved[e.first]  = 1;
        else                       involved[e.second] = 1;
        edges[i] = e;
    }
    return edges;
}

template< class InputIt >
bool EdgeExist(InputIt firstRow, InputIt secondRow, InputIt firstRowEnd, const Edge &e) {
    while(firstRow != firstRowEnd) {
        if(*firstRow == 1 && *secondRow == 1) return true;
        firstRow++;
        secondRow++;
    }
    return false;
}

Matrix GenerateIncMatrix() {
    const unsigned V = 5;
    const unsigned R = 6;
    vector<Edge> connEdges = GenerateConnectedEdges(V);
    Matrix m(V, vector<uint8_t>(R));
    size_t i = 0;
    for(auto &e: connEdges) {
        m[e.first][i] = m[e.second][i] = 1;
        i++;
    }
    for(i; i < R; i++) {
        Edge e;
        bool b;
        do {
            e = GenerateEdge(0, V - 1);
        } while (EdgeExist(m[e.first].begin(), m[e.second].begin(), m[e.first].begin()+i, e));
        m[e.first][i] = m[e.second][i] = 1;
    }
    return m;
}

Matrix AMatrixFromIMatrix(const Matrix &I) {
    unsigned V = I.size();
    unsigned R = I[0].size();
    Matrix result(V, vector<uint8_t>(V));
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

// void DFS() {
//     stack<unsigned> s;
//     s.push(0);
//     while(!s.empty()) {
//         unsigned v = s.top();
//         s.pop();
//         for(unsigned i = 0; i < edges[v].size(); i++) {
//             if(mark[edges[v][i]] == 0) {
//                 s.push(edges[v][i]);
//                 mark[edges[v][i]] = 1;
//             }
//         }
//     }
// }

int main() {
    do {
        auto k = GenerateIncMatrix();
        MatrixOutput(k, cout);  
        cout << endl;
        MatrixOutput(AMatrixFromIMatrix(k), cout);
        system("pause");
    } while(true);
    return 0;
}