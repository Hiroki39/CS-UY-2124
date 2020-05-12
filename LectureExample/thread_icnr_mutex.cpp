#include <unistd.h>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

volatile int glob = 0;  // Don't want optimization to effect the answer
const int LOOPS = 10000;
mutex myMutex;

void threadFunc() {  // we need to make sure only one of our thread is in this
                     // critical region which could access the shared memory
    for (int j = 0; j < LOOPS; j++) {
        myMutex.lock();  // if one of the thread grabs the lock, then other
                         // threads have to wait until that thread leaves
        ++glob;
        myMutex.unlock();
    }
}

int main() {
    thread t1(threadFunc);
    t1.join();

    thread t2(threadFunc);
    t2.join();
    cout << "glob = " << glob << endl;
}
