/*
  hw02.cpp
  Sec C, Feb 23,2020
  Hongyi Zheng
  Simulate battles between warriors
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Warrior {
  // class prototype to ensure defining of second friend funtion without error
  class Weapon;
  friend ostream& operator<<(ostream& os, const Warrior& somewarrior);
  friend ostream& operator<<(ostream& os, const Weapon& someweapon);

public:
  // initialization list
  Warrior(const string& theName, const string& theWeapon, int theStrength)
      : name(theName), weapon(theWeapon, theStrength) {}

  // getters and setters
  string getName() const { return name; }
  int getStrength() const { return weapon.getStrength(); }
  void setStrength(int theStrength) { weapon.setStrength(theStrength); }

  // battle is now a method, instead of funtion
  // modify strength of Warriors, output different messages in different cases
  void battle(Warrior& enemy) {
    cout << name << " battles " << enemy.name << endl;
    if (getStrength() == 0 && enemy.getStrength() == 0) {
      cout << "Oh, NO! They're both dead! Yuck!" << endl;
    } else if (getStrength() == 0 && enemy.getStrength() > 0) {
      cout << "He's dead, " << enemy.name << endl;
    } else if (getStrength() > 0 && enemy.getStrength() == 0) {
      cout << "He's dead, " << name << endl;
    } else {  // the strengths of both warriors are not 0
      if (getStrength() == enemy.getStrength()) {
        setStrength(0);
        enemy.setStrength(0);
        cout << "Mutual Annihilation: " << name << " and " << enemy.name
             << " die at each other's hands" << endl;
      } else if (getStrength() > enemy.getStrength()) {
        setStrength(getStrength() - enemy.getStrength());
        enemy.setStrength(0);
        cout << name << " defeats " << enemy.name << endl;
      } else {  // getStrength() < enemy.getStrength()
        enemy.setStrength(enemy.getStrength() - getStrength());
        setStrength(0);
        cout << enemy.name << " defeats " << name << endl;
      }
    }
  }

private:
  // nested private Weapon class
  class Weapon {
    // friend function for the Weapon class
    friend ostream& operator<<(ostream& os, const Weapon& someweapon);

  public:
    // initialization list
    Weapon(const string& theName, int theStrength)
        : weapon_name(theName), strength(theStrength) {}
    int getStrength() const { return strength; }
    void setStrength(int theStrength) { strength = theStrength; }

  private:
    // private variables of Weapon class
    string weapon_name;
    int strength;
  };
  // private variables of Warrior class
  string name;
  Weapon weapon;
};

// function prototypes
void openFile(ifstream& warriorStream);
void displayWarriorVector(const vector<Warrior>& warriorVector);
int searchWarrior(const string& name, const vector<Warrior>& warriorVector);

int main() {
  ifstream warriorStream;
  openFile(warriorStream);

  vector<Warrior> warriors;  // stores all Warrior structures
  string command;            // read command key words from stream
  // identify the command word and take different actions
  while (warriorStream >> command) {
    if (command == "Warrior") {
      string name, weapon;
      int strength;
      warriorStream >> name >> weapon >> strength;
      // construct a new Warrior and put it into the vector
      warriors.emplace_back(name, weapon, strength);
    } else if (command == "Status") {
      displayWarriorVector(warriors);
    } else {
      string name1, name2;
      warriorStream >> name1 >> name2;
      // find the index of warriors involved in the battle
      int warrior_index1 = searchWarrior(name1, warriors);
      int warrior_index2 = searchWarrior(name2, warriors);
      warriors[warrior_index1].battle(warriors[warrior_index2]);
    }
  }
  warriorStream.close();
}

void openFile(ifstream& warriorStream) {
  warriorStream.clear();
  warriorStream.open("warriors.txt");
  // check if the file is succesfully opened
  if (!warriorStream) {
    cerr << "failed to open warriors.txt";
    exit(1);
  }
}

// show numbers and information of existing Warriors
void displayWarriorVector(const vector<Warrior>& warriorVector) {
  cout << "There are: " << warriorVector.size() << " warriors" << endl;
  for (const Warrior& curr_warrior : warriorVector) {
    cout << curr_warrior;
  }
}

// search corresponding Warrior by the name provided in a specified vector
// and return its index in the vector
int searchWarrior(const string& name, const vector<Warrior>& warriorVector) {
  for (size_t index = 0; index < warriorVector.size(); index++) {
    if (warriorVector[index].getName() == name) {
      return index;
    }
  }
  return warriorVector.size();  // return size of vector if Warrior is not found
}

// operator overload for Warrior
ostream& operator<<(ostream& os, const Warrior& somewarrior) {
  os << "Warrior: " << somewarrior.name << ", " << somewarrior.weapon;
  return os;
}

// operator overload for Weapon
ostream& operator<<(ostream& os, const Warrior::Weapon& someweapon) {
  os << "weapon: " << someweapon.weapon_name << ", " << someweapon.strength
     << endl;
  return os;
}
