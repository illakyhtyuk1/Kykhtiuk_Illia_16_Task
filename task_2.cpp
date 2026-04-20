#include <iostream>
#include <cmath>
#include <Windows.h>

using namespace std;

double factorial(int num) {
    double result = 1;
    for (int i = 1; i <= num; i++) {
        result *= i;
    }
    return result;
}

double calcSqrtIJ(int i, int j) {
    return sqrt(i * i + j * j);
}

double calcFirstFraction(int i) {
    double denominator = sqrt(i * i + 1.3 * 1.3);
    return factorial(i) / denominator;
}

double calcSecondFraction(int i, int j) {
    double denominator = sqrt(pow(i * j, 2) + i * i);
    return cos(i) / denominator;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int i = 6;
    int j = 5;

    double sqrtPart = calcSqrtIJ(i, j);

    double fraction1 = calcFirstFraction(i);

    double fraction2 = calcSecondFraction(i, j);

    double sum = fraction1 + fraction2;

    double y = sqrtPart * sum;

    cout << "----- calculation results -----" << endl;
    cout << "square root sqrt(i^2 + j^2): " << sqrtPart << endl;
    cout << "first fraction: " << fraction1 << endl;
    cout << "second fraction: " << fraction2 << endl;
    cout << "sum in parentheses: " << sum << endl;
    cout << "final value y = " << y << endl;
    cout << "-------------------------------" << endl;

    return 0;
}
