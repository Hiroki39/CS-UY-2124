#include <unistd.h>
#include <iostream>
#include <thread>
using namespace std;

#define MAX 20
int x = 0;

void someFunc() {
    cerr << "Hi from some Func.\n";
    for (int i = 0; i < MAX; ++i) {
        x++;
        cerr << ".";
    }
    cerr << "\nBye from someFunc\n";
}

int main() {
    cerr << "x = " << x << endl;
    cerr << "About to call someFunc.\n";
    thread myThread(someFunc);
    cerr << "Back from calling someFunc.\n";
    myThread.join();  // Block until myThread finishes
    cerr << "x = " << x << endl;
    cerr << "main out\n";
}
