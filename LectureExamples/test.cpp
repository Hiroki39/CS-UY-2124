#include <iostream>
using namespace std;

int main() {
    int b = 15;
    int* c = new int(0);
    delete c;
    c = new int(1);
    cout << *c << endl;
    bool* a = new bool[b];
    for (int i = 0; i < b; i++) {
        cout << a[i];
    }
    for (int i = 0; i < b; i++) {
        cout << a[i];
    }
    delete[] a;
}
