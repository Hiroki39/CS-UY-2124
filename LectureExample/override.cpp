#include <iostream>
using namespace std;

class Base {
public:
    virtual void whereAmI() const { cout << "Base\n"; }
};

class Derived : public Base {
public:
    void whereAmI() const override;
};

void foo(Base& thing) { thing.whereAmI(); }

int main() {
    Base base;
    foo(base);
    Derived der;
    foo(der);
}

void Derived::whereAmI() const { cout << "Derived\n"; }
