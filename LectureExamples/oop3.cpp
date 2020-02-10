/*
  oop3.cpp;
  Sec C, Feb 10, 2020
  --Hongyi Zheng
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Date {
public:
  Date(int m, int d, int y) : month(m), day(d), year(y) {}

private:
  int month, day, year;
};
// struct makes everything public by default, class makes everything private
class Person {
  // allow this function to access private variables
  friend ostream &operator<<(ostream &os, const Person &somebody);
  // in C++, methods first
public:
  /*
  class Date {
  public:
    Date(int m, int d, int y) : month(m), day(d), year(y) {}

  private:
    int month, day, year;
  };
  */
  // we could embed the definition of a type inside another
  /*
    constructor
    const makes it possible to accept literals and protect the input variables
  */
  Person(const string &theName, int m, int d, int y)
      : name(theName), dob(m, d, y) {}
  /*
    the method does not change anything of the object, mark it as const to
    fulfill the requirement in "void displayPerson(const Person &aPerson)"
  */
  void display() const { cout << "Person: " << name << endl; }

private:
  string name;
  // access aPerson.name outside the definition would result in error
  Date dob;
};

void displayPerson(const Person &aPerson) {
  // cout << "Person: " << name << endl;
  aPerson.display();
}

// operator overload
ostream &operator<<(ostream &os, const Person &somebody) {
  os << "Person: " << somebody.name;
  return os;
}
// a << b << c is equivalent to (a << b) << c
// so this function returns an ostream

int main() {
  // Person john;
  // john.name = "John";
  Person john("John", 7, 1, 1990);
  displayPerson(john);
  john.display();
  cout << john; // operator<<(cout, john);
}
