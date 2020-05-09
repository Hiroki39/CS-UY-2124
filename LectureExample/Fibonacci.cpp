#include <iostream>
using namespace std;

int fib(int n) {
    if (n < 2) return n;             // fib(0) == 0, fib(1) == 1
    return fib(n - 2) + fib(n - 1);  // complexity too high !
}

int main() {
    for (int i = 0; i < 10; ++i) {
        cout << "fib(" << i << ") =" << fib(i) << endl;
    }
}
