#include <iostream>
using namespace std;

// Stała określająca maksymalny rozmiar kolejki
const int MAX_SIZE = 100;

// Struktura reprezentująca kolejkę
class Kolejka {
private:
    int tablica[MAX_SIZE];
    int przod;
    int tyl;

public:
    Kolejka() : przod(-1), tyl(-1) {}

    // Metoda sprawdzająca, czy kolejka jest pusta
    bool CzyPusta() {
        return przod == -1 && tyl == -1;
    }

    // Metoda sprawdzająca, czy kolejka jest pełna
    bool CzyPelna() {
        return (tyl + 1) % MAX_SIZE == przod;
    }

    // Metoda dodająca element do kolejki
    void dodajElement(int value) {
        if (CzyPelna()) {
            cout << "Kolejka jest pełna, nie można dodać elementu." << endl;
            return;
        }

        if (CzyPusta()) {
            przod = tyl = 0;
        }
        else {
            tyl = (tyl + 1) % MAX_SIZE;
        }
        tablica[tyl] = value;
    }

    // Metoda usuwająca element z kolejki o wartości x
    
    void UsunX(int x) {
        if (CzyPusta()) {
            cout << "Kolejka jest pusta, nie ma elementów do usunięcia." << endl;
            return;
        }

        bool znaleziony = false;
        int indeks = przod;
        int znalezionyIndeks = -1; // Indeks znalezionego elementu

        while (indeks != (tyl + 1) % MAX_SIZE) {
            if (tablica[indeks] == x) {
                znaleziony = true;
                znalezionyIndeks = indeks;
                break;
            }
            indeks = (indeks + 1) % MAX_SIZE;
        }

        if (znaleziony) {
            // Usuwamy element z kolejki
            if (przod == tyl) {
                // Kolejka ma tylko jeden element
                przod = tyl = -1;
            }
            else if (znalezionyIndeks == tyl) {
                // Usuwamy ostatni element kolejki
                tyl = (tyl - 1 + MAX_SIZE) % MAX_SIZE;
            }
            else {
                // Usuwamy element z dowolnej pozycji w kolejce
                for (int i = znalezionyIndeks; i != tyl; i = (i + 1) % MAX_SIZE) {
                    tablica[i] = tablica[(i + 1) % MAX_SIZE];
                }
                tyl = (tyl - 1 + MAX_SIZE) % MAX_SIZE; // Zmniejszamy tyl o 1
            }
            cout << "Usunięto element " << x << " z kolejki." << endl;
        }
        else {
            cout << "Nie znaleziono elementu " << x << " w kolejce." << endl;
        }
    }



    // Metoda usuwająca element z kolejki
    void usunElement() {
        if (CzyPusta()) {
            cout << "Kolejka jest pusta, nie można usunąć elementu." << endl;
            return;
        }

        if (przod == tyl) {
            przod = tyl = -1;
        }
        else {
            przod = (przod + 1) % MAX_SIZE;
        }
    }

    // Metoda zwracająca element z przodu kolejki
    int wierzcholek() {
        if (CzyPusta()) {
            cout << "Kolejka jest pusta, nie ma elementu do pobrania." << endl;
            return -1; // Zwracamy wartość domyślną dla pustej kolejki
        }
        return tablica[przod];
    }
};

int main() {
    Kolejka kolejka;
    kolejka.dodajElement(1);
    kolejka.dodajElement(2);
    kolejka.dodajElement(3);
    kolejka.dodajElement(4);
    kolejka.dodajElement(5);

    cout << "Kolejka przed usunięciem elementu: ";
    while (!kolejka.CzyPusta()) {
        cout << kolejka.wierzcholek() << " ";
        kolejka.usunElement();
    }
    cout << endl;

    kolejka.dodajElement(1);
    kolejka.dodajElement(2);
    kolejka.dodajElement(3);
    kolejka.dodajElement(4);
    kolejka.dodajElement(5);

    kolejka.UsunX(3);

    cout << "Kolejka po usunięciu elementu 3: ";
    while (!kolejka.CzyPusta()) {
        cout << kolejka.wierzcholek() << " ";
        kolejka.usunElement();
    }
    cout << endl;

    return 0;
}
