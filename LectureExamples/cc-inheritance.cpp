#include <iostream>
using namespace std;

class Base {
public:
    Base() { cerr << "Base()\n"; }
    Base(const Base& rhs) { cerr << "Base(const Base&)\n"; }
    virtual ~Base() { cerr << "~Base()\n"; }
    Base& operator=(const Base& rhs) {
        cerr << "Base::operator=(const Base&)\n";
        return *this;
    }
};

class Member {
public:
    Member() { cerr << "Member()\n"; }
    Member(const Member& rhs) { cerr << "Member(const Member&)\n"; }
    virtual ~Member() { cerr << "~Member()\n"; }
    Member& operator=(const Member& rhs) {
        cerr << "Member::operator=(const Member&)\n";
        return *this;
    }
};

class Derived : public Base {
public:
    // Derived() { cerr << "Derived()\n"; }
    // Derived() : Base() { cerr << "Derived()\n"; }
    Derived() : Base(), mem() { cerr << "Derived()\n"; }  // all equivalent

    ~Derived() {
        cerr << "~Derived()\n";
        // destructors for non-primitives get called automatically
        // destructors for base class get called automatically
    }

    Derived(const Derived& rhs) : Base(rhs) {
        cerr << "Derived(const Derived& rhs)\n";
    }

    Derived& operator=(const Derived& rhs) {
        Base::operator=(rhs);
        cerr << "Derived::operator=(const Derived&)\n";
        return *this;
    }

private:
    Member mem;
};

int main() {
    cerr << "Derived der;\n"
         << "--------\n";
    Derived der;
    cout << "===\n";

    // cerr << "Derived der2(der);\n"
    //      << "--------\n";
    // Derived der2(der);
    // cout << "===\n";
    //
    // cerr << "Derived der3 = der;\n"
    //      << "--------\n";
    // Derived der3 = der;
    // cout << "===\n";
    //
    // cerr << "der = der2;\n"
    //      << "--------\n";
    // der = der2;
    // cout << "===\n";
    //
    // cerr << "Derived* p = new Derived();\n"
    //      << "delete p;\n"
    //      << "--------\n;";
    // Derived* p = new Derived();
    // delete p;
    // cout << "===\n";
    //
    // cerr << "Base* bp = new Derived();\n"
    //      << "delete p;\n"
    //      << "--------\n";
    // Base* bp = new Derived();
    // delete bp;
    // cout << "===\n";
}
