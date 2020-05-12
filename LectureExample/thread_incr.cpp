#include <unistd.h>
#include <iostream>
#include <thread>
using namespace std;

volatile int glob = 0;  // Don't want optimization to effect the answer

const int LOOPS = 10000;

void threadFunc() {  // we need to make sure only one of our thread is in this
                     // critical region which could access the shared memory
    for (int j = 0; j < LOOPS; j++) {
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
