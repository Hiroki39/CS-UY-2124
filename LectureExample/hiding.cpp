#include <iostream>
using namespace std;

class Base {
public:
    void foo(int n) const { cout << "Base::foo(n)" << endl; }
};

class Derived : public Base {
public:
    void foo() const {
        cout << "Derived::foo()" << endl;
    }  // C++ regard this as changing the meaning of foo

    // void foo(int n) const { Base::foo(n); }
    using Base::foo;
};

int main() {
    Derived der;
    der.foo(17);
    der.foo();
    // der.Base::foo(17);
}
