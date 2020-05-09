#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#define NDEBUG
#include <cassert>
using namespace std;

struct MyException : exception {
    const char* what() const noexcept { return "this is My MyException"; }
};

void bar(int n) {
    assert(n <= 200);
    if (n > 200) {
        // What to do?
        throw MyException{};
    }
}

void foo(int n) { bar(n); }

int main() {
    try {
        foo(300);
    } catch (exception& ex) {
        cerr << "Caught an exception: " << ex.what() << endl;
        // catch (double d)
    } catch (...) {
        cerr << "so long and thanks for all the fish\n";
    }
    cout << "Still running\n";
}
