#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>
#include <future>
#include <string>

using namespace std;
using namespace std::chrono;

void insertionSort(vector<int> arr) {
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

void selectionSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

void shellSort(vector<int> arr) {
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

double benchmarkTask(string name, void (*sortFunc)(vector<int>), const vector<int>& baseArr) {
    auto start = high_resolution_clock::now();
    sortFunc(baseArr);
    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;
    return diff.count();
}

void runAsyncBenchmark(int n) {
    auto baseArr = generateRandomArray(n);
    cout << "\nStarting Async Benchmarking for n=" << n << "..." << endl;

    auto futureInsertion = async(launch::async, benchmarkTask, "Insertion", insertionSort, baseArr);
    auto futureSelection = async(launch::async, benchmarkTask, "Selection", selectionSort, baseArr);
    auto futureShell = async(launch::async, benchmarkTask, "Shell", shellSort, baseArr);

    cout << "Insertion Sort: " << fixed << setprecision(5) << futureInsertion.get() << "s" << endl;
    cout << "Selection Sort: " << fixed << setprecision(5) << futureSelection.get() << "s" << endl;
    cout << "Shell Sort:     " << fixed << setprecision(5) << futureShell.get() << "s" << endl;
}

int main() {
    vector<int> sizes = { 15, 150, 2000, 9000, 40000, 140000 };

    for (int n : sizes) {
        runAsyncBenchmark(n);
    }

    vector<int> searchArr = generateRandomArray(150);
    sort(searchArr.begin(), searchArr.end());

    int target;
    cout << "\nEnter element to find in 150-size array: ";
    if (cin >> target) {
        int result = binarySearch(searchArr, target);
        if (result != -1) cout << "Found at index " << result << endl;
        else cout << "Not found" << endl;
    }

    return 0;
}
