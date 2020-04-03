#include <iostream>
using namespace std;

class Parent {
public:
    virtual void bar() { cout << "Parent::bar()" << endl; }
};
class Child : public Parent {
public:
    void bar() { cout << "Child::bar()" << endl; }
};
class Grandchild : public Child {
public:
    void bar() { cout << "Grandchild::bar()" << endl; }
};

void func(Parent& base) { cout << "func(Parent)" << endl; }
void func(Child& derived) { cout << "func(Child)" << endl; }

void otherFunc(Parent& base) {
    func(base);  // the choice of overload is done when? at compile time
    base.bar();  // polymorphism, choosing the override instead of overload,
                 // when? at runtime
}

int main() {
    Parent parent;
    func(parent);
    Child child;
    func(child);
    Grandchild gc;
    func(gc);  // both func() are available, the compilor would select the most
               // specific one! (the smaller set of input)

    otherFunc(child);
}
