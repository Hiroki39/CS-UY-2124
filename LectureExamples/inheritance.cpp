#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pet {
public:
    Pet(const string& name) : name(name) {}
    // void eat() { cout << "eating" << endl; }
    virtual void eat() { cout << "eating" << endl; }
    virtual ~Pet() {}  // virtual destructor
protected:
    const string& getName() const { return name; }

private:
    string name;
};

class Cat : public Pet {
public:
    // Cat(const string& name) : name(name) {}
    Cat(const string& name) : Pet(name) {}
    // void eat() { cout << "Cat eating" << endl; }
    void eat() override {
        cout << "Cat ";
        Pet::eat();
        purr();
    }
    void purr() { cout << getName() << " the Cat purring" << endl; }
};

class Slug : public Pet {
public:
    using Pet::Pet;  // a simpler way
};

class Roach : public Pet {
public:
    using Pet::Pet;
};

// void someFunc(Pet aPet) { // Slicing problem
void someFunc(Pet& aPet) {
    cout << "someFunc: ";
    aPet.eat();  // polymorphism
    // aPet.purr();  // Compilation error(purr is not in the "public interface
    // of Pet")
}

int main() {
    Pet peeve("Peeve");
    peeve.eat();
    someFunc(peeve);

    Cat felix("Felix");
    felix.eat();
    someFunc(felix);  // principlle of substiutibility

    Roach archie("Archie");
    archie.eat();  // code reuse

    Slug sluggo("Sluggo");

    cout << "===========" << endl;
    vector<Pet> managerie;
    managerie.push_back(peeve);
    managerie.push_back(felix);
    managerie.push_back(sluggo);
    managerie.push_back(archie);
    for (size_t i = 0; i < managerie.size(); ++i) {
        managerie[i].eat();
    }

    cout << "===========" << endl;
    vector<Pet*> managerie2;
    managerie2.push_back(&peeve);
    managerie2.push_back(&felix);
    managerie2.push_back(&sluggo);
    managerie2.push_back(&archie);

    for (size_t i = 0; i < managerie2.size(); ++i) {
        managerie2[i]->eat();
    }

    peeve = felix;  // We can assign a Cat to a Pet (Slicing)
                    // The attribute of Cat will lost
    // felix = peeve;  // But we cannot assign a Pet to a Cat

    Pet* petPtr = &felix;  // Will work because felix is a Cat, and also a Pet
    // Cat* catPtr = petPtr;  // Will not work (compiler would not be sure what
    // the petPtr is pointing to)
}
