#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pet {
public:
  // void eat() { cout << "eating" << endl; }
  virtual void eat() { cout << "eating" << endl; }
};

class Cat : public Pet {
public:
  // void eat() { cout << "Cat eating" << endl; }
  void eat() {
    cout << "Cat ";
    Pet::eat();
    purr();
  }
  void purr() { cout << "Cat purring" << endl; }
};

class Stug : public Pet {};

class Roach : public Pet {};

void someFunc(Pet& aPet) {
  cout << "someFunc: ";
  aPet.eat();  // polymorphism
  // aPet.purr();  // Compilation error
}

int main() {
  Pet peeve;
  peeve.eat();
  someFunc(peeve);

  Cat felix;
  felix.eat();      // code reuse
  someFunc(felix);  // principlle of substiutibility
}
