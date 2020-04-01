/*
  hw04.cpp
  Sec C, Feb 25,2020
  Hongyi Zheng
  Simulate battles between Nobles and their Warriors
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Warrior {
    // friend funtion prorotype
    friend ostream& operator<<(ostream& os, const Warrior& somewarrior);

public:
    // initialization list
    Warrior(const string& theName, int theStrength)
        : name(theName), strength(theStrength), hired(false) {}
    // getters and setters
    const string& getName() const { return name; }
    int getStrength() const { return strength; }
    void setStrength(int theStrength) { strength = theStrength; }
    bool getHiredStatus() const { return hired; }
    void changeHiredStatus() { hired = !hired; }

private:
    // private variables of Warrior class
    string name;
    int strength;
    bool hired;
};

class Noble {
    // friend funtion prorotype
    friend ostream& operator<<(ostream& os, const Noble& somenoble);

public:
    // initialization list
    Noble(const string& theName) : name(theName), army(), alive(true) {}
    // sum up strengths of all the Warriors in the army and return
    int getArmyStrength() const {
        int total_strength = 0;
        for (Warrior* const& curr_ptr : army) {
            total_strength += curr_ptr->getStrength();
        }
        return total_strength;
    }
    // multiply strength of each warrior with the ratio
    void updateArmyStrength(int winner_strength, int loser_strength) {
        for (Warrior*& curr_ptr : army) {
            int updatedStrength =
                curr_ptr->getStrength() * (winner_strength - loser_strength) /
                winner_strength;  // current strength times the ratio
            curr_ptr->setStrength(updatedStrength);
        }
    }
    bool getStatus() const { return alive; }
    // change the status of "alive" and change strength of all Warriors to 0
    void die() {
        alive = false;
        // a simple way to set stength of all Warriors in the army to 0
        updateArmyStrength(1, 1);
    }
    // atttempt to hire a warrior
    bool hire(Warrior& somewarrior) {
        if (somewarrior.getHiredStatus() || !alive) {
            return false;  // fail if Noble is dead or the warrior is already
                           // hired
        }
        somewarrior.changeHiredStatus();
        army.push_back(&somewarrior);
        return true;
    }
    // attempt to fire a warrior
    bool fire(Warrior& somewarrior) {
        if (!alive) {
            return false;  // fail if Noble is dead
        }
        bool fired = false;
        for (size_t i = 0; i < army.size(); i++) {
            if (fired == false) {
                if (army[i] == &somewarrior) {
                    cout << "You don't work for me anymore "
                         << somewarrior.getName() << "! -- " << name << "."
                         << endl;
                    somewarrior.changeHiredStatus();
                    fired = true;
                }
            } else {
                army[i - 1] = army[i];  // after the Warrior is fired, move
                                        // pointer to that Warrior to the back
                                        // of the vector and pop it
            }
            army.pop_back();
        }
        return fired;  // fail if the Warrior is not hired by the Noble
    }
    // battle is now a method of Noble, instead of Warrior
    void battle(Noble& enemy) {
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

private:
    // private variables of Noble class
    string name;
    vector<Warrior*> army;
    bool alive;
};

int main() {  // test code
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
}

// operator overload for Warrior
ostream& operator<<(ostream& os, const Warrior& somewarrior) {
    os << "  " << somewarrior.name << ": " << somewarrior.strength;
    return os;
}

// operator overload for Noble
ostream& operator<<(ostream& os, const Noble& somenoble) {
    os << somenoble.name << " has an army of " << somenoble.army.size() << endl;
    for (Warrior* curr_warriorp : somenoble.army) {
        if (curr_warriorp) {
            os << *curr_warriorp << endl;
        }
    }
    return os;
}
