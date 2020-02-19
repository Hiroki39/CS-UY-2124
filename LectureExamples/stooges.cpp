#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
public:
  void display() const { cout << "Name: " << name << " Age: " << age; }
  Person(const string &name, int age) : name(name), age(age) {}
  string getName() { return name; }

private:
  string name;
  int age;
};

int main() {
  ifstream ifs("stooges.txt");
  vector<Person *> stooges;

  string name;
  int age;

  while (ifs >> name >> age) {
    // Person someone(name, age); // there is only one "someone" in the memory!
    // stooges.push_back(&someone);
    Person *personPtr = new Person(
        name, age); // allocate Person on the heap (we need to free it later)
    stooges.push_back(personPtr);
  }
  for (Person *stooge : stooges) {
    cout << stooge << " " << stooge->getName() << endl;
    delete stooge; // free memories on the heap
  }
  Person *p = new Person("Fred", 20); // become garbage on heap
  p = nullptr;                        // result in memory leak!
}
