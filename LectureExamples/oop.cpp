/*
  oop.cpp;
  Sec C, Feb 5, 2020
  --Hongyi Zheng
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// struct makes everything public by default, class makes everything private
// strucrt Person
class Person {
  // in C++, methods first
public:
  // Person() {} default constructor
  Person() : name("fred"), age(17) {} // initialization list
  /*
    constructor
    const makes it possible to accept literals and protect the input variables
  */
  Person(const string &theName) : name(theName) {
    // name = theName; not ideal
    age = 17;
  }
  /*
    the method does not change anything of the object, mark it as const to
    fulfill the requirement in "void displayPerson(const Person &aPerson)"
  */
  void display() const { cout << "Person: " << name << endl; }

private:
  string name;
  int age;
  // access aPerson.name outside the definition would result in error
};

void displayPerson(const Person &aPerson) {
  // cout << "Person: " << name << endl;
  aPerson.display();
}

int main() {
  // Person john;
  // john.name = "John";
  Person john("John");
  displayPerson(john);
  john.display();

  // if we don't have the default the constructor this line won't compile
  Person mary;
}
