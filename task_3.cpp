#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <Windows.h>

using namespace std;

int** createMatrix(int n) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }
    return matrix;
}

void fillMatrix(int** matrix, int n, int V) {
    int min = -10 - V;
    int max = 10 + V;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

int processSector5(int** matrix, int n, int k) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= j && (i + j) >= (n - 1)) {
                if (matrix[i][j] > k) {
                    sum += matrix[i][j];
                }
            }
        }
    }
    return sum;
}

int processSector3(int** matrix, int n) {
    int maxAbs = abs(matrix[0][0]);
    int maxVal = matrix[0][0];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(matrix[i][j]) > maxAbs) {
                maxAbs = abs(matrix[i][j]);
                maxVal = matrix[i][j];
            }
        }
    }

    cout << "Maximum absolute value in matrix: " << maxVal
        << " (|" << maxVal << "| = " << maxAbs << ")\n";

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j <= i && (i + j) <= (n - 1)) {
                count++;
                matrix[i][j] = maxVal;
            }
        }
    }
    return count;
}

void deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(time(0));

    int n, k;
    int V = 16;

    cout << "Enter matrix size n: ";
    cin >> n;
    cout << "Enter value k: ";
    cin >> k;

    int** matrix = createMatrix(n);
    fillMatrix(matrix, n, V);

    cout << "\nInitial matrix:\n";
    printMatrix(matrix, n);

    cout << "\n--------------------------------- Calculation Results ----------------------------------\n";

    int sum5 = processSector5(matrix, n, k);
    cout << "Sum of elements in Sector 5 greater than k = " << k << ": " << sum5 << "\n\n";

    int count3 = processSector3(matrix, n);
    cout << "Number of elements in Sector 3: " << count3 << "\n";

    cout << "\nMatrix after replacements in Sector 3:\n";
    printMatrix(matrix, n);

    deleteMatrix(matrix, n);
    return 0;
}
