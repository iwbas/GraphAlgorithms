#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include <stack>
#include <queue>
#include <fstream>

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
    const unsigned V = 7;
    const unsigned R = 12;
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

void DFSIMatrix(const Matrix &M, const unsigned &start) {
    ofstream out("Graph.txt", ios::app);
    out << "Проход в ширину: " << endl;
    const unsigned R = M[0].size();
    vector<unsigned> mark(M.size());
    mark[start] = 1;
    stack<unsigned> s;
    s.push(start);
    while(!s.empty()) {
        unsigned v = s.top();
        s.pop();
        out << v << " ";
        for(unsigned j = 0; j < R; j++) {
            while (M[v][j] != 1 && j < R) j++;
            unsigned k = 0;
            while ( ( M[k][j] != 1 || k == v ) && j < R) k++;
            if(mark[k] == 0) {
                s.push(k);
                mark[k] = 1;
            }
        }
    }
}



vector<unsigned> BFSAMatrix(const Matrix &M, const unsigned &start, const unsigned &to) {
    ofstream out("Graph1.txt");
    const unsigned V = M[0].size();
    vector<unsigned> mark(M.size());
    queue<unsigned> s;
    s.push(start);
    mark[start] = 1;
    while(!s.empty()) {
        unsigned v = s.front();
        s.pop();
        out << v << " ";
        for(unsigned j = 0; j < V; j++) {
            if(M[v][j] == 1 && mark[j] == 0) {
                s.push(j);
                mark[j] = 1;
            }
        }
    }
}

unsigned Diameter(const Matrix &M) {
    unsigned diameter = 0;
    for(size_t i = 0; i < M.size() - 1; i++) {
        vector<unsigned> mark(M.size());
        queue<unsigned> s;
        vector<unsigned> d(M.size());
        s.push(i);
        mark[i] = 1;
        while(!s.empty()) {
            unsigned v = s.front();
            s.pop();
            for(unsigned j = 0; j < M.size(); j++) {
                if(M[v][j] == 1 && mark[j] == 0) {
                    s.push(j);
                    mark[j] = 1;
                    d[j] = d[v] + 1;
                }
            }
        }
        auto max = max_element(d.begin(), d.end());
        if(*max > diameter) {
            diameter = *max;
        }
    }
    return diameter;
}

void MatrixToFile(const Matrix &M, const string &fileName) {
    ofstream o(fileName);
    MatrixOutput(M, o);
}

int main() {
    auto IMatrix = GenerateIncMatrix();
    MatrixToFile(IMatrix, "Graph.txt");
    DFSIMatrix(IMatrix, 0);
    
    auto AMatrix = AMatrixFromIMatrix(IMatrix);
    MatrixToFile(AMatrix, "Graph1.txt");
    BFSAMatrix(AMatrix, 0, 5);

    cout << Diameter(AMatrix) << endl;

    return 0;
}