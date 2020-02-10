/*
  CS-2124 - Sec C
  rec02.cpp
  Hongyi Zheng
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Hydrocarbon {
  Hydrocarbon(int numofC, int numofH) : C(numofC), H(numofH) {} // constructor

  // add name of a substance to the corresponding chemical formula
  void addname(const string &newName) { names.push_back(newName); }

  // display the information of chemical formula
  void display() const {
    cout << "C" << C << "H" << H;
    for (const string &name : names) {
      cout << " " << name;
    }
    cout << endl;
  }

  // make getting number of H and C possible
  int getNumofH() const { return H; }
  int getNumofC() const { return C; }

private:
  int C;
  int H;
  vector<string> names;
};

void fillHCVector(ifstream &HCStream, vector<Hydrocarbon> &hydrocarbons);
bool addNametoHydrocarbon(const string &name, int H, int C,
                          vector<Hydrocarbon> &hydrocarbons);
void sortHCVector(vector<Hydrocarbon> &hydrocarbons);
void swapHydrocarbons(vector<Hydrocarbon> &hydrocarbons, int pos1, int pos2);
void displayHCVector(const vector<Hydrocarbon> &hydrocarbons);
void openFile(ifstream &HCStream);

int main() {
  ifstream HCStream;
  openFile(HCStream);

  vector<Hydrocarbon> hydrocarbons;
  fillHCVector(HCStream, hydrocarbons);
  HCStream.close();

  sortHCVector(hydrocarbons);
  displayHCVector(hydrocarbons);
}

// read all names of formula into a vector containing Hydrocarbon data structure
void fillHCVector(ifstream &HCStream, vector<Hydrocarbon> &hydrocarbons) {
  int H, C;
  string name;
  char skip;

  while (HCStream >> name >> skip >> C >> skip >> H) {
    // try to add name of substance to an existing Hydrocarbon data structure.
    // If no existing Hydrocarbon has the required number of H and C,
    // construct a new one.
    if (!addNametoHydrocarbon(name, H, C, hydrocarbons)) {
      Hydrocarbon new_hydrocarbon(C, H);
      new_hydrocarbon.addname(name);
      hydrocarbons.push_back(new_hydrocarbon);
    }
  }
}

bool addNametoHydrocarbon(const string &name, int H, int C,
                          vector<Hydrocarbon> &hydrocarbons) {
  for (Hydrocarbon &curr_struct : hydrocarbons) {
    if (curr_struct.getNumofC() == C && curr_struct.getNumofH() == H) {
      curr_struct.addname(name);
      return true;
    }
  }
  return false;
}

// insertion sort
void sortHCVector(vector<Hydrocarbon> &hydrocarbons) {
  for (size_t i = 1; i < hydrocarbons.size(); i++) {
    for (size_t j = i; j > 0; j--) {
      if (hydrocarbons[j].getNumofC() < hydrocarbons[j - 1].getNumofC()) {
        swapHydrocarbons(hydrocarbons, j, j - 1);
      } else if (hydrocarbons[j].getNumofC() ==
                 hydrocarbons[j - 1].getNumofC()) {
        if (hydrocarbons[j].getNumofH() < hydrocarbons[j - 1].getNumofH()) {
          swapHydrocarbons(hydrocarbons, j, j - 1);
        } else {
          break;
        }
      } else {
        break;
      }
    }
  }
}

// swap the positions of Hydrocarbon structure in a vector
void swapHydrocarbons(vector<Hydrocarbon> &hydrocarbons, int pos1, int pos2) {
  Hydrocarbon tmp = hydrocarbons[pos1];
  hydrocarbons[pos1] = hydrocarbons[pos2];
  hydrocarbons[pos2] = tmp;
}

void displayHCVector(const vector<Hydrocarbon> &hydrocarbons) {
  for (const Hydrocarbon &curr_struct : hydrocarbons) {
    curr_struct.display();
  }
}

void openFile(ifstream &HCStream) {
  do {
    HCStream.clear(); // prevent defective stream
    string filename;
    cout << "input filename: ";
    cin >> filename;
    HCStream.open(filename);
  } while (!HCStream);
}
