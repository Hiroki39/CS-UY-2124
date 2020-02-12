#include <iostream>
#include <string>
using namespace std;

class Person {
public:
  void display() const {
    cout << "Name: " << name;
    if (spouse != nullptr) {
      // cout << *spouse.name;
    }
  }
  Person(const string &name) : name(name), spouse(nullptr) {}

  // john.marries(mary)
  void marries(Person &betrothed) {
    spouse = &betrothed;
    // privacy is to the type, not instance!
    betrothed.spouse = this; // keyword 'this' can only be used inside a method
  }

private:
  string name;
  Person *spouse;
};

int main() {
  Person john("John");
  Person mary("Mary");
  john.display();
  mary.display();
  john.marries(mary);

  int x = 17;
  // where is x?
  cout << &x << endl; // address-of operator
  int *p = &x;        // p is a pointer to int
  cout << p << endl;

  // cout << x << endl;
  cout << *p << endl; // dereference operator

  *p = 42;
}
