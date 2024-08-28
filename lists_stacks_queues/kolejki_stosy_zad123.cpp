
#include <iostream>
using namespace std; 

// stała określająca maksymalny rozmiar stosu
const int MAX_SIZE = 100;


//klasa elementu stosu
class StackNode {
public:
     int data;
    StackNode* next;

    StackNode( int value) :data(value), next(nullptr) {} //konstruktor
};

//klasa stosu
class Stack {
private:
    StackNode* top;

public:
    Stack() :top(nullptr) {} //konstruktor
    ~Stack() {
        while (!isEmpty()) {
            pop();
        } //destruktor
    }
    bool isEmpty() {
        return top == nullptr;
    } //metoda ktora sprawdza czy stos jest pusty

    void push( int value) {
        StackNode* newNode = new StackNode(value);
        newNode->next = top;
        top = newNode;
    } //metoda dodajaca nowy element na wierzcholek stosu

    void pop() {
        if (isEmpty()) {
            cout << "stos jest pusty, nie da sie usunac elementu" << endl;
            return;
        }
        StackNode* temp = top;
        top = top->next;
        delete temp;
    } //metoda usuwajaca elementy ze stosu

    int peek() {
        if (!isEmpty()) {
            return top->data;
        }
        return -1; //zwrot gdy stos pusty
    } //metoda zwracajaca wierzcholek stosu

    void reverseWithSecondStack() {
        Stack secondStack; // Tworzymy drugi stos, w którym umieścimy odwróconą zawartość

        // Przepisujemy zawartość oryginalnego stosu na drugi stos (czyli odwracamy)
        while (!isEmpty()) {
            secondStack.push(peek());
            pop();
        }

        // Kopiujemy odwróconą zawartość z drugiego stosu na oryginalny
        while (!secondStack.isEmpty()) {
            push(secondStack.peek());
            secondStack.pop();
        }
    }


    void reverseWithoutSecondStack() {
        StackNode* prev = nullptr;
        StackNode* current = top;
        StackNode* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }

        top = prev; // Nowy wierzchołek stosu staje się ostatnim elementem
    }
};


class Stack_tab {
private:
    int array[MAX_SIZE];
    int top;

public:
    Stack_tab() : top(-1) {}

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX_SIZE - 1;
    }

    void push(int value) {
        if (!isFull()) {
            array[++top] = value;
        }
        else {
            std::cout << "Stos jest pelny, nie mozna dodac elementu." << std::endl;
        }
    }

    void pop() {
        if (!isEmpty()) {
            --top;
        }
        else {
            std::cout << "Stos jest pusty, nie mozna usunac elementu." << std::endl;
        }
    }

    int peek() {
        if (!isEmpty()) {
            return array[top];
        }
        else {
            std::cout << "Stos jest pusty, nie ma zadnego elementu do pobrania." << std::endl;
            return -1; // Zwracamy wartość domyślną dla pustego stosu
        }
    }

    // Usuwa element ze stosu na pozycji n (licząc od wierzchołka stosu)
    void removeElementFromPosition(int n) {
        if (isEmpty()) {
            std::cout << "Stos jest pusty, nie ma elementow do usuniecia." << std::endl;
            return;
        }

        if (n <= 0 || n > top + 1) {
            std::cout << "Nieprawidlowa pozycja elementu do usuniecia." << std::endl;
            return;
        }

        for (int i = top - n + 1; i < top; ++i) {
            array[i] = array[i + 1];
        }

        --top;
    }
};

//------------------------------------zad1------------------------------------------
//Funkcja ktora wybiera liczby bedace wielokrotnosciami 'l' z ciagu liczb naturalnych
//i ustawia je na stosie
void StosL( int* ciag, int M, int l, Stack& stos) {
    {
        for (int i = 0; i < M; i++) {
            if (ciag[i] % l == 0) {
                stos.push(ciag[i]);
            }
        }
    }
}

//dla stacktab
void StosL_tab(int* ciag, int M, int l, Stack_tab& stos) {
    {
        for (int i = 0; i < M; i++) {
            if (ciag[i] % l == 0) {
                stos.push(ciag[i]);
            }
        }
    }
}



int main(){
     int ciag[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    int M = sizeof(ciag) / sizeof(ciag[0]);
    int l = 2;
    Stack stos;
    StosL(ciag, M, l, stos);

    //wyswietlenie
    cout << "zawartosc stosu z wielokrotnosciami liczby l= " << l << endl;
    while (!stos.isEmpty()) {
        cout << stos.peek() << " ";
        stos.pop();
    }
    cout << endl;

    StosL(ciag, M, l, stos);
    // Obracanie zawartości stosu przy użyciu drugiego stosu 2a)
    stos.reverseWithSecondStack();

    //----------------------------------zad2a)-------------------------------
    cout << "Zawartosc stosu po odwroceniu: ";
    // Tworzymy nowy stos, na którym umieścimy odwróconą zawartość
    Stack reversedStack;
    while (!stos.isEmpty()) {
        // Przepisujemy zawartość odwróconego stosu na nowy stos
        reversedStack.push(stos.peek());
        stos.pop();
    }

    // Wyświetlamy zawartość nowego stosu
    while (!reversedStack.isEmpty()) {
        cout << reversedStack.peek() << " ";
        reversedStack.pop();
    }
    cout << endl;
    
    // Ponowne umieszczenie elementów na stosie
    StosL(ciag, M, l, stos);

    //----------------------------zad 2b)------------------------
    // Obracanie zawartości stosu bez użycia drugiego stosu 2b)
    stos.reverseWithoutSecondStack();

    cout << "Zawartosc stosu po odwroceniu: ";
    while (!stos.isEmpty()) {
        cout << stos.peek() << " ";
        stos.pop();
    }
    cout << endl;

    //-----------------------------------zad.3. stos tablicowy--------------------------
    Stack_tab stacktab;
    StosL_tab(ciag, M, l, stacktab);
    // Wyświetlamy zawartość stosu
    cout << "Zawartosc stosu_tab: ";
    while (!stacktab.isEmpty()) {
        cout << stacktab.peek() << " ";
        stacktab.pop();
    }
    cout << endl;
    //ponowne wypelnienie
    StosL_tab(ciag, M, l, stacktab);
    // Usuwamy element na pozycji 3 (licząc od wierzchołka stosu)
    stacktab.removeElementFromPosition(3);

    // Wyświetlamy zawartość stosu po usunięciu elementu
    cout << "Zawartosc stosu_tab po usunieciu elementu na pozycji 3: ";
    while (!stacktab.isEmpty()) {
        cout << stacktab.peek() << " ";
        stacktab.pop();
    }
    cout << endl;
    
    

    return 0;
}
