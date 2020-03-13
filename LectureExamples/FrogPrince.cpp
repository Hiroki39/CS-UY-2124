#include "FrogPrince.hpp"
#include "Princess.hpp"
using namespace std;

namespace Fantasy {
  // FrogPrince Implementation Code
  ostream& operator<<(ostream& os, const FrogPrince& frogprince) {
    os << "FrogPrince: " << frogprince.name;
    if (frogprince.spouse) {
      os << "Spouse: " << *frogprince.spouse;
    }
    return os;
  }

  FrogPrince::FrogPrince(const string& name) : name(name), spouse(nullptr) {}
  const string& FrogPrince::getName() const { return name; }
  void FrogPrince::setSpouse(Princess* betrothed) { spouse = betrothed; }

}  // namespace Fantasy
