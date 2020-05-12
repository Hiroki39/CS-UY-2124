#include <unistd.h>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

volatile int glob = 0;  // Don't want optimization to effect the answer
const int LOOPS = 10000;
mutex myMutex;

void threadFunc() {
    for (int j = 0; j < LOOPS; j++) {
        lock_guard<mutex> myLock(myMutex);
        ++glob;
    }
}

int main() {
    thread t1(threadFunc);
    t1.join();

    thread t2(threadFunc);
    t2.join();
    cout << "glob = " << glob << endl;
}
