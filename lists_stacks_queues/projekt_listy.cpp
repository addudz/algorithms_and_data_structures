
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Prezydent {
private:
    string imie;
    string drugie_imie;
    string nazwisko;
    int kadencjaStart;
    int kadencjaEnd;
    string partia;
    //Prezydent* next;
public:
    Prezydent* next;
    Prezydent(string imie, string drugie_imie, string nazwisko, int kadencjaStart, int kadencjaEnd, string partia, Prezydent* next = nullptr) {
        this->imie = imie;
        this->drugie_imie = drugie_imie;
        this->nazwisko = nazwisko;
        this->kadencjaStart = kadencjaStart;
        this->kadencjaEnd = kadencjaEnd;
        this->partia = partia;
        this->next = next;
    }
    //gettery
    string getImie() {
        return imie;
    }
    string getDrugie_imie() {
        return drugie_imie;
    }
    string getNazwisko() {
        return nazwisko;
    }
    int	getKadencjaStart() {
        return kadencjaStart;
    }
    int	getKadencjaEnd() {
        return kadencjaEnd;
    }
    string	getPartia() {
        return partia;
    }
    //settery
    void setImie(string i) {
        imie = i;
    }
    void setDrugie_imie(string di) {
        drugie_imie = di;
    }
    void setNazwisko(string n) {
        nazwisko = n;
    }
    void setKadencjaStart(int ks) {
        kadencjaStart = ks;
    }
    void setKadencjaEnd(int ke) {
        kadencjaEnd = ke;
    }
    void setPartia(string pp) {
        partia = pp;
    }

    int dlugoscKadencji() const {
        return kadencjaEnd - kadencjaStart;
    }
};

class ListaPrezydentow {
public:
    Prezydent* head;

    ListaPrezydentow() : head(nullptr) {}

    ~ListaPrezydentow() {
        Prezydent* current = head;
        while (current != nullptr) {
            Prezydent* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void DodajPrezydenta(string imie, string drugie_imie, string nazwisko, int kadencjaStart, int kadencjaEnd, string partia) {
        Prezydent* newPresident = new Prezydent(imie, drugie_imie, nazwisko, kadencjaStart, kadencjaEnd, partia);
        if (head == nullptr) {
            head = newPresident;
        }
        else {
            Prezydent* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newPresident;
        }
    }

    void WyswietlPrezydenta() const {
        Prezydent* current = head;
        while (current != nullptr) {
            cout << current->getImie << " " << current->getDrugie_imie << " " << current->getNazwisko << " (" << current->getDlugoscKadencji()
                << " lat, " << current->getPartia << ")" << endl;
            current = current->next;
        }
    }

    void WyswietlLata() const {
        Prezydent* current = head;
        while (current != nullptr) {
            cout << "(" << current->getKadencjaStart << " - " << current->getKadencjaEnd << ")" << endl;
            current = current->next;
        }
    }

    Prezydent* NajkrotszyPrezydent() {
        if (head == nullptr) {
            return nullptr;
        }
        // Znajdź najkrótszą długość kadencji
        int najkrotszaKadencja = head->dlugoscKadencji();
        Prezydent* current = head->next;
        while (current != nullptr) {
            if (current->dlugoscKadencji() < najkrotszaKadencja) {
                najkrotszaKadencja = current->dlugoscKadencji();
            }
            current = current->next;
        }
        // Utwórz listę prezydentów o najkrótszej kadencji zad1
        Prezydent* ListaNajkrotszychPrezydentow = nullptr;
        current = head;
        while (current != nullptr) {
            if (current->dlugoscKadencji() == najkrotszaKadencja) {
                Prezydent* newPresident = new Prezydent(current->getImie, current->getDrugie_imie, current->getNazwisko,
                    current->getKadencjaStart, current->getKadencjaEnd, current->getPartia);
                newPresident->next = ListaNajkrotszychPrezydentow;
                ListaNajkrotszychPrezydentow = newPresident;
            }
            current = current->next;
        }

        return ListaNajkrotszychPrezydentow;
    }

    Prezydent* TaSamaPartia(string party) {

        //znajdz ta sama partie polityczna zad2
        Prezydent* kolejny = head->next;
        Prezydent* prezydenciPartii = nullptr;
        while (head != nullptr) {
            if (head->getPartia == party) {
                Prezydent* newPresident = new Prezydent(head->getImie, head->getDrugie_imie, head->getNazwisko,
                    head->getKadencjaStart, head->getKadencjaEnd, head->getPartia);
                newPresident->next = prezydenciPartii;
                prezydenciPartii = newPresident;
            }
            head = head->next;
        }
        return prezydenciPartii;
    }
    //kto wtedy rzadzil zad3
    Prezydent* KtoRzadzil(int rok) {

        Prezydent* current = head; // Używamy kopii początkowego wskaźnika head
        Prezydent* prezydenciRzady = nullptr;
        while (current != nullptr) {
            if (rok >= current->getKadencjaStart && rok <= current->getKadencjaEnd) {
                Prezydent* newPresident = new Prezydent(current->getImie, current->getDrugie_imie, current->getNazwisko,
                    current->getKadencjaStart, current->getKadencjaEnd, current->getPartia);
                newPresident->next = prezydenciRzady;
                prezydenciRzady = newPresident;
            }
            current = current->next;
        }
        return prezydenciRzady;
    }

};

int main() {
    ListaPrezydentow listaprezydentow;

    // Wczytanie prezydentów z pliku i dodanie ich do listy
    ifstream file("presidents.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string imie, drugie_imie, nazwisko, partia;
            int kadencjaStart, kadencjaEnd;
            char comma;
            if (iss >> imie >> drugie_imie >> nazwisko >> kadencjaStart >> comma >> kadencjaEnd >> comma >> partia) {
                listaprezydentow.DodajPrezydenta(imie, drugie_imie, nazwisko, kadencjaStart, kadencjaEnd, partia);
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }

    // Wyświetlenie wszystkich prezydentów zad0 PROBA TESTOWA
    cout << "Wszyscy prezydenci:" << endl << endl;
    listaprezydentow.WyswietlPrezydenta();
    cout << endl;


    //ZAD3 PREZYDENCI RZADZACY W DANYM ROKU
    cout << endl << "---------------------------------------------------------------------------------------" << endl;
    int rok;
    cout << "Mam dane o prezydentach rzadzacych w latach: " << endl;
    listaprezydentow.WyswietlLata();
    cout << endl;
    cout << endl << "Podaj konkretny rok, zeby sprawdzic kto wtedy rzadzil." << endl;
    cout << "Rok: ";
    cin >> rok;
    Prezydent* podanyrok = listaprezydentow.KtoRzadzil(rok);

    cout << endl << "W roku " << rok << " rzadzily nastepujace osoby: " << endl << endl;
    while (podanyrok != nullptr) {
        cout << podanyrok->getImie << " " << podanyrok->getDrugie_imie << " " << podanyrok->getNazwisko << " ("
            << podanyrok->getDlugoscKadencji() << " lat, " << podanyrok->getPartia << ")" << endl;
        Prezydent* temp = podanyrok;
        podanyrok = podanyrok->next;
        delete temp;
    }



    // Znalezienie i wyświetlenie prezydentów o najkrótszej kadencji;ZAD 1
    Prezydent* shortestPresidents = listaprezydentow.NajkrotszyPrezydent();
    cout << endl << "---------------------------------------------------------------------------------------" << endl;
    cout << endl << "Prezydenci o najkrotszej kadencji:" << endl;
    while (shortestPresidents != nullptr) {
        cout << shortestPresidents->imie << " " << shortestPresidents->drugie_imie << " "
            << shortestPresidents->nazwisko << " (" << shortestPresidents->dlugoscKadencji() << " lat, "
            << shortestPresidents->partia << ")" << endl;
        Prezydent* temp = shortestPresidents;
        shortestPresidents = shortestPresidents->next;
        delete temp;
    }

    //ZAD 2 PREZYDENCI DANEJ PARTII
    int wybor;
    string nazwa_partii;
    cout << endl << "---------------------------------------------------------------------------------------" << endl;
    cout << endl << "Podaj numer (1-6) odpowiadający partii, a dowiesz się jacy prezydenci do niej należeli. " << endl;
    cout << "1. Federalist " << endl;
    cout << "2. Democratic-Republican" << endl;
    cout << "3. Democratic" << endl;
    cout << "4. Whig" << endl;
    cout << "5. Republican" << endl;
    cout << "6. Unaffiliated" << endl;
    cout << "Wybor: ";
    cin >> wybor;


    switch (wybor) {
    case 1:
        nazwa_partii = "Federalist";
        break;
    case 2:
        nazwa_partii = "Democratic-Republican";
        break;
    case 3:
        nazwa_partii = "Democratic";
        break;
    case 4:
        nazwa_partii = "Whig";
        break;
    case 5:
        nazwa_partii = "Republican";
        break;
    case 6:
        nazwa_partii = "Unaffiliated";
        break;
    default:
        cout << "Podales liczbe spoza dozwolonego zakresu. " << endl;
    }
    Prezydent* tasamapartia = listaprezydentow.TaSamaPartia(nazwa_partii);

    cout << endl << "Zgodnie z Twoim wyborem, oto prezydenci partii " << nazwa_partii << ": " << endl << endl;
    while (tasamapartia != nullptr) {
        cout << tasamapartia->getImie << " " << tasamapartia->getDrugie_imie << " " << tasamapartia->getNazwisko
            << " (" << tasamapartia->dlugoscKadencji() << " lat, " << tasamapartia->getPartia << ")" << endl;
        Prezydent* temp = tasamapartia;
        tasamapartia = tasamapartia->next;
        delete temp;
    }



    //presidentList.kto_rzadzil(rok);
    return 0;
}
