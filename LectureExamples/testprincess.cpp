#include <iostream>
#include <string>

#include "FrogPrince.hpp"
#include "Princess.hpp"
using namespace std;
using namespace Fantasy;

int main() {
  Princess snowy("Snow White");
  cout << snowy << endl;
  FrogPrince froggy("Froggy");
  snowy.marries(froggy);
  cout << snowy << endl;
}
