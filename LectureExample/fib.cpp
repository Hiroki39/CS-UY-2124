#include <iostream>
using namespace std;

long long fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    for (size_t i = 0; i < 100; i++) {
        cout.imbue(locale(""));
        cout << "fib(" << i << "): " << fib(i) << endl;
    }
}
