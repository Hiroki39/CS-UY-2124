#include <iostream>
using namespace std;

class FrogPrince;

class Princess {
  friend ostream& operator<<(ostream& os, const Princess& princess);

public:
  Princess(const string& name);
  void marries(FrogPrince& betrothed);

private:
  string name;
  FrogPrince* spouse;
};

class FrogPrince {
  friend ostream& operator<<(ostream& os, const FrogPrince& frogprince);
  friend void Princess::marries(FrogPrince& betrothed);

public:
  FrogPrince(const string& name);
  const string& getName() const;  // the second const is part of the prototype!

private:
  string name;
  Princess* spouse;
};

int main() {
  Princess snow_white("Snow White");
  FrogPrince snowy("Snowy");
  snow_white.marries(snowy);
  cout << snow_white << endl;
}

// Princess Code
ostream& operator<<(ostream& os, const Princess& princess) {
  os << "Princess: " << princess.name;
  if (princess.spouse) {
    os << "Spouse: " << princess.spouse->getName();
  }
  return os;
}

Princess::Princess(const string& name) : name(name), spouse(nullptr) {}

void Princess::marries(FrogPrince& betrothed) {
  spouse = &betrothed;
  betrothed.spouse = this;
}

// FrogPrince Code
ostream& operator<<(ostream& os, const FrogPrince& frogprince) {
  os << "FrogPrince: " << frogprince.name;
  if (frogprince.spouse) {
    os << "Spouse: " << *frogprince.spouse;
  }
  return os;
}

FrogPrince::FrogPrince(const string& name) : name(name), spouse(nullptr) {}
const string& FrogPrince::getName() const { return name; }
