#include <iostream>
#include <vector>
#include "Noble.hpp"
#include "Warrior.hpp"
using namespace std;

namespace WarriorCraft {
    // Noble Implementation Code
    // operator overload for Noble
    ostream& operator<<(ostream& os, const Noble& somenoble) {
        os << somenoble.name << " has an army of " << somenoble.army.size()
           << endl;
        for (Warrior* curr_warriorp : somenoble.army) {
            os << "        " << *curr_warriorp << endl;
        }
        return os;
    }

    // initialization list
    Noble::Noble(const string& theName) : name(theName), army(), alive(true) {}

    // getters and setters
    const string& Noble::getName() const { return name; }
    int Noble::getArmyStrength() const {
        // sum up strengths of all the Warriors in the army and return
        int total_strength = 0;
        for (Warrior* const& curr_ptr : army) {
            total_strength += curr_ptr->getStrength();
        }
        return total_strength;
    }

    // multiply strength of each warrior with the ratio
    void Noble::updateArmyStrength(int winner_strength, int loser_strength) {
        for (Warrior*& curr_ptr : army) {
            int updatedStrength =
                curr_ptr->getStrength() * (winner_strength - loser_strength) /
                winner_strength;  // current strength times the ratio
            curr_ptr->setStrength(updatedStrength);
        }
    }

    // change the status of "alive" and change strength of all Warriors to 0
    void Noble::die() {
        alive = false;
        updateArmyStrength(1, 1);  // set stength of all Warriors to 0
    }

    // hire a warrior
    bool Noble::hire(Warrior& somewarrior) {
        if (!alive) {
            cout << "Noble " << name << " is already dead!" << endl;
            return false;  // fail if Noble is dead
        }
        if (somewarrior.getLord()) {  // if somewarrior.lord is not a nullptr
            cout << "Warrior " << somewarrior.getName() << " is already hired!"
                 << endl;
            return false;  // fail if Warrior is already hired
        }
        somewarrior.setLord(this);
        army.push_back(&somewarrior);
        return true;
    }

    // fire a warrior
    bool Noble::fire(Warrior& somewarrior) {
        if (!alive) {
            cout << "Noble " << name << " is already dead!" << endl;
            return false;  // fail if Noble is dead
        }
        if (remove(somewarrior)) {
            cout << "You don't work for me anymore " << somewarrior.getName()
                 << "! -- " << name << "." << endl;
            return true;
        }
        return false;  // fail if the warrior is not removed
    }

    // attempt to remove a warrior (fire or runaway)
    bool Noble::remove(Warrior& somewarrior) {
        for (size_t i = 0; i < army.size(); i++) {
            if (army[i] == &somewarrior) {
                somewarrior.setLord(nullptr);
                army[i] = army.back();  // copy last element to removed
                                        // warrior's place
                army.pop_back();
                return true;
            }
        }
        cout << somewarrior.getName() << " is not hired by " << name << "!"
             << endl;
        return false;  // fail if the Warrior is not hired by the Noble
    }

    // battle between Nobles
    void Noble::battle(Noble& enemy) {
        cout << name << " battles " << enemy.name << endl;
        // check whether there's dead nobel(s).
        if (!alive && !enemy.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!alive && enemy.alive) {
            cout << "He's dead, " << enemy.name << endl;
        } else if (alive && !enemy.alive) {
            cout << "He's dead, " << name << endl;
        } else {  // both nobles are alive
            int self_strength = getArmyStrength();
            int enemy_strength = enemy.getArmyStrength();
            // determine which noble to die
            if (self_strength == enemy_strength) {
                die();
                enemy.die();
                cout << "Mutual Annihilation: " << name << " and " << enemy.name
                     << " die at each other's hands" << endl;
            } else if (self_strength > enemy_strength) {
                updateArmyStrength(self_strength, enemy_strength);
                enemy.die();
                cout << name << " defeats " << enemy.name << endl;
            } else {  // self_strength < enemy_strength
                enemy.updateArmyStrength(enemy_strength, self_strength);
                die();
                cout << enemy.name << " defeats " << name << endl;
            }
        }
    }
}  // namespace WarriorCraft
