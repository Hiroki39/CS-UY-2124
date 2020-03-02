/*
  hw05.cpp
  Sec C, March 1, 2020
  Hongyi Zheng
  Simulate battles between Nobles and their Warriors
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Simulate the behavior of Warrior
class Warrior {
  // friend funtion prorotype
  friend ostream& operator<<(ostream& os, const Warrior& somewarrior);

public:
  // initialization list
  Warrior(const string& theName, int theStrength)
      : name(theName), strength(theStrength), hired(false) {}
  // getters and setters
  string getName() const { return name; }
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

// Simulate the behavior of Noble
class Noble {
  // friend funtion prorotype
  friend ostream& operator<<(ostream& os, const Noble& somenoble);

public:
  // initialization list
  Noble(const string& theName) : name(theName), army(), alive(true) {}
  string const& getName() const { return name; }
  int getArmySize() const { return army.size(); }  // return the size of army
  int getArmyStrength()
      const {  // sum up strengths of all the Warriors in the army and return
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
    updateArmyStrength(1, 1);  // set stength of all Warriors to 0
  }
  // atttempt to hire a warrior
  bool hire(Warrior& somewarrior) {
    if (!alive) {
      cout << "Noble " << name << " is already dead!" << endl;
      return false;  // fail if Noble is dead
    }
    if (somewarrior.getHiredStatus()) {
      cout << "Warrior " << somewarrior.getName() << " is already hired!"
           << endl;
      return false;  // fail if the warrior is already hired
    }
    somewarrior.changeHiredStatus();
    army.push_back(&somewarrior);
    return true;
  }
  // attempt to fire a warrior
  bool fire(Warrior& somewarrior) {
    if (!alive) {
      cout << "Noble " << name << " is already dead!" << endl;
      return false;  // fail if Noble is dead
    }
    bool fired = false;
    for (size_t i = 0; i < army.size(); i++) {
      if (!fired) {
        if (army[i] == &somewarrior) {
          cout << "You don't work for me anymore " << somewarrior.getName()
               << "! -- " << name << "." << endl;
          somewarrior.changeHiredStatus();
          fired = true;
        }
      } else {  // after the Warrior is fired, move pointer to that
                // Warrior to the back of the vector and pop it
        army[i - 1] = army[i];
      }
    }
    if (fired) {  // pop last element in vector only if the attempt succeed
      army.pop_back();
    } else {
      cout << somewarrior.getName() << " is not hired by " << name << "!"
           << endl;
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

private:
  // private variables of Noble class
  string name;
  vector<Warrior*> army;
  bool alive;
};

// function prototypes
void openFile(ifstream& nobleWarriorStream);
Warrior* searchWarrior(const string& name, const vector<Warrior*>& warriors);
Noble* searchNoble(const string& name, const vector<Noble*>& nobles);
void deleteptrs(vector<Noble*>& nobles, vector<Warrior*>& warriors);
void displayStatus(vector<Noble*>& nobles, vector<Warrior*>& warriors);

int main() {
  ifstream nobleWarriorStream;
  openFile(nobleWarriorStream);  // open nobleWarriors.txt

  string command;
  vector<Noble*> nobles;
  vector<Warrior*> warriors;

  // identify the command and take different actions
  while (nobleWarriorStream >> command) {
    if (command == "Noble") {
      string name;
      nobleWarriorStream >> name;
      if (searchNoble(name, nobles)) {  // check if Noble alredy exists
        cout << "Noble " << name << " already exists!" << endl;
      } else {
        nobles.emplace_back(new Noble(name));
      }
    } else if (command == "Warrior") {
      string name;
      int strength;
      nobleWarriorStream >> name >> strength;
      if (searchWarrior(name, warriors)) {  // check if Warrior already exists
        cout << "Warrior " << name << " already exists!" << endl;
      } else {
        warriors.emplace_back(new Warrior(name, strength));
      }
    } else if (command == "Status") {
      displayStatus(nobles, warriors);
    } else if (command == "Hire") {
      string noble, warrior;
      nobleWarriorStream >> noble >> warrior;
      Noble* nobleptr;
      Warrior* warriorptr;
      // check if both Noble and Warrior exist
      if ((nobleptr = searchNoble(noble, nobles)) &&
          (warriorptr = searchWarrior(warrior, warriors))) {
        nobleptr->hire(*warriorptr);
      } else {
        if (!nobleptr) {
          cout << "Noble " << noble << " not found!" << endl;
        } else {
          cout << "Warrior " << warrior << " not found!" << endl;
        }
      }
    } else if (command == "Fire") {
      string noble, warrior;
      nobleWarriorStream >> noble >> warrior;
      Noble* nobleptr;
      Warrior* warriorptr;
      // check if both Noble and Warrior exist
      if ((nobleptr = searchNoble(noble, nobles)) &&
          (warriorptr = searchWarrior(warrior, warriors))) {
        nobleptr->fire(*warriorptr);
      } else {
        if (!nobleptr) {
          cout << "Noble " << noble << " not found!" << endl;
        } else {
          cout << "Warrior" << warrior << " not found!" << endl;
        }
      }
    } else if (command == "Battle") {
      string name1, name2;
      nobleWarriorStream >> name1 >> name2;
      Noble *nobleptr1, *nobleptr2;
      // check if both Nobles exist
      if ((nobleptr1 = searchNoble(name1, nobles)) &&
          (nobleptr2 = searchNoble(name2, nobles))) {
        nobleptr1->battle(*nobleptr2);
      } else {
        if (!nobleptr1) {
          cout << "Noble " << name1 << " not found!" << endl;
        } else {
          cout << "Noble " << name2 << " not found!" << endl;
        }
      }
    } else {
      deleteptrs(nobles, warriors);  // free up space on the heap
      nobles.clear();
      warriors.clear();
    }
  }
  nobleWarriorStream.close();
  deleteptrs(nobles, warriors);  // free up space on the heap
}

// open nobleWarriors.txt
void openFile(ifstream& nobleWarriorStream) {
  nobleWarriorStream.clear();
  nobleWarriorStream.open("nobleWarriors.txt");
  // check if the file is succesfully opened
  if (!nobleWarriorStream) {
    cerr << "failed to open nobleWarriors.txt";
    exit(1);
  }
}

// search for Warrior within a vector of pointers to Warrior
Warrior* searchWarrior(const string& name, const vector<Warrior*>& warriors) {
  for (Warrior* warriorp : warriors) {
    if (warriorp->getName() == name) {
      return warriorp;
    }
  }
  return nullptr;  // return nullptr if Warrior not found
}

// search for Noble within a vector of pointers to Noble
Noble* searchNoble(const string& name, const vector<Noble*>& nobles) {
  for (Noble* noblep : nobles) {
    if (noblep->getName() == name) {
      return noblep;
    }
  }
  return nullptr;  // return nullptr if Noble not found
}

// freeup spaces by iterate through vectors of pointers pointing
// to the address on heap
void deleteptrs(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
  for (Noble* noblep : nobles) {
    delete noblep;
  }
  for (Warrior* warriorp : warriors) {
    delete warriorp;
  }
}

// output current status of all Nobles and Warriors
void displayStatus(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
  cout << "Status" << endl << "======" << endl << "Nobles:" << endl;
  int hiredWarriorCount = 0;
  if (nobles.size() > 0) {
    for (Noble* noblep : nobles) {
      cout << *noblep;
      hiredWarriorCount += noblep->getArmySize();
    }
  } else {  // if no pointer to Noble in the vector
    cout << "NONE" << endl;
  }
  cout << "Unemployed Warriors:" << endl;
  // check whether there's pointer to Noble in the vector and whether all Nobles
  // are hired
  if (warriors.size() - hiredWarriorCount > 0) {
    for (Warrior* warriorp : warriors) {
      if (!warriorp->getHiredStatus()) {
        cout << *warriorp << endl;
      }
    }
  } else {
    cout << "NONE" << endl;
  }
}

// operator overload for Warrior
ostream& operator<<(ostream& os, const Warrior& somewarrior) {
  os << somewarrior.name << ": " << somewarrior.strength;
  return os;
}

// operator overload for Noble
ostream& operator<<(ostream& os, const Noble& somenoble) {
  os << somenoble.name << " has an army of " << somenoble.army.size() << endl;
  for (Warrior* curr_warriorp : somenoble.army) {
    if (curr_warriorp) {
      os << "        " << *curr_warriorp << endl;
    }
  }
  return os;
}
