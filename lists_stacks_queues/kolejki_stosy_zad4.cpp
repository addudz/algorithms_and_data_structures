#include <iostream>
using namespace std;
//------------------------------------zad4------------------------------
// Struktura reprezentująca element listy
struct ListNode {
    int data;
    ListNode* next;

    ListNode(int value) : data(value), next(nullptr) {}
};

// Klasa reprezentująca listę
class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() : head(nullptr) {}

    // Metoda dodająca element na koniec listy
    void append(int value) {
        ListNode* newNode = new ListNode(value);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            ListNode* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Metoda wyświetlająca zawartość listy
    void display() {
        ListNode* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Metoda łącząca dwie listy naprzemiennie
    void merge(LinkedList& otherList) {
        if (otherList.head == nullptr) {
            return; // Nie ma nic do dołączenia, druga lista jest pusta }

        ListNode* current = head;
        ListNode* otherCurrent = otherList.head;
        ListNode* prev = nullptr;

        while (current != nullptr && otherCurrent != nullptr) {
            ListNode* nextNode = current->next;

            // Wstawiamy element z drugiej listy przed bieżącym elementem z pierwszej listy
            otherList.head = otherCurrent->next;
            otherCurrent->next = current->next;
            current->next = otherCurrent;
            current = otherCurrent->next;

            prev = otherCurrent; // Aktualizujemy wskaźnik poprzednika
            otherCurrent = otherList.head;
        }

        if (otherCurrent != nullptr) {
            // Dołączamy pozostałe elementy listy drugiej na koniec listy pierwszej
            if (current == nullptr) {
                // Wstawiamy na koniec listy pierwszej
                prev->next = otherCurrent;
            }
            else {
                // Wstawiamy po ostatnim elemencie listy pierwszej
                ListNode* lastNode = current;
                while (lastNode->next != nullptr) {
                    lastNode = lastNode->next;
                }
                lastNode->next = otherCurrent;
            }
            otherList.head = nullptr; // Druga lista jest teraz pusta
        }
    }

    // Destruktor usuwający elementy listy
    ~LinkedList() {
        while (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list1;
    list1.append(1);
    list1.append(3);
    list1.append(5);

    LinkedList list2;
    list2.append(2);
    list2.append(4);
    list2.append(6);
    list2.append(8);

    cout << "Lista 1 przed polaczeniem: ";
    list1.display();

    cout << "Lista 2 przed polaczeniem: ";
    list2.display();

    list1.merge(list2);

    cout << "Lista 1 po polaczeniu: ";
    list1.display();

    cout << "Lista 2 po polaczeniu: ";
    list2.display(); // Lista 2 powinna być teraz pusta

    return 0;
}
