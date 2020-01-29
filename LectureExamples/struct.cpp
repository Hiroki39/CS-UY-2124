#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Motorcycle {
  string brand;
  int cc;
  string model;
};

int main() {

  /*
  Motorcycle bike;
  bike.brand = "Harley";
  bike.model = "cruiser";
  bike.cc = 1200;
  */

  Motorcycle bike{"Harley", 1200, "cruiser"};
}
