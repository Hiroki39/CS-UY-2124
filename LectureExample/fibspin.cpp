#include <unistd.h>
#include <iostream>
#include <thread>
using namespace std;

const int SPIN_CYCLE = 200000;  // 200000 micro secs

// Recursively compute the nth fibonnaci number
long long fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

// Dislplay a "Spinner"
void spin() {
    int index = 0;
    char dial[] = "-\\|/";
    for (;;) {
        cerr << dial[index] << "\r";
        usleep(SPIN_CYCLE);
        index = (index + 1) % 4;
    }
}

int main(int argc, char** argv) {  // accepting input
    // Initialize
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << "fibIndex\n";
    }
    cout.imbue(locale(""));
    long int fibIndex =
        strtol(argv[1], NULL, 0);  // convert string input into long

    // Start spinner
    thread tid(spin);
    tid.detach();  // it will not affect the main() exit normally

    // Compute and display the fibonacci number
    cout << fib(fibIndex) << endl;
}
