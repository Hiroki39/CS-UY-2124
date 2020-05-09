#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

void someFunc() {
    vector<int> v;
    v.push_back(28);
    // v[17] = 42;
    // This is runtime, not compile time error! (if no push_back)
    // However, this will not result in a crash after a push_back
    // cout << v[17] << endl
    v.at(17) = 42;
    cout << v.at(17) << endl;  // report an exception
}

int main() {
    // vector<int> v;
    // v.push_back(28);
    // // v[17] = 42;
    // // This is runtime, not compile time error! (if no push_back)
    // // However, this will not result in a crash after a push_back
    // // cout << v[17] << endl
    // v.at(17) = 42;
    // cout << v.at(17) << endl;  // report an exception

    try {
        someFunc();
    } catch (exception& ex) {
        cout << "Caught an exception: " << ex.what() << endl;
    }
}
