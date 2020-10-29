//ToDo:
// 1.	Сгенерировать количество вершин и рёбер, сгенерировать остальные данные +
// 2.	Снеренировать случайные веса ребер в матрице смежности +
// 3.	Вывести сгенерированное представление в текстовый файл Graph +
// 4.	Реализовать алгоритм Краскала на матрице смежности; вывести дерево в файл TreeK +
// 5.	Реализовать алгоритм Прима на матрице смежности; вывести дерево в файл TreeP
// 6.	Преобразовать матрицу в список ребер и реализовать алгоритм Краскала;
// вывести дерево в файл TreeKE
// 7.	Преобразовать матрицу в список смежных вершин и реализовать алгоритм Прима;
// вывести дерево в файл TreePL

#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

using Matrix = vector<vector<unsigned>>;
using RibsList = vector<pair<unsigned, unsigned>>;

mt19937 generator(static_cast<unsigned int>(
    chrono::high_resolution_clock::now().time_since_epoch().count())
);

void MatrixOutput(const Matrix &m, ostream&& out) {
    for(const auto &row: m) {

        for(const auto &item: row)
            out << (item == UINT32_MAX ? 0 : item) << " ";

        out << endl;
    }
}

void RibsListOutput(const RibsList &l, ostream&& out) {
    for (auto &item: l)
        out << "( " << item.first << ", " << item.second << " ) ";
}

unsigned random(const unsigned &l, const unsigned &r) {
    return uniform_int_distribution<unsigned>(l, r)(generator);
}

Matrix generateConnectedGraph(const unsigned &V) {
    Matrix graph(V, vector<unsigned>(V, UINT32_MAX));

    for (unsigned i = 0; i < V-1; i++) {
        unsigned v = random(i+1, V-1);
        graph[i][v] = graph[v][i] = 1;
    }
    
    return graph;
}

Matrix generateAdjacencyMatrix(const unsigned &V, const unsigned &R) {
    if (R > V*(V-1)/2)
        throw std::invalid_argument("The number R of ribs exceeds the maximum");

    Matrix graph = generateConnectedGraph(V);
    
    for(unsigned i = 0; i < R-(V-1); i++) {
        unsigned first, second;

        do {
            first  = random(0, V-1);
            second = random(0, V-1);
        } while(first == second || graph[first][second] == 1 || graph[second][first] == 1);
        
        graph[first][second] = graph[second][first] = 1;
    }
    return graph;
}

void RandomlyWeigh(Matrix &graph) {
    const unsigned V = graph.size();
    
    for(size_t i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            if(graph[i][j] == 1)
                graph[i][j] = graph[j][i] = random(1, 10);
}

RibsList kruskalFindMST(Matrix graph) {
    const unsigned V = graph.size();

    MatrixOutput(graph, move(cout));

    RibsList tree;
    vector<unsigned> componentId(V); //id = 0 - вершина не пренадлежит компоненту
    unsigned componentCounter = 0;
    
    unsigned k = 0;

    while (k < V-1) {
        // вычитаем единицу, чтобы при поиске минимального веса
        // не было лишних присвоений UINT32_MAXных элементов из-за <= в if
        unsigned minWeight = UINT32_MAX - 1; 
        unsigned minI, minJ;

        for (unsigned i = 0; i < V-1; i++) {
            for (unsigned j = i+1; j < V; j++) {
                unsigned &w = graph[i][j];

                if (w <= minWeight) {
                    minWeight = w;
                    minI = i;
                    minJ = j;
                }
            }
        }
        graph[minI][minJ] = graph[minJ][minI] = UINT32_MAX;

        //Если вершины находятся не в одной компоненте
        //Id могут быть одинаковыми в случае
        //если вершины не принадлежат ни одному компоненту (id = 0)
        //Поэтому один из Id проверяется на 0
        if (componentId[minI] != componentId[minJ] || componentId[minI] == 0) {
            //Могут быть равны только при 0
            if (componentId[minI] != componentId[minJ]) {
                //Если у обоих вершин есть компоненты, соединяем в одну компоненту
                if (componentId[minI] != 0 && componentId[minJ] != 0) {
                    unsigned id = componentId[minJ];
                    for (unsigned c = 0; c < componentId.size(); c++)
                        if (componentId[c] == id)
                            componentId[c] = componentId[minI];
                } else {
                    //Если одна из вершин без компоненты, приписываем ей id
                    if (componentId[minI] == 0) componentId[minI] = componentId[minI];
                    else                        componentId[minJ] = componentId[minI];
                } 
            } else {
                componentCounter++;
                componentId[minI] = componentId[minJ] = componentCounter;
            }

            tree.push_back(make_pair(minI, minJ));
            k++;
        }
    }
    return tree;
}

int main() {
    // Сгенерировать количество вершин и рёбер, сгенерировать остальные данные
    const unsigned V = random(20, 30);
    const unsigned R = random(V-1, V*(V-1)/2);

    // Снеренировать случайные веса ребер в матрице смежности
    // Matrix graph = generateAdjacencyMatrix(V, R);
    Matrix graph = generateAdjacencyMatrix(5, 7);
    RandomlyWeigh(graph);

    // Вывести сгенерированное представление в текстовый файл Graph
    MatrixOutput(graph, ofstream("Graph.txt"));

    // Реализовать алгоритм Краскала на матрице смежности; вывести дерево в файл TreeK
    RibsList MST = kruskalFindMST(graph);
    RibsListOutput(MST, ofstream("TreeK.txt"));


    return 0;
}