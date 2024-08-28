#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// struktura ktora bedzie przedstawiac krawedz 
struct Edge {
    int src, dest, weight;
};

// struktura ktora bedzie przedstawiala zbiór w strukturze zbiorów rozłącznych (union-find)
struct Subset {
    int parent, rank;
};

// implementacja algorytmu kruskala
class Kruskal {
private:
    int V; // liczba wierzcholkow w grafie
    vector<Edge> edges; // wektor krawedzi w grafie

    // pomocnicze funkcje
    int find(Subset subsets[], int i);
    void Union(Subset subsets[], int x, int y);

public:
    Kruskal(int v);
    void addEdge(int src, int dest, int weight);
    void findMST();
};

Kruskal::Kruskal(int v) {
    V = v;
}

// dodawanie krawedzi do grafu
void Kruskal::addEdge(int src, int dest, int weight) {
    Edge edge = { src, dest, weight };
    edges.push_back(edge);
}

// find do znajdywania korzenia zbioru
int Kruskal::find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// union do laczenia dwoch zbiorow
void Kruskal::Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// findMST do znajdywania min drzewa rozpinajacego
void Kruskal::findMST() {
    vector<Edge> result; // wektor z krawędziami MST
    int e = 0; // indeks krawędzi w grafie
    // krawedzie beda sortowane wedlug wag
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
        });
    // alokowanie pamieci dla zbiorow rozlacznych
    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;}
    // iteracje przeprowadzane po krawedziach i przypisywanie do mst
    while (e < V - 1 && !edges.empty()) {
        Edge next_edge = edges.front();
        edges.erase(edges.begin());

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
            e++;}}
    // drukowanie krawedzi mst i ich sumy
    int mstWeight = 0;
    for (Edge edge : result) {
        cout << (char)('A' + edge.src) << " --" << edge.weight << "-- " << (char)('A' + edge.dest) << endl;
        mstWeight += edge.weight;
    }
    cout << "SUMA wag MST: " << mstWeight << endl;

    delete[] subsets;
}

int main() {
    Kruskal graph(6);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 7);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 4, 1);
    graph.addEdge(3, 4, 5);
    graph.addEdge(4, 5, 5);

    cout << "MINIMALNE drzewo rozpinajace (MST) dla grafu:" << endl;
    graph.findMST();

    return 0;
}
