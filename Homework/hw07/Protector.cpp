#include "Noble.hpp"
#include "Protector.hpp"
using namespace std;

namespace WarriorCraft {
    // Protector Implementation Code
    // initialization list
    Protector::Protector(const string& theName, int theStrength)
        : name(theName), strength(theStrength), lord(nullptr) {}

    // getters and setters
    const string& Protector::getName() const { return name; }
    int Protector::getStrength() const { return strength; }
    void Protector::setStrength(int theStrength) { strength = theStrength; }
    void Protector::setLord(Lord* lordptr) { lord = lordptr; }
    Lord* Protector::getLord() const { return lord; }

    // let the Protector runaway
    bool Protector::runaway() {
        if (strength == 0) {  // fail if Protector is dead
            cout << name << " is already dead!" << endl;
            return false;
        }
        if (!lord) {  // fail if lord is a nullptr
            cout << name << " doesn't have a lord!";
            return false;
        }
        string lordname = lord->getName();
        if (lord->remove(*this)) {
            cout << name << " flees in terror, abandoning his lord, "
                 << lordname << endl;
            return true;
        }
        return false;  // fail if the Protector is not removed from the army
    }

    void Warrior::defend() const {
        cout << getName() << " says: Take that in the name of my lord, "
             << getLord()->getName() << endl;
    }

    // Wizard Implementation Code
    void Wizard::defend() const { cout << "POOF!" << endl; }

    // Archer Implementation Code
    void Archer::defend() const {
        cout << "TWANG! ";
        Warrior::defend();
    }

    // Archer Implementation Code
    void Swordsman::defend() const {
        cout << "CLANG! ";
        Warrior::defend();
    }
}  // namespace WarriorCraft
