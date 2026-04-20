#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

void printArray(const vector<int>& arr) {
    for (int i : arr) cout << i << " ";
    cout << endl;
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

int binarySearch(const vector<int>& arr, int x) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

vector<int> generateRandomArray(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    for (int i = 0; i < n; i++) arr[i] = dis(gen);
    return arr;
}

void runSyncBenchmark(int n) {
    auto baseArr = generateRandomArray(n);

    vector<string> names = { "Insertion", "Selection", "Shell" };
    for (int i = 0; i < 3; ++i) {
        auto arr = baseArr;
        auto start = high_resolution_clock::now();

        if (i == 0) insertionSort(arr);
        else if (i == 1) selectionSort(arr);
        else shellSort(arr);

        auto end = high_resolution_clock::now();
        duration<double> diff = end - start;
        cout << names[i] << " Sort for n=" << n << ": " << fixed << setprecision(5) << diff.count() << "s" << endl;
    }
}

int main() {
    vector<int> sizes = { 15, 150, 2000, 9000, 40000, 140000 };

    cout << "--- Synchronous Benchmarking ---" << endl;
    for (int n : sizes) {
        runSyncBenchmark(n);
    }

    vector<int> searchArr = generateRandomArray(150);
    shellSort(searchArr);
    int target;
    cout << "\nEnter element to find: ";
    cin >> target;
    int result = binarySearch(searchArr, target);
    (result != -1) ? cout << "Found at index " << result : cout << "Not found";

    return 0;
}
