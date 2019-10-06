#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

mt19937 engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
using AList = vector<list<unsigned>>;

/* TODO:
 *  1. Сгенерировать количество вершин и ребер                          +
 *  2. В соответствии с вариантом сгенерировать остальные данные        -
 *  3. Вывести сгенерированное представление в текстовый файл Graph     +
 *  4. Вычислить степени вершин и вывести в текстовый файл Degree       -
 *  5. Выполнить преобразование 1                                       -
 *  6. Вывести сгенерированное представление в текстовый файл Graph 1   -
 *  7. Вычислить степени вершин и сравнить с файлом Degree              -
 *  8. Выполнить преобразование 2                                       -
 *  9. Вывести сгенерированное представление в текстовый файл Graph 2   -
 *  10.Вычислить степени вершин и сравнить с файлом Degree              -
 */

/* TODO:
 *  1. Сгенерить минимальное остовное дерево
 *  2. Добавить случайно
 *
 */

void shuffle(vector<unsigned> &a) {
    uniform_int_distribution<unsigned> dist(0, a.size() - 1);
    for(size_t i = 0; i < a.size(); i++) {
        unsigned j;
        do {
            j = dist(engine);
        } while (i == a[j] || j == a[i]);
        swap(a[i], a[j]);
    }
}

void displayAdjGraph(AList a) {
    for(auto &l: a) {
        for(auto &x: l) {
            cout << x << " ";
        }
        cout << endl;
    }
    cout << endl;
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
    displayAdjGraph(result);
    return result;
}

AList generateGraph() {
    uniform_int_distribution<unsigned> intDist(20, 30);
    const unsigned V = 5;//intDist(engine);
    const unsigned ADJ_MAX = V - 1;
    AList a = generateConnectedGraph(V);
    for(size_t i = 0; i < 3; i++) {
        //диапазон распределения от 0 до ADJ_MAX - i - 1
        const unsigned SIZE = a[i].size();
        intDist.param(typename decltype(intDist)::param_type(SIZE, ADJ_MAX));
        //генерируем количество добавляемых смежных вершин
        const unsigned ADJS_LEFT = intDist(engine);
        intDist.param(typename decltype(intDist)::param_type(i + 1, ADJ_MAX));
        for(size_t j = SIZE; j < ADJS_LEFT; j++) {
            unsigned v;
            do {
                v = intDist(engine);
            } while (find(a[i].begin(), a[i].end(), v) != a[i].end());
            a[i].push_back(v);
            a[v].push_back(i);
        }
    }
    displayAdjGraph(a);
    return a;
}

int main() {
    generateGraph();
    return 0;
}