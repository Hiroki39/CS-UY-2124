#include "FrogPrince.hpp"
#include "Princess.hpp"
using namespace std;

namespace Fantasy {
  // Princess Implementation Code
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
    betrothed.setSpouse(this);
  }

}  // namespace Fantasy
