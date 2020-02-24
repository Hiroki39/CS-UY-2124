#include <iostream>
using namespace std;

class Thing {
  friend ostream &operator<<(ostream &os, const Thing &rhs);

public:
  Thing(int x) { p = new int(x); }
  // Copy Constructor
  Thing(const Thing &yetAnotherThing) { p = new int(*yetAnotherThing.p); }
  void setValue(int val) { *p = val; }
  int getValue() const { return *p; }

  // void cleanup() { delete p; }
  ~Thing() { delete p; } // destructor
private:
  int *p;
};

void doNothing(Thing anotherThing) {
  // void doNothing)const Thing& anootherThing
} // making a copy of anotherThing and destruct it after implementation

void simpleFunc() {
  Thing aThing(17);
  cout << aThing << endl;
  // delete aThing.p; // no, p is private
  // aThing.cleanup();
  doNothing(aThing); // after this line the p of aThing is a dangling pointer!

  Thing thing29(aThing);
  Thing thing30 = aThing; // both making a copy
}

int main() { simpleFunc(); }

ostream &operator<<(ostream &os, const Thing &rhs) {
  os << *rhs.p;
  return os;
}
