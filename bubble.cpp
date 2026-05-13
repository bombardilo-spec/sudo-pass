#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

// ---------------- SEQUENTIAL BUBBLE SORT ----------------
void bubbleSequential(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << "Sequential Bubble Sort Done\n";
}

// ---------------- PARALLEL BUBBLE SORT (ODD-EVEN) ----------------
void bubbleParallel(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        int start= i%2;
        #pragma omp parallel for
        for (int j = start; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }

    }

    cout << "Parallel Bubble Sort Done\n";
}

// ---------------- PRINT FUNCTION ----------------
void printArray(vector<int>& arr) {

    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

// ---------------- MAIN ----------------
int main() {

    int n;
    cout << "Enter size: ";
    cin >> n;

    vector<int> original(n);

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> original[i];
    }

    vector<int> a = original;
    vector<int> b = original;

    auto start = chrono::high_resolution_clock::now();
    bubbleSequential(a);
    auto end = chrono::high_resolution_clock::now();

    cout << "Sequential Time: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    cout << "Sequential Sorted Array: ";
    printArray(a);

    start = chrono::high_resolution_clock::now();
    bubbleParallel(b);
    end = chrono::high_resolution_clock::now();

    cout << "Parallel Time: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    cout << "Parallel Sorted Array: ";
    printArray(b);

    return 0;
}
