#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

// ---------------- MERGE FUNCTION ----------------
void merge(vector<int>& arr, int l, int m, int r) {

    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;

    while (i < left.size() && j < right.size()) {

        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
    }

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}

// ---------------- SEQUENTIAL MERGE SORT ----------------
void mergeSequential(vector<int>& arr, int l, int r) {

    if (l < r) {

        int m = (l + r) / 2;

        mergeSequential(arr, l, m);
        mergeSequential(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// ---------------- PARALLEL MERGE SORT ----------------
void mergeParallel(vector<int>& arr, int l, int r) {

    if (l < r) {

        int m = (l + r) / 2;

        #pragma omp task
        mergeParallel(arr, l, m);

        #pragma omp task
        mergeParallel(arr, m + 1, r);

        #pragma omp taskwait

        merge(arr, l, m, r);
    }
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

    // ---------------- SEQUENTIAL ----------------
    auto start = chrono::high_resolution_clock::now();

    mergeSequential(a, 0, n - 1);

    auto end = chrono::high_resolution_clock::now();

    cout << "Sequential Merge Sort Done\n";

    cout << "Sequential Merge Sort Time: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    cout << "Sequential Sorted Array: ";
    printArray(a);

    // ---------------- PARALLEL ----------------
    start = chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        mergeParallel(b, 0, n - 1);
    }

    end = chrono::high_resolution_clock::now();

    cout << "Parallel Merge Sort Done\n";

    cout << "Parallel Merge Sort Time: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";

    cout << "Parallel Sorted Array: ";
    printArray(b);

    return 0;
}
