#include <iostream>
#include <map>
#include <string>
using namespace std;

struct Foo {
    Foo(const string& name, int val) : name(name), val(val) {}
    Foo(const Foo& rhs) : name(rhs.name), val(rhs.val) {
        cerr << "Foo(Foo):" << name << ' ' << val << endl;
    }
    string name;
    int val;
};

bool operator<(const Foo& lhs, const Foo& rhs) { return lhs.name < rhs.name; }

ostream& operator<<(ostream& os, const Foo& rhs) {
    return os << rhs.name << ' ' << rhs.val;
}

int main() {
    cerr << "map<Foo, int> mfi;\n";
    map<Foo, int> mfi;

    cerr << "mfi[Foo(\"Fred\", 17)] = 16;\n";
    mfi[Foo("Fred", 17)] = 6;

    cerr << "for (pair<Foo, int> p : mfi)\n";
    for (pair<Foo, int> p : mfi) cout << p.first << endl;

    cerr << "for (const pair<Foo, int>& p : mfi)\n";
    for (const pair<Foo, int>& p : mfi) cout << p.first << endl;

    cerr << "for (const pair<Foo&, int>& p : mfi)\n";
    for (const pair<const Foo&, int>& p : mfi) cout << p.first << endl;

    cerr << "for (auto p : mfi)\n";
    for (auto p : mfi) cout << p.first << endl;

    cerr << "for (const auto& p : mfi)\n";
    for (const auto& p : mfi) cout << p.first << endl;

    cerr << "Adding mary:\n";
    mfi[Foo("mary", 28)] = -42;
    for (const auto& p : mfi) cout << p.first << " " << p.second << endl;

    cerr << "for (pair<const Foo, int>& p : mfi)\n";
    for (pair<const Foo, int>& p : mfi) p.second += 1;
    for (const auto& p : mfi) cout << p.first << " " << p.second << endl;
}
