#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include<stdio.h>
#include <chrono>
#include<vector>
#include<stdbool.h>
using namespace std;

int suma = 0;

#define TOTAL_CHARACTERS 256


void badCharacterHeuristic(string s, int n,
    int badCharacter[TOTAL_CHARACTERS]) {

    for (int i = 0; i < TOTAL_CHARACTERS; i++)
        badCharacter[i] = -1;


    for (int i = 0; i < n; i++)
        badCharacter[(int)s[i]] = i;
}


void BoyerMooreAlgorithm(string text, string pattern) {

    int m = pattern.size();
    int n = text.size();


    int badCharacter[TOTAL_CHARACTERS];

    badCharacterHeuristic(pattern, m, badCharacter);


    int shifts = 0;


    while (shifts <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shifts + j])
            j--;

        if (j < 0) {
            // cout << "Pattern found at index: " << shifts << endl;

            shifts += (shifts + m < n) ? m - badCharacter[text[shifts + m]] : 1;
        }


        else
            shifts += max(1, j - badCharacter[text[shifts + j]]);
    }
}




int search_naive(string& pat, string& txt) {
    int M = pat.size();
    int N = txt.size();

    // petla jeden do jeden
    for (int i = 0; i <= N - M; i++) {
        int j;

        // dla obecnego indeksu sprawdz wzorzec
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pat[j]) {
                break;
            }
        }

        // jesli wzorzec odpowiada indeksowi i
        if (j == M) {
            //cout << "wzorzec znaleziony o  indeksie: " << i << endl;
            ++suma;
            //cout << "suma wystapien: " << suma << endl;


        }

    }


    return suma;

}

vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31;
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T));
    p_pow[0] = 1;
    for (int i = 1; i < (int)p_pow.size(); i++)
        p_pow[i] = (p_pow[i - 1] * p) % m;

    vector<long long> h(T + 1, 0);
    for (int i = 0; i < T; i++)
        h[i + 1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m;
    long long h_s = 0;
    for (int i = 0; i < S; i++)
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m;

    vector<int> occurrences;
    for (int i = 0; i + S - 1 < T; i++) {
        long long cur_h = (h[i + S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
            occurrences.push_back(i);
    }
    return occurrences;
}


void computeLPSArray(const string& pattern, vector<int>& lps) {
    int patternLen = pattern.length();
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < patternLen) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}


void KMPSearch(const string& text, const string& pattern) {
    int textLen = text.length();
    int patternLen = pattern.length();

    vector<int> lps(patternLen, 0);

    computeLPSArray(pattern, lps);
    int i = 0;
    int j = 0;
    while (i < textLen) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == patternLen) {
            //cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < textLen && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}



//znajdz najdluzszy prefiks, bedacy sufiksem
string najdluzszyPrefiks(const string& str) {
    int N = str.length();
    // jesli dl <2
    if (N < 2) { return ""; }

    int dl = 0;
    int i = 0;
    //iteracja przez 1sza polowe
    while (i < N / 2) {
        int j1 = 0, j2 = (N - 1) - i;
        int prefiksIsufiks = 1;
        //czy znaki na pozycjach w 1szej i 2giej polowie ciagu sa ==
        while (j1 <= i) {
            //jesli cos nie pasuje to przerwij
            if (str[j1] != str[j2]) {
                prefiksIsufiks = 0;
                break;
            }
            j1++;
            j2++;
        }

        //jesli nie ma niezgodnosci to aktualizacja dl
        if (prefiksIsufiks == 1) { dl = i + 1; }
        i++;
    }
    //zwrot
    return str.substr(0, dl);
}



//znaki wieloznaczne
bool znakiWieloznaczne(const char* in1, const char* in2) {
    //gdy znaleznione koncowi obu strinów=> koniec
    if (*in1 == '\0' && *in2 == '\0') return true;
    //eliminacja kolejnego *
    if (*in1 == '*') {
        while (*(in1 + 1) == '*') in1++;
    }

    if (*in1 == '*' && *(in1 + 1) != '\0' && *in2 == '\0') return false;//text nie zawiera 2woch kolejnych *
    if (*in1 == '?' || *in1 == *in2) return znakiWieloznaczne(in1 + 1, in2 + 1); //gdy text zawiera ? lub text i pattern pasuja do siebie
    if (*in1 == '*') return znakiWieloznaczne(in1 + 1, in2) || znakiWieloznaczne(in1, in2 + 1); // gdy * nalezy sprawdzic biezacy znak in2 albo go zignorowac
    return false;
}

const int MAX_ROWS = 4;
const int MAX_COLS = 4;
const int MAX_len = 100;

bool wzorzec2D(char tab[MAX_ROWS][MAX_COLS], int row, int col, char* pattern, int& startRow, int& startCol) {
    int dl = strlen(pattern);
    int rows = MAX_ROWS;
    int cols = MAX_COLS;

    //poziomo
    if (col + dl <= cols) {
        char horizontal[MAX_len + 1];
        memcpy(horizontal, tab[row] + col, dl);
        horizontal[dl] = '\0';
        if (strcmp(horizontal, pattern) == 0) {
            startRow = row;
            startCol = col;
            return true;
        }
    }

    //pionowo
    if (row + dl <= rows) {
        char vertical[MAX_len + 1];
        for (int i = 0; i < dl; ++i) {
            vertical[i] = tab[row + i][col];
        }
        vertical[dl] = '\0';
        if (strcmp(vertical, pattern) == 0) {
            startRow = row;
            startCol = col;
            return true;
        }
    }

    //po skosie- prawo i dol
    if (row + dl <= rows && col + dl <= cols) {
        char diagonal[MAX_len + 1];
        for (int i = 0; i < dl; ++i) {
            diagonal[i] = tab[row + i][col + i];
        }
        diagonal[dl] = '\0';
        if (strcmp(diagonal, pattern) == 0) {
            startRow = row;
            startCol = col;
            return true;
        }
    }

    //po skosie- lewo i dol
    if (row + dl <= rows && col - dl + 1 >= 0) {
        char diagonal[MAX_len + 1];
        for (int i = 0; i < dl; ++i) {
            diagonal[i] = tab[row + i][col - i];
        }
        diagonal[dl] = '\0';
        if (strcmp(diagonal, pattern) == 0) {
            startRow = row;
            startCol = col;
            return true;
        }
    }

    return false;
}

void szukajWzorzec2D(char tab[MAX_ROWS][MAX_COLS], char* pattern) {
    int rows = MAX_ROWS;
    int cols = MAX_COLS;
    int len = strlen(pattern);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int startRow, startCol;
            if (j + len <= cols && wzorzec2D(tab, i, j, pattern, startRow, startCol)) {
                std::cout << "Znaleziono wzorzec '" << pattern << "' w pozycji rozpoczynajacej sie od id: (" << startRow + 1 << ", " << startCol + 1 << ").\n";
                return;
            }
        }
    }

    std::cout << "Nie znaleziono wzorca '" << pattern << "' w tablicy.\n";
}

int main()
{
    ifstream plik("C:/Users/adria/Desktop/Hobbit.txt");  // Otwarcie pliku 
    string linia;     //  odczytane wierszy tekstu
    string pat = "hobbit";

    if (plik)
    {
        // Udało się otworzyć plik

        while (getline(plik, linia))    // jesli nie koniec pliku, czytamy dalej
        {
           search_naive(pat, linia);
           //rabin_karp(pat, linia);
           //KMPSearch(pat, linia);
          // BoyerMooreAlgorithm(pat, linia);
        }
        cout << "ZADANIE 1" << endl;
        cout << "suma wystapien: " << search_naive(pat, linia) << endl;



    }
    else
    {
        cout << "BŁĄD: nie można otworzyć pliku do odczytu." << endl;
    }




    
    //NAIVE ALGORYTM
    auto begin = std::chrono::high_resolution_clock::now();
    search_naive(pat, linia);
    auto end = std::chrono::high_resolution_clock::now();
    cout << "naive: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl;
    cout << endl;

    cout << "ZADANIE 2" << endl;
    //RUBIN ALGORYTM
    auto begin2 = std::chrono::high_resolution_clock::now();
    rabin_karp(pat, linia);
    auto end2 = std::chrono::high_resolution_clock::now();
    cout << "rubin: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << " microseconds" << endl;
    

    //KMP ALGORYTM
    auto begin3 = std::chrono::high_resolution_clock::now();
    KMPSearch(pat, linia);
    auto end3 = std::chrono::high_resolution_clock::now();
    cout << "kmp: " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << " microseconds" << endl;
    

    //BOYER MOORE ALGORYTM
    auto begin4 = std::chrono::high_resolution_clock::now();
    BoyerMooreAlgorithm(pat, linia);
    auto end4 = std::chrono::high_resolution_clock::now();
    cout << "boyer moore: " << std::chrono::duration_cast<std::chrono::microseconds>(end4 - begin4).count() << " microseconds" << endl;
    cout << endl;

    cout << "ZADANIE 3" << endl;
    //ZNAJDZ NAJDLUZSZY PREFIKS BEDACY SUFIKSEM
    string input = "aabcdaabc";
    string output = najdluzszyPrefiks(input);
    cout << "input: " << input << endl;
    cout << "output: " << output << endl;
    cout << endl;

    cout << "ZADANIE 4" << endl;
    //ZNAKI * ORAZ ?
    cout << "text: " << "baaabab" << endl;
    cout << "input 1: " << "baa?bab" << " -> " << (znakiWieloznaczne("baa?bab", "baaabab") ? "True" : "False") << endl;
    cout << "input 2: " << "a*ab" << " -> " << (znakiWieloznaczne("a*ab", "baaabab") ? "True" : "False") << endl;;
    cout << endl;

    cout << "ZADANIE 5" << endl;
    //tablica 2D i wzorce
    char tab[MAX_ROWS][MAX_COLS] = {
        {'a', 'b', 'c', 'd'},
        {'e', 'f', 'g', 'h'},
        {'i', 'j', 'k', 'l'},
        {'m', 'n', 'o', 'p'}
    };

    std::cout << "Tablica 2D:\n";
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            std::cout << tab[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    char pattern[] = "efg";
    szukajWzorzec2D(tab, pattern);

    return 0;
}

