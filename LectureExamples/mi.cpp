#include <iostream>
#include <vector>
using namespace std;

// Mixin class
class Flier {
public:
    virtual void fly() = 0;
};
void Flier::fly() { cout << "I can fly!!!\n"; }

class Animal {
public:
    virtual void display() { cout << "Animal\n"; }
};

class Bat : public Animal, public Flier {
public:
    void fly() {
        cout << "Flap...flap";
        Flier::fly();
    }
};

class Insect : public Animal, public Flier {
public:
    void fly() {
        cout << "Bzzzz.";
        Flier::fly();
    }
};

class Plane : public Flier {
public:
    void fly() { cout << "vrooommmmm!"; }
};

class Person {
public:
    Person(const string& name) : name(name) {}

private:
    string name;
};

class Student : public Person {
public:
    Student(const string& name) : Person(name) {}
    virtual void display() const { cout << "Student\n"; }

    // private:
    //     string name;
};

class Instructor : public Person {
public:
    Instructor(const string& name) : Person(name) {}
    virtual void display() const { cout << "Instructor\n"; }

    // private:
    //     string name;
};

class TA : public Student, public Instructor {
public:
    // TA() : Student(), Instructor() {}
    TA(const string& name) : Student(name), Instructor(name) {}
    using Student::display;
};

int main() {
    Bat battie;
    battie.display();
    battie.fly();
    Plane sopwithCamel;
    Insect lady;

    cout << "================\n";
    vector<Flier*> vf;
    vf.push_back(&battie);
    vf.push_back(&sopwithCamel);
    vf.push_back(&lady);
    for (Flier* flier : vf) {
        flier->fly();
    }

    TA rohit("rohit");
    // rohit.display();
    rohit.Student::display();
}
