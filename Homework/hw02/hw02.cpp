/*
  hw02.cpp
  Sec C, Feb 11,2020
  Hongyi Zheng
  Simulate battles between warriors
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Warrior {
    // constructor
    Warrior(const string& theName, int theStrength)
        : name(theName), strength(theStrength) {}

    string name;
    int strength;
};

void openFile(ifstream& warriorStream);
Warrior structWarrior(const string& name, int strength);
void displayWarriorVector(const vector<Warrior>& warriorVector);
Warrior searchWarrior(const string& name, const vector<Warrior>& warriorVector);
void battle(Warrior& warrior1, Warrior& warrior2);
void replaceWarrior(const Warrior& warrior1, const Warrior& warrior2,
                    vector<Warrior>& warriorVector);

int main() {
    ifstream warriorStream;
    openFile(warriorStream);

    vector<Warrior> warriors;  // stores all Warrior structures
    string command;            // read command key words from stream

    // identify the command word and take different actions
    while (warriorStream >> command) {
        if (command == "Warrior") {
            string name;
            int strength;
            warriorStream >> name >> strength;
            // struct a new Warrior and put it into the vector
            warriors.push_back(structWarrior(name, strength));
        } else if (command == "Status") {
            displayWarriorVector(warriors);
        } else {
            string name1, name2;
            warriorStream >> name1 >> name2;
            Warrior warrior1 = searchWarrior(name1, warriors);
            Warrior warrior2 = searchWarrior(name2, warriors);
            battle(warrior1, warrior2);
            replaceWarrior(warrior1, warrior2, warriors);
        }
    }
    warriorStream.close();
}

// try to open warriors.txt, output an error if failed to open it
void openFile(ifstream& warriorStream) {
    warriorStream.clear();
    warriorStream.open("warriors.txt");
    // check if the file is succesfully opened
    if (!warriorStream) {
        cerr << "failed to open warriors.txt";
        exit(1);
    }
}

// create a new Warrior structure and return it
Warrior structWarrior(const string& name, int strength) {
    Warrior new_warrior(name, strength);
    return new_warrior;
}

// show numbers and information of existing Warriors
void displayWarriorVector(const vector<Warrior>& warriorVector) {
    cout << "There are: " << warriorVector.size() << " warriors" << endl;
    for (const Warrior& curr_warrior : warriorVector) {
        cout << "Warrior: " << curr_warrior.name << " " << curr_warrior.strength
             << endl;
    }
}

// search corresponding Warrior by the name provided in a specified vector
Warrior searchWarrior(const string& name,
                      const vector<Warrior>& warriorVector) {
    for (const Warrior& curr_warrior : warriorVector) {
        if (curr_warrior.name == name) {
            return curr_warrior;
        }
    }
}

// create a battle, modify strength of Warriors, and output different messages
// in different cases
void battle(Warrior& warrior1, Warrior& warrior2) {
    cout << warrior1.name << " battles " << warrior2.name << endl;
    if (warrior1.strength == 0 && warrior2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    } else if (warrior1.strength == 0 && warrior2.strength > 0) {
        cout << "He's dead, " << warrior2.name << endl;
    } else if (warrior1.strength > 0 && warrior2.strength == 0) {
        cout << "He's dead, " << warrior1.name << endl;
    } else {  // the strengths of both warriors are not 0
        if (warrior1.strength == warrior2.strength) {
            warrior1.strength = warrior2.strength = 0;
            cout << "Mutual Annihilation: " << warrior1.name << " and "
                 << warrior2.name << " die at each other's hands" << endl;
        } else if (warrior1.strength > warrior2.strength) {
            warrior1.strength -= warrior2.strength;
            warrior2.strength = 0;
            cout << warrior1.name << " defeats " << warrior2.name << endl;
        } else {  // warrior1.strength < warrior2.strength
            warrior2.strength -= warrior1.strength;
            warrior1.strength = 0;
            cout << warrior2.name << " defeats " << warrior1.name << endl;
        }
    }
}

// an approach to update the information of Warriors in the vector without using
// pointers
void replaceWarrior(const Warrior& warrior1, const Warrior& warrior2,
                    vector<Warrior>& warriorVector) {
    // iterate through the vector to find the Warrior that need to be replaced
    for (Warrior& curr_warrior : warriorVector) {
        if (curr_warrior.name == warrior1.name) {
            curr_warrior = warrior1;
        } else if (curr_warrior.name == warrior2.name) {
            curr_warrior = warrior2;
        }
    }
}
