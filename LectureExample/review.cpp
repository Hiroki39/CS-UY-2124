#include <iostream>
using namespace std;

class Thing {
public:
    virtual void aVirtualMethod() {}
    virtual void aPureVirtualMethod() = 0;
};

class Derived : public Thing {
public:
    void aPureVirtualMethod() {}
};

class Dervied2 : public Thing {};

void doNothing(Derived anotherDer) {}
void doNothing(int n) {}

int main() {
    // Thing thingOne;
    // thingOne.aVirtualMethod();
    Derived der;
    der.aPureVirtualMethod();

    // Using a copy constructor
    Derived der2(
        der);  // if you need a destructor, then you need a copy constructor!
    doNothing(der);

    Derived der3;
    // assignment
    der3 = der;

    // when was the decision of using which version made? Compile time
    doNothing(17);  // overload

    int** p = new int*[10];  // p is a pointer to int pointers

    // .. filling the array with pointers to ints on the heap
    for (int i = 0; i < 10; i++) {
        p[i] = new int(i);
    }
    // if we delete[] p before the following loop, will result in memory leak!

    for (int i = 0; i < 10; ++i) {
        // assuimg all entries have valid addresses on the heap in them
        delete p[i];     // delete *(p + i)
        p[i] = nullptr;  // Good idea
    }

    // free up the array
    delete[] p;
    p = nullptr;  // Good idea
}
