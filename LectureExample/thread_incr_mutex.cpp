#include <unistd.h>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

volatile int glob = 0;  // Don't want optimization to effect the answer
const int LOOPS = 100000000;
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
    thread tid(spin);
    tid.detach();

    thread t1(threadFunc);
    thread t2(threadFunc);
    thread t3(threadFunc);
    thread t4(threadFunc);
    thread t5(threadFunc);
    thread t6(threadFunc);
    thread t7(threadFunc);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    cout << "glob = " << glob << endl;
}
