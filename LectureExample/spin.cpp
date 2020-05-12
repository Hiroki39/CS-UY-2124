#include <unistd.h>  // usleep
#include <iostream>
using namespace std;

const int SPIN_CYCLE = 200000;  // 200000 micro seconds

void spin() {
    int index = 0;
    char dial[] = "-\\|/";
    for (;;) {
        cerr << dial[index] << "\r";
        usleep(SPIN_CYCLE);  // 0.2 sec
        index = (index + 1) % 4;
    }
}

int main() {
    // start the spinner
    spin();
}
