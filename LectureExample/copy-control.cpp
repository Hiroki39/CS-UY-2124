#include <iostream>
using namespace std;

class Thing {
    friend ostream& operator<<(ostream& os, const Thing& rhs);

public:
    Thing(int x) { p = new int(x); }
    // Copy Constructor
    Thing(const Thing& yetAnotherThing) { p = new int(*yetAnotherThing.p); }
    void setValue(int val) { *p = val; }
    int getValue() const { return *p; }

    // void cleanup() { delete p; }
    ~Thing() { delete p; }  // destructor

    // operator overload (rhs = right hand side)
    // return Thing to satisfy expression such as a = b = c
    Thing& operator=(const Thing& rhs) {  // Thing& : return by reference!
        // 0. Test for self-assigment
        if (this != &rhs) {
            // 1. Avoid memory leak. Free up resources. (destructor?)
            delete p;
        }
        // 2. Allocate
        // 3. Copy
        p = new int(*rhs.p);
        // return yourself
        return *this;
    }

private:
    int* p;
};

void doNothing(Thing anotherThing) {
    // void doNothing(const Thing& anotherThing)
}  // making a copy of anotherThing and destruct it after implementation

void simpleFunc() {
    Thing aThing(17);
    cout << aThing << endl;
    // delete aThing.p; // no, p is private
    // aThing.cleanup();
    doNothing(
        aThing);  // after this line the p of aThing is a dangling pointer!

    Thing thing29(aThing);
    Thing thing30 = aThing;  // both making a copy

    Thing someOtherThing(42);
    // only make a shallow copy, so we need to overload "=" operator
    // equivalent to: aThing.operator=(someOtherThing)
    aThing = someOtherThing;
    // note: assigment operator must be a method!
}

int main() { simpleFunc(); }

ostream& operator<<(ostream& os, const Thing& rhs) {
    os << *rhs.p << endl;
    return os;
}
