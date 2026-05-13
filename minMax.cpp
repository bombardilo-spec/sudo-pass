#include <iostream>
#include <climits>
#include <omp.h>

using namespace std;

int main() {

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;
    int sum = 0;

    // ---------------- MIN ----------------
    #pragma omp parallel for reduction(min: min_val)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val)
            min_val = arr[i];
    }

    // ---------------- MAX ----------------
    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val)
            max_val = arr[i];
    }

    // ---------------- SUM ----------------
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    double avg = (double)sum / n;

    cout << "\nMinimum: " << min_val;
    cout << "\nMaximum: " << max_val;
    cout << "\nSum: " << sum;
    cout << "\nAverage: " << avg << endl;

    return 0;
}