#include <iostream>
using namespace std;

// towers of hanoi
// n is the number of disks, start is the spindle that they start on, tagrte is
// where they are bebing moved to, and spare is the "unused" spindle
void towers(int n, char start, char target, char spare) {
    if (n == 0) return;  // simpler
    // if (n == 1) {  // save many (not only one) bottom calls
    //     // print moving one disks
    //     return;
    // }
    // move all but the last one disks to the spare
    towers(n - 1, start, spare, target);
    cout << "Move disk " << n << " from spindle " << start << " to spindle "
         << target << endl;
    // move those disks at spare to the target
    towers(n - 1, spare, target, start);
}

int main() { towers(8, 'a', 'c', 'b'); }
