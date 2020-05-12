#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Base {
public:
    virtual void method() {}
    void foo() {}       // overload
    void foo(int n) {}  // overload
    virtual void bar() { cout << "Base::bar()\n"; }

private:
};

class Derived : public Base {
public:
    void method() {}
    void another() { Base::bar(); }
    void bar() { cout << "Derived::bar()\n"; }

private:
};

int main() {
    Derived der;
    der.method();
    Base* bp = &der;
    bp->method();  // runtime choice
    bp->foo();     // compile time choice

    string bar = "bar";

    der.another();

    char* cstring = "cat";  // ['c', 'a', 't', '\0']
}
