#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <malloc.h>
#include <stdio.h>
using namespace std;

#define SHOW(m) printf(#m "=%d-%d\n", after.m, before.m)

//SORTOWANIE NR 1 
//funkcja znajdujaca wartosc max w tablicy
int findMax(int tab[], int size) {
    int max = tab[0];
    for (int i = 1; i < size; i++) {
        if (tab[i] > max) max = tab[i];
    }
    return max;
}

//funkcja znajdujaca wartosc min w tablicy
int findMin(int tab[], int size) {
    int min = tab[0];
    for (int i = 1; i < size; i++) {
        if (tab[i] < min) min = tab[i];
    }
    return min;
}

//sortowanie kubelkowe
void bucketSort(int tab[], int size) {
    int max = findMax(tab, size);

    //stworzenie kubelkow-tablic o rozmiarze max+1
    int* buckets = new int[max + 1](); // inicjalizacja tablicy zerami

    //zliczanie ile razy wystapil dany element
    for (int i = 0; i < size; ++i) {
        ++buckets[tab[i]];
    }

    //przeniesienie elementow do odpowiednich kubelkow
    int idx = 0;
    for (int i = 0; i <= max; ++i) {
        for (int j = 0; j < buckets[i]; ++j) {
            tab[idx++] = i;
        }
    }
    delete[] buckets; //zwolnienie pamieci
}


//SORTOWANIE NR 2
//reprezentacja niestandardowego obiektu
class Obiekt {
public:
    int atr;
    Obiekt(int a) :atr(a) {}
    Obiekt() {}
};

//sortowanie babelkowe dla nstd tablicy
void bubbleSort(Obiekt tab[], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (tab[j].atr > tab[j + 1].atr) {
                //zamien miejscami jesli zla kolejnosc
                Obiekt temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}



//SORTOWANIE NR 3: PARTIAL SORT
// parametr szablonu T do obslugiwania roznych typow danych
template<typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

//lista
template<typename T>
class LList {
private:
    Node<T>* head;
    int size;
public:
    LList() :head(nullptr), size(0) {}

    //dodaj elem na koniec listy
    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) { head = newNode; }
        else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size;
    }

    //wyswietlenie
    void display() const {
        Node<T>* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    //sortowanie czesciowe PARTIAL SORT
    void partialSort(int k) {
        if (k >= size) return; //niepotrzebne sortowanie

        Node<T>* current = head;
        Node<T>* prev = nullptr;

        //wyszukanie k-tego elem w liscie
        for (int i = 0; i < k && current; ++i) {
            prev = current;
            current = current->next;
        }

        //jesli brak k-tego elementu= zakoncz
        if (!current) return;

        //odlaczenie reszty listy od k-tego elem
        if (prev) {
            prev->next = nullptr;
        }

        //sortowanie k pierwszych elem listy
        FirstPartialSort(head);

        //dolaczenie reszty listy
        while (prev->next) {
            prev = prev->next;
        }
        prev->next = current;
    }

private:
    void FirstPartialSort(Node<T>* start) {
        if (!start || !start->next) return;

        Node<T>* sorted = nullptr;
        Node<T>* current = start;

        while (current) {
            Node<T>* next = current->next;
            insertSorted(&sorted, current);
            current = next;
        }
        head = sorted;
    }
    //wstawienie elem w poprawne miejsce w tab
    void insertSorted(Node<T>** headRef, Node<T>* newNode) {
        Node<T>* current;
        if (*headRef == nullptr || (*headRef)->data >= newNode->data) {
            newNode->next = *headRef;
            *headRef = newNode;
        }
        else {
            current = *headRef;
            while (current->next != nullptr && current->next->data < newNode->data) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

};


//sortowanie babelkowe tablicy liczb całkowitych - algorytm sortowania w miejscu 
void babelkowe(int tablica[], int rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar - 1; j++)
        {
            if (tablica[j] > tablica[j + 1]) {
                swap(tablica[j], tablica[j + 1]);
            }
        }
    }
}

//sortowanie przez scalanie - algorytm wymagajacy dodatkowej pamieci 

//funkcja scalajaca
void scal(int tablica[], int const lewy, int const srodkowy, int const prawy) {
    //obliczenie rozmiarow tablic pomocniczych, powstalych po podziale:
    int const rozmiarLewejTablicy = srodkowy - lewy + 1;
    int const rozmiarPrawejTablicy = prawy - srodkowy;

    //podzial tablicy na 2 tablice:
    auto* lewaTablica = new int[rozmiarLewejTablicy];
    auto* prawaTablica = new int[rozmiarPrawejTablicy];
    for (auto i = 0; i < rozmiarLewejTablicy; i++) {
        lewaTablica[i] = tablica[lewy + i];
    }
    for (auto j = 0; j < rozmiarPrawejTablicy; j++) {
        prawaTablica[j] = tablica[srodkowy + 1 + j];
    }

    //laczenie tablic z rownoczesnym sortowaniem elementow:
    auto indeksLewejTablicy = 0, indeksPrawejTablicy = 0;
    int indeksScalonejTablicy = lewy;
    while (indeksLewejTablicy < rozmiarLewejTablicy && indeksPrawejTablicy < rozmiarPrawejTablicy) {
        if (lewaTablica[indeksLewejTablicy] < prawaTablica[indeksPrawejTablicy]) {
            tablica[indeksScalonejTablicy] = lewaTablica[indeksLewejTablicy];
            indeksLewejTablicy++;
        }
        else {
            tablica[indeksScalonejTablicy] = prawaTablica[indeksPrawejTablicy];
            indeksPrawejTablicy++;
        }
        indeksScalonejTablicy++;
    }

    //dopisanie do tablicy pozostalych elementow tablic pomocniczych:
    while (indeksLewejTablicy<rozmiarLewejTablicy) {
        tablica[indeksScalonejTablicy] = lewaTablica[indeksLewejTablicy];
        indeksLewejTablicy++;
        indeksScalonejTablicy++;
    }
    while (indeksPrawejTablicy<rozmiarPrawejTablicy) {
        tablica[indeksScalonejTablicy] = prawaTablica[indeksPrawejTablicy];
        indeksPrawejTablicy++;
        indeksScalonejTablicy++;
    }

    delete[] lewaTablica;
    delete[] prawaTablica;
}

//funkcja sortujaca 
void przez_scalanie(int tablica[],int const lewy, int const prawy) {
    if (lewy >= prawy) {
        return;
    }
    int srodkowy = lewy + (prawy - lewy) / 2;
    przez_scalanie(tablica, lewy, srodkowy);
    przez_scalanie(tablica, srodkowy + 1, prawy);
    scal(tablica, lewy, srodkowy, prawy);
}



//sortowanie pozycyjne - algorytm wymagajacy dodatkowej pamieci
//funkcja sortujaca liczby wg cyfr na ustalonej pozycji
void sortuj_pozycje(int tablica[], int rozmiar, int pozycja) {
    //deklaracja tablicy licznikow poszczegolnych cyfr 0-9 na ustalonej pozycji (np jednosci, dziesiątek itd)
    int licznik[10] = { 0 };

    //liczenie wystapien poszczegolnych cyfr 0-9 na danej pozycji
    for (int i=0;i<rozmiar;i++) {
        licznik[(tablica[i]/pozycja) % 10]++;
    }

    //dla kazdej cyfry 0-9 (na ustalonej pozycji) obliczamy ostanie jej wystapienie w sortoanej tablicy
    for (int i = 1; i < 10; i++) {
        licznik[i] =licznik[i] + licznik[i - 1];

    }

    //deklarujemy nowa tablice pomocnicza i wypelniamy ja elementami sortowanej tablicy wg wyzej ustalonego porzadku
    int *tab =new int [rozmiar];
    for (int i = rozmiar-1; i >= 0; i--) {
        tab[--licznik[(tablica[i] / pozycja) % 10]]=tablica[i];
    }

    //kopiujemy czesciowo posortowana tablice pomocnicza do sortowanej tablicy
    for (int i = 0; i < rozmiar;i++) {
        tablica[i] = tab[i];
    }

}

//funkcja sortujaca 
void pozycyjne(int tablica[], int rozmiar) {
    int max = findMax(tablica, rozmiar);
    for (int pozycja = 1; (max / pozycja) > 0; pozycja *= 10) {
        sortuj_pozycje(tablica,rozmiar,pozycja);
    }
}

//algorytm hybrydowy 
void hybrydowy(int tablica[],int rozmiar) {
    int min = findMin(tablica, rozmiar);
    int max = findMax(tablica, rozmiar); 
    int zakres = max - min; 

    if (rozmiar >=500) {
        bucketSort(tablica, rozmiar);
    }
    if (rozmiar < 500 && zakres >= 1000) {
        pozycyjne(tablica,rozmiar);
    }
    else {
        bucketSort(tablica, rozmiar);
    }

}

int main()
{
    srand(time(0)); //generator liczb losowych-inicjalizacja
    const int size = 10000;


    //tworzenie tablicy
    int tab[size];
    for (int i = 0; i < size; ++i) {
        tab[i] = rand() % 1000; //losowe liczby 0-999
    }

    //SORTOWANIE NR 1 KUBELKOWE
    int tab2[size];
    copy(tab, tab + size, tab2);
    //sortowanie bucketSort
    auto start = std::chrono::steady_clock::now();
    bucketSort(tab2, size);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "bucketSort: " << duration.count() << " mikrosekund" << endl;

    //tablica nstd obiektów
    Obiekt obiekt[size];
    for (int i = 0; i < size; ++i) {
        //losowe wartosci i wsadzenie do obiektu
        int randomAtr = rand() % 1000; //0-999
        obiekt[i] = Obiekt(randomAtr);
    }

    //SORTOWANIE NR 2 NIESTANDARDOWE
    //sortowanie nstd tablicy
    auto start1 = std::chrono::steady_clock::now();
    bubbleSort(obiekt, size);
    auto end1 = std::chrono::steady_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    cout << "niestandardowe sortowanie: " << duration1.count() << " mikrosekund" << endl;


    //SORTOWANIE NR 3 CZESCIOWE
    const int k = 10; //liczba pierwszych liczb do sortowania

    //tworzenie listy 
    LList<int> lista;
    for (int i = 0; i < size; ++i) {
        lista.push_back(rand() % 1000);
    }

    auto start2 = std::chrono::steady_clock::now();
    //wykonanie sortowania 
    lista.partialSort(k);
    auto end2 = std::chrono::steady_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    cout << "czesciowe sortowanie: " << duration2.count() << " mikrosekund" << endl;

    cout << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl; 
    cout << endl;

    int tab3[size], tab4[size], tab5[size], tab6[size];
    copy(tab, tab + size, tab3);
    copy(tab, tab + size, tab4);
    copy(tab, tab + size, tab5);
    copy(tab, tab + size, tab6);

    //sortowanie babelkowe
    auto start3 = std::chrono::steady_clock::now();
    babelkowe(tab3, size);
    auto end3 = std::chrono::steady_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);
    cout << "Sortowanie Babelkowe: " << duration3.count() << " mikrosekund" << endl;

    //sortowanie kubelkowe
    auto start4 = std::chrono::steady_clock::now();
    bucketSort(tab4, size);
    auto end4 = std::chrono::steady_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4);
    cout << "Sortowanie Kubelkowe: " << duration4.count() << " mikrosekund" << endl;

    //sortowanie przez scalanie
    auto start5 = std::chrono::steady_clock::now();
    przez_scalanie(tab5,0, size-1);
    auto end5 = std::chrono::steady_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(end5 - start5);
    cout << "Sortowanie Przez Scalanie: " << duration5.count() << " mikrosekund" << endl;

    //sortowanie pozycyjne
    auto start6 = std::chrono::steady_clock::now();
    pozycyjne(tab6, size);
    auto end6 = std::chrono::steady_clock::now();
    auto duration6 = std::chrono::duration_cast<std::chrono::microseconds>(end6 - start6);
    cout << "Sortowanie Pozycyjne: " << duration6.count() << " mikrosekund" << endl;


    return 0;
}
