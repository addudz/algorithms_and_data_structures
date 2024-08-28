#include <iostream>
#include <cstdlib>
#include <random>
using namespace std;


struct BSTNode {
    int key;
    BSTNode* Left;
    BSTNode* Right;
    BSTNode* Parent;

    //BSTNode(int x) : key(x), Left(nullptr), Right(nullptr) {}
    static BSTNode* insert(BSTNode* node, int key);
    static BSTNode* inOrderSuccessor(BSTNode* n);
    BSTNode* min(BSTNode* root);
    BSTNode* rremove(BSTNode* node, int z);
};

class FlightScheduler {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int key) {
        if (node == NULL)
        {
            node = new BSTNode;
            node->key = key;
            node->Left = NULL;
            node->Right = NULL;
            node->Parent = NULL;
        }
        else if (node->key < key) {
            node->Right = insert(node->Right, key);
            node->Right->Parent = node;
        }
        else
        {
            node->Left = insert(node->Left, key);
            node->Left->Parent = node;
        }

        return node;
    }

    bool find(BSTNode* node, int val) {
        if (node == nullptr) {
            return false;
        }

        if (node->key == val) {
            return true;
        }
        else if (val < node->key) {
            return find(node->Left, val);
        }
        else {
            return find(node->Right, val);
        }
    }

    void printTreeInOrder(BSTNode* node) {
        if (node == NULL) {
            return;
        }
        if (node->Left) {
            printTreeInOrder(node->Left);

        }
        cout << node->key << endl;
        if (node->Right) {
            printTreeInOrder(node->Right);
        }
    }

    bool canReserveLanding(BSTNode* node, int time, int current_time) {
        if (node == nullptr) {
            return true;
        }

        if (abs(node->key - time) < 3 || time < current_time) {
            return false;
        }

        if (time < node->key) {
            return canReserveLanding(node->Left, time, current_time);
        }
        else {
            return canReserveLanding(node->Right, time, current_time);
        }
    }

    //wyszukiwanie minimum
    BSTNode* min(BSTNode* root) {
        while (root->Left) {
            root = root->Left;
        }
        return root;
    }

    //znajdowanie nastepnika
    BSTNode* inOrderSuccessor(BSTNode* n) {
        if (n->Right) return min(n->Right);
        BSTNode* y = n->Parent;
        while ((y == y->Right) && (n == y->Right)) {
            n = y;
            y = y->Parent;
        }
        return y;
    }

    BSTNode* rremove(BSTNode* node, int z) {
        if (node == nullptr) {
            return node;
        }

        // Znajdź węzeł do usunięcia
        if (z < node->key) {
            node->Left = rremove(node->Left, z);
        }
        else if (z > node->key) {
            node->Right = rremove(node->Right, z);
        }
        else {
            // Węzeł do usunięcia został znaleziony

            // Przypadek 1: Węzeł jest liściem lub ma jedno dziecko
            if (node->Left == nullptr) {
                BSTNode* temp = node->Right;
                delete node;
                return temp;
            }
            else if (node->Right == nullptr) {
                BSTNode* temp = node->Left;
                delete node;
                return temp;
            }

            // Przypadek 2: Węzeł ma dwoje dzieci
            BSTNode* temp = min(node->Right);
            node->key = temp->key;
            node->Right = rremove(node->Right, temp->key);
        }

        return node;
    }
    

public:
    FlightScheduler() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    bool find(int val) {
        return find(root, val);
    }

    void printSchedule() {
        cout << "Planowane zdarzenia: "<<endl;
        printTreeInOrder(root);
        cout << endl;
    }

    void reserveLanding(int time, int current_time) {
        if (canReserveLanding(root, time, current_time)) {
            insert(time);
            cout << "Proba rezerwacji " << time << " zakonczona SUKCESEM :)." << endl;
        }
        else {
            cout << "Proba rezerwacji " << time << " zakonczona ODMOWA :(." << endl;
        }
    }
    int generate_random_time(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
    void remove(int val) {
        root = rremove(root, val);
    }
};

int main() {
    FlightScheduler flightScheduler;

    //aktualny czas
    int current_time = flightScheduler.generate_random_time(0, 60);
    cout << "Aktualny czas: " << current_time << endl;

    //zmienna pomocnicza
    int s1 = current_time;
    int s2 = current_time + 3;
    int s3 = current_time + 9;
    int s4 = current_time + 18;
    //wypelnione rezerwacje
    flightScheduler.insert(s1);
    flightScheduler.insert(s2);
    flightScheduler.insert(s3);
    flightScheduler.insert(s4);

    //wydruk biezacych rezerwacji
    flightScheduler.printSchedule();

    //proba dokonania rezerwacji
    cout << "Ile nowych rezerwacji chcesz wprowadzic? Podaj liczbe naturalna: ";
    int numberReservation;
    cin >> numberReservation;
    for (int i = 0; i < numberReservation; i++) {
        cout << "Wprowadz nowa rezerwacje (wartosc calkowita): ";
        int newReservation;
        cin >> newReservation;
        flightScheduler.reserveLanding(newReservation, current_time);
        int newTime = current_time + 1;
        cout << endl<<"Aktualny czas: " << newTime << endl;

        if (newTime > s1) flightScheduler.remove(s1);
        if (newTime > s2) flightScheduler.remove(s2);
        if (newTime > s3) flightScheduler.remove(s3);
        if (newTime > s4) flightScheduler.remove(s4);

    }
    //wydruk aktualnych rezerwacji
    cout << endl << "AKTUALNE planowane rezerwacje: " << endl;
    flightScheduler.printSchedule();
    return 0;
}
