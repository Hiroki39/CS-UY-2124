#include "Noble.hpp"
#include "Warrior.hpp"
using namespace std;

namespace WarriorCraft {
    // Warrior Implementation Code
    // operator overload for Warrior
    ostream& operator<<(ostream& os, const Warrior& somewarrior) {
        os << somewarrior.name << ": " << somewarrior.strength;
        return os;
    }

    // initialization list
    Warrior::Warrior(const string& theName, int theStrength)
        : name(theName), strength(theStrength), lord(nullptr) {}

    // getters and setters
    const string& Warrior::getName() const { return name; }
    int Warrior::getStrength() const { return strength; }
    void Warrior::setStrength(int theStrength) { strength = theStrength; }
    void Warrior::setLord(Noble* nobleptr) { lord = nobleptr; }
    Noble* Warrior::getLord() const { return lord; }

    // let the warrior runaway
    bool Warrior::runaway() {
        if (strength == 0) {  // fail if warrior is dead
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
        return false;  // fail if the warrior is not removed from the army
    }
}  // namespace WarriorCraft
