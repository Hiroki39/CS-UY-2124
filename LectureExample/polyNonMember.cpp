#include <iostream>
using namespace std;

class Base {
public:
    virtual void display(ostream& os) const { os << "Base"; }
};

ostream& operator<<(ostream& os, const Base& rhs) {
    // os << "Base";
    rhs.display(os);
    return os;
}

class Derived : public Base {
public:
    void display(ostream& os) const override { os << "Derived"; }
};

// ostream& operator<<(ostream& os, const Derived& rhs) {
//     os << "Derived";
//     return os;
// }

void func(const Base& base) { cout << base << endl; }

int main() {
    Derived der;
    cout << der << endl;  // will output "Derived"
    func(der);            // will output "Base"
}
