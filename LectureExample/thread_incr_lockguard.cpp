#include <unistd.h>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

volatile int glob = 0;  // Don't want optimization to effect the answer
const int LOOPS = 10000000;
const int SPIN_CYCLE = 200000;  // 200000 micro seconds
mutex myMutex;

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

void threadFunc() {
    for (int j = 0; j < LOOPS; j++) {
        lock_guard<mutex> myLock(myMutex);
        ++glob;
    }
}

int main() {
    thread tid(spin);
    tid.detach();

    thread t1(threadFunc);
    thread t2(threadFunc);
    t1.join();
    t2.join();
    cout << "glob = " << glob << endl;
}
