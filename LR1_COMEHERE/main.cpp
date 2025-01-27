#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
//#include "windows.h"

using namespace std;

mt19937 engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
using AList   = vector<list<unsigned>>;
using Edge    = pair<unsigned, unsigned>;
using RList   = vector<Edge>;
using IMatrix = vector<vector<unsigned>>;

/* TODO:
 *  1. Сгенерировать количество вершин и ребер                          +
 *  2. В соответствии с вариантом сгенерировать остальные данные        +
 *  3. Вывести сгенерированное представление в текстовый файл Graph     +
 *  4. Вычислить степени вершин и вывести в текстовый файл Degree       +
 *  5. Выполнить преобразование 1                                       +
 *  6. Вывести сгенерированное представление в текстовый файл Graph 1   +
 *  7. Вычислить степени вершин и сравнить с файлом Degree              +
 *  8. Выполнить преобразование 2                                       +
 *  9. Вывести сгенерированное представление в текстовый файл Graph 2   +
 *  10.Вычислить степени вершин и сравнить с файлом Degree              +
 */

// Генерация списка смежности, преобразования
AList   generateConnectedGraph(const unsigned &);
AList   generateGraph();
RList   RListFromAList(const AList &);
IMatrix IMatrixFromRList(const RList &);
// Вывод в файл
void GraphToFile(const AList &, const string &);
void GraphToFile(const RList &, const string &);
void GraphToFile(const IMatrix &, const string &);
// Вывод на экран
void GraphDisplay(const AList &);
void GraphDisplay(const RList &);
// Подсчет степеней
unsigned CalculateVertexAmount(const RList &);
vector<unsigned> CalculateDegrees(const RList &);
vector<unsigned> CalculateDegrees(const IMatrix &);
// Вывод степеней вершин в файл
void DegreesToFile(const AList &a, const string &);
vector<unsigned> DegreesFromFile(const string &);

unsigned CalculateDegreesAmount(const AList &a);
unsigned CalculateRibsAmount(const AList &a);

int main() {
    auto a = generateGraph();
    GraphToFile(a, "Graph.txt");
    DegreesToFile(a, "Degree.txt");
    auto r = RListFromAList(a);
    GraphDisplay(r);
    GraphToFile(r, "Graph 1.txt");
    auto rDegrees = CalculateDegrees(r);
    auto aDegrees = DegreesFromFile("Degree.txt");
    cout << "Степени " << ((rDegrees == aDegrees) ? "совпадают" : "не совпадают") << endl;
    auto inc = IMatrixFromRList(r);
    GraphToFile(inc, "Graph 2.txt");
    auto iDegrees = CalculateDegrees(inc);
    cout << "Степени " << ((rDegrees == iDegrees) ? "совпадают" : "не совпадают") << endl;
    return 0;
}

AList generateConnectedGraph(const unsigned &V) {
    AList result(V);
    const unsigned ADJ_MAX = V - 1;
    uniform_int_distribution<unsigned> dist(1, ADJ_MAX);
    unsigned v = dist(engine);
    result[0].push_back(v);
    result[v].push_back(0);
    unsigned involvedVertics = 2;
    size_t i = 1;
    dist.param(typename decltype(dist)::param_type(0, ADJ_MAX));
    while(involvedVertics != V) {
        if(result[i].empty()) {
            do {
                v = dist(engine);
            } while (result[v].empty());
            result[i].push_back(v);
            result[v].push_back(i);
            involvedVertics++;
        }
        i++;
    }
    return result;
}

AList generateGraph() {
    uniform_int_distribution<unsigned> intDist(20, 30);
    const unsigned V = 12;//intDist(engine);
    const unsigned ADJ_MAX = V - 1;
    unsigned RIBS_COUNT = 0;
    AList a = generateConnectedGraph(V);
    for(size_t i = 0; i < V; i++) {
        const unsigned SIZE = a[i].size();
        intDist.param(typename decltype(intDist)::param_type(0, ADJ_MAX-SIZE));
        const unsigned ADJ_LEFT = intDist(engine);
        intDist.param(typename decltype(intDist)::param_type(0, ADJ_MAX));
        for(size_t j = 0; j < ADJ_LEFT; j++) {
            unsigned v;
            do {
                v = intDist(engine);
            } while(find(a[i].begin(), a[i].end(), v) != a[i].end()
                    || a[v].size() == ADJ_MAX
                    || i == v);
            a[i].push_back(v);
            a[v].push_back(i);
        }
    }
    return a;
}

RList RListFromAList(const AList &a) {
    RList result(CalculateRibsAmount(a));
    auto iter = result.begin();
    for(size_t i = 0; iter != result.end(); i++) {
        for(const auto &v: a[i]) {
            if(v > i) {
                *iter = Edge(i, v);
                iter++;
            }
        }
    }
    return result;
}

IMatrix IMatrixFromRList(const RList &r) {
    IMatrix result(CalculateVertexAmount(r), vector<unsigned>(r.size()));

    for(size_t i = 0; i < r.size(); i++) {
        result[r[i].first][i] = 1;
        result[r[i].second][i] = 1;
    }
    return result;
}

void GraphToFile(const AList &a, const string &fileName) {
    ofstream out(fileName);
    out << "Сгенерированный граф," << endl
        << "в виде списка смежностей с количеством вершин - "
        << a.size() << ","
        << endl
        << "и количеством ребер - "
        << CalculateRibsAmount(a)
        << endl;
    for(size_t i = 0; i < a.size(); i++) {
        out << i << ": ";
        for(auto &x: a[i]) {
            out << x << " ";
        }
        out << endl;
    }
}

void GraphToFile(const RList &r, const string &fileName) {
    ofstream out(fileName);
    out << "Список ребер:" << endl;
    for(const auto &edge: r) {
        out << "[ " << edge.first << "; " << edge.second << " ]" << endl;
    }
}

void GraphToFile(const IMatrix &inc, const string &fileName) {
    ofstream out(fileName);
    out << "Матрица инциденции:" << endl;
    for(const auto &row: inc) {
        for(const auto &x: row)
            out << x << " ";
        out << endl;
    }
}

void GraphDisplay(const AList &a) {
    for (auto &l: a) {
        for (auto &x: l) {
            cout << x << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void GraphDisplay(const RList &r) {
    for(const auto &edge: r) {
        cout << "[ " << edge.first << "; " << edge.second << " ]" << endl;
    }
}

/*
 * Ввиду составленного алгоритма преобразования списка смежности в список ребер,
 * первая вершина пары не может иметь максимальный индекс вершины.
 * Поэтому происходит поиск максимального индекса по второй.
 */
unsigned CalculateVertexAmount(const RList &r) {
    auto t = max_element(r.begin(), r.end(), [](const Edge &a, const Edge &b){
        return ( a.second < b.second );
    });
    return t->second + 1;
}

vector<unsigned> CalculateDegrees(const RList &r) {
    vector<unsigned> result(CalculateVertexAmount(r));
    for(const auto &edge: r) {
        result[edge.first]++;
        result[edge.second]++;
    }
    return result;
}

vector<unsigned> CalculateDegrees(const IMatrix &inc) {
    vector<unsigned> result(inc.size());
    for(size_t i = 0; i < inc.size(); i++)
        for(const auto &x: inc[i]) {
            if(x == 1) {
                result[i]++;
            }
        }

    for(const auto& x: result) {
        cout << x << " ";
    }
    cout << endl;
    return result;
}

void DegreesToFile(const AList &a, const string &fileName) {
    ofstream out(fileName);
    for(const auto & d : a)
        out << d.size() << " ";
}

vector<unsigned> DegreesFromFile(const string &fileName) {
    ifstream in(fileName);
    vector<unsigned> result;
    unsigned t;
    while(in >> t)
        result.push_back(t);
    return result;
}

unsigned CalculateDegreesAmount(const AList &a) {
    unsigned amount = 0;
    for(auto &l: a)
        amount += l.size();
    return amount;
}

unsigned CalculateRibsAmount(const AList &a) {
    return CalculateDegreesAmount(a) / 2;
}