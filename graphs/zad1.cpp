#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <queue>
#include <stack>

using namespace std;

// przyleganie wezlow (sasiedztwo)
struct AdjListNode {
    int data;
    AdjListNode* next;
};

// lista dla tych wezlow
struct AdjList {
    AdjListNode* head;  // wskaznik do head
};

// struktura grafu. graf jest tablica przyleganie(sasiezdtwa) wezlow
// rozmiar tablicy to bedzie V (wszystkie wierzcholki)
struct Graph {
    int V;
    AdjList* arr;
};

// zmienne globalne
int n; // liczba wierzcholkow
bool* visited;

AdjListNode* newAdjListNode(int);
Graph* createGraph(int);
void addEdge(Graph*, int, int);
void printGraph(Graph*);
void BFS(Graph*, int v); // procedura przejscia wszerz
void DFS(Graph*, int v); // procedura przejscia wzdłuż

int main() {
    // przykladowy nowy graf
    int totalVertices = 4;
    n = totalVertices;
    Graph* graph;
    graph = createGraph(totalVertices);

    // polaczenie wezlow
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);

    // wyprintowanie listowej reprezentacji grafu
    printGraph(graph);

    // alokowanie pamięci dla tablicy odwiedzin
    visited = new bool[totalVertices];

    // przejście wszerz
    cout << "BFS- przejscie WSZERZ: ";
    for (int i = 0; i < totalVertices; i++) visited[i] = false;
    BFS(graph, 0);
    cout << endl;

    // przejście wzdłuż
    cout << "DFS- przejscie WZDLUZ: ";
    for (int i = 0; i < totalVertices; i++) visited[i] = false;
    DFS(graph, 0);
    cout << endl;

    delete[] visited;
    delete[] graph->arr;
    delete graph;

    return 0;
}

// stworzenie nowego wezla
AdjListNode* newAdjListNode(int data) {
    AdjListNode* nptr = new AdjListNode;
    nptr->data = data;
    nptr->next = NULL;
    return nptr;
}

// funkcja do tworzenia grafu V - wierzcholkow
Graph* createGraph(int V) {
    Graph* graph = new Graph;
    graph->V = V;
    // tablica przylegania. rozmiar tablicy to V
    graph->arr = new AdjList[V];
    // inicjalizacja NULL (e.g root=NULL)
    for (int i = 0; i < V; i++) {
        graph->arr[i].head = NULL;
    }
    return graph;
}

// dodaj wierzcholek do grafu nieskierowanego
void addEdge(Graph* graph, int src, int dest) {
    // dodanie wierzcholka z src do dest. nowy wierzcholek zostanie dodany do listy przylegania src
    // wezel zostanie dodany na poczatek
    AdjListNode* nptr = newAdjListNode(dest);
    nptr->next = graph->arr[src].head;
    graph->arr[src].head = nptr;

    // polaczenie z dest do src (od nieskierowanego)
    nptr = newAdjListNode(src);
    nptr->next = graph->arr[dest].head;
    graph->arr[dest].head = nptr;
}

// funkcja do wypisania grafu
void printGraph(Graph* graph) {
    // petla po kazdej liscie przylegania
    for (int i = 0; i < graph->V; i++) {
        AdjListNode* root = graph->arr[i].head;
        cout << "Lista przylegania wierzcholkow nr " << i << endl;
        // petla po kazdym wezle w liscie
        while (root != NULL) {
            cout << root->data << " -> ";
            root = root->next;
        }
        cout << endl;
    }
}

// procedura przejscia WSZERZ (BFS)
void BFS(Graph* graph, int v) {
    queue<int> q;

    visited[v] = true;
    q.push(v);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        AdjListNode* temp = graph->arr[curr].head;
        while (temp != NULL) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                q.push(adjVertex);
            }
            temp = temp->next;
        }
    }
}

// procedura przejscia WZDŁUŻ (DFS)
void DFS(Graph* graph, int v) {
    stack<int> s;
    s.push(v);

    while (!s.empty()) {
        int curr = s.top();
        s.pop();

        if (!visited[curr]) {
            visited[curr] = true;
            cout << curr << " ";
        }

        AdjListNode* temp = graph->arr[curr].head;
        while (temp != NULL) {
            int adjVertex = temp->data;
            if (!visited[adjVertex]) {
                s.push(adjVertex);
            }
            temp = temp->next;
        }
    }
}
