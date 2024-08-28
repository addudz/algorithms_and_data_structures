
#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubblesort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insert_sort(int array[], int size) {
    for (int step = 1; step < size; step++) {
        int key = array[step];
        int j = step - 1;

        while (j >= 0 && key < array[j]) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

void select_sort(int tab[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (tab[j] < tab[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(tab[i], tab[min_index]);
        }
    }
}

void comb_sort(int tab[], int size) {
    int gap = size;
    bool swapped = true;
    while (gap > 1 || swapped) {
        gap = max(1, int(gap / 1.3));
        swapped = false;
        for (int i = 0; i < size - gap; ++i) {
            int j = i + gap;
            if (tab[i] > tab[j]) {
                swap(tab[i], tab[j]);
                swapped = true;
            }
        }
    }
}

void shell_sort(int tab[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            int temp = tab[i];
            int j;
            for (j = i; j >= gap && tab[j - gap] > temp; j -= gap) {
                tab[j] = tab[j - gap];
            }
            tab[j] = temp;
        }
    }
}

int generate_random(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

int main() {
    const int size = 10000;
    int tab[size];
    for (int i = 0; i < size; i++) {
        tab[i] = generate_random(0, 10000);
    }

    int tab2[size];
    copy(tab, tab + size, tab2);
    auto start = high_resolution_clock::now();
    bubblesort(tab2, size);
    auto end = high_resolution_clock::now();
    cout << "Bubblesort: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;

    int tab3[size];
    copy(tab, tab + size, tab3);
    start = high_resolution_clock::now();
    insert_sort(tab3, size);
    end = high_resolution_clock::now();
    cout << "Insertion sort: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;

    int tab4[size];
    copy(tab, tab + size, tab4);
    start = high_resolution_clock::now();
    select_sort(tab4, size);
    end = high_resolution_clock::now();
    cout << "Selection sort: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;

    int tab5[size];
    copy(tab, tab + size, tab5);
    start = high_resolution_clock::now();
    comb_sort(tab5, size);
    end = high_resolution_clock::now();
    cout << "Comb sort: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;

    int tab6[size];
    copy(tab, tab + size, tab6);
    start = high_resolution_clock::now();
    shell_sort(tab6, size);
    end = high_resolution_clock::now();
    cout << "Shell sort: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;

    return 0;
}
