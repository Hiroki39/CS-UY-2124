#include <iostream>
using namespace std;

void recursiveFunction() {
    recursiveFunction();  // infinite loop
}

int main() { towers(64, 'a', 'c', 'b'); }
