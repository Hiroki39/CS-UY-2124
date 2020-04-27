#include <iostream>
#include <vector>
using namespace std;

int main() {
    int* i = new int(8);
    delete i;
    delete i;
}
