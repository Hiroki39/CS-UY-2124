#include <iostream>
using namespace std;

class Base {};

ostream& operator<<(ostream& os, const Base& rhs) {
    os << "Base";
    return os;
}

class Derived : public Base {};

ostream& operator<<(ostream& os, const Derived& rhs) {
    os << "Derived";
    return os;
}

void func(const Base& base) { cout << base << endl; }

int main() {
    Derived der;
    cout << der << endl;  // will output "Derived"
    func(der);            // will output "Base"
}
