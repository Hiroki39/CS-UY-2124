/*
    filename.cpp
    Sec C, May 6, 2020
    Hongyi Zheng
    <|Introduction>
*/

#include <iostream>
using namespace std;

void printDigits(int n) {
    if (n < 10) {  // bottom case
        cout << n << ' ';
    } else {
        printDigits(n / 10);
        cout << (n % 10) << ' ';  // print last digit
    }
}

void printDigitsReverse(int n) {
    if (n < 10) {
        cout << n << ' ';
    } else {
        cout << (n % 10) << ' ';  // print before higher digits are printed
        printDigits(n / 10);
    }
}

// 5 : 1 0 1
// 16 : 1 0 0 0 0
void printBits(int n) {
    if (n < 2) {  // bottom case
        cout << n << ' ';
    } else {
        printBits(n / 2);
        cout << (n % 2) << ' ';  // print last bit
    }
}

// count the number of bits that are 1
int countOnes(int n) {
    if (n < 2) return n;
    return countOnes(n / 2) + (n % 2);
}

int main() {
    cout << "printDigits(314159); ";
    printDigits(314159);
    // 314159: 31415 9
    // 314159: 3 14159  harder to achieve
    cout << endl;

    /*
    cout << "printDigitsR1(314159); ";
    printnDigitsR1(314159)
    cout << endl;

    cout << "printDigitsR2(314159); ";
    printnDigitsR2(314159)
    cout << endl;

    cout << "printBits"
    */
}
