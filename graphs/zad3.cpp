#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// krawedz
struct Edge {
    int dest, weight;
};

// algorytm Prima
class Prim {
private:
    int V; // liczba wierzcholkow
    vector<vector<Edge>> graph; // graf jako lista sasiedztwa

public:
    Prim(int v);
    void addEdge(int src, int dest, int weight);
    void findMST();
};

Prim::Prim(int v) {
    V = v;
    graph.resize(V);
}

// dodawanie krawedzi do grafu
void Prim::addEdge(int src, int dest, int weight) {
    Edge edge = { dest, weight };
    graph[src].push_back(edge);
    edge.dest = src; // krawedz w obie strony, bo graf nieskierowany
    graph[dest].push_back(edge);
}

// szukanie min drzewa rozpinajacego
void Prim::findMST() {
    vector<bool> visited(V, false); // wektor do przechowywania wart. bool czy dany wierzcholek zostal odwiedzony czy nie
    vector<Edge> mst; //  krawedzie MST
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //kolejka priorytetow krawedzi (do opcjonalnego dodania do mst)

    // start od pierwszego wierzcholka
    int start_vertex = 0;
    visited[start_vertex] = true;

    // przypisanie kolejce krawedzi od pocz wierzcholka
    for (Edge edge : graph[start_vertex]) {
        pq.push({ edge.weight, edge.dest });
    }

    // dodawanie krawedzi do mst w sposob iteracyjny
    while (!pq.empty()) {
        pair<int, int> front = pq.top(); //krawedz o najmniejszym koszcie
        pq.pop();
        int weight = front.first;
        int u = front.second;

        // w przypadku braku odwiedzin wierzcholka, nastepuje dodanie go do mst
        if (!visited[u]) {
            visited[u] = true;
            mst.push_back({ u, weight });

            // dodanie krawedzi zaczynajacych sie w rozpatrywanym wierzcholku
            for (Edge edge : graph[u]) {
                if (!visited[edge.dest]) {
                    pq.push({ edge.weight, edge.dest });
                }
            }
        }
    }

    // wydruk krawedzi mst i ich sumy wag
    int mstWeight = 0;
    cout << "minimalne drzewo rozpinajace (MST) dla grafu:" << endl;
    for (Edge edge : mst) {
        cout << (char)('A' + edge.dest) << " --" << edge.weight << "-- " << (char)('A' + start_vertex) << endl;
        mstWeight += edge.weight;
    }
    cout << "suma wag MST: " << mstWeight << endl;
}

int main() {
    Prim graph(6);
    graph.addEdge(0, 1, 6);
    graph.addEdge(0, 2, 1);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 2, 5);
    graph.addEdge(1, 4, 3);
    graph.addEdge(2, 3, 5);
    graph.addEdge(2, 4, 6);
    graph.addEdge(2, 5, 4);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 5, 6);

    graph.findMST();

    return 0;
}
