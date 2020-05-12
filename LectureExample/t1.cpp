#include <iostream>
#include <thread>  // std::thread
using namespace std;

void someFunc() { cerr << "Hi from someFunc.\n"; }

int main() {
    cerr << "About to call someFunc.\n";
    thread myThread(someFunc);
    myThread.detach();  // don't worry about our thread when exit main
    cerr << "Back from calling someFunc.\n";
    cerr << "main out\n";
}
