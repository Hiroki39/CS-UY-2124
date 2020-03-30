/*
  struct.cpp
  Sec C, Feb 3, 2020
  --Hongyi Zheng
*/
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

// void displayBike(Motorcycle aBike)
// void displayBike(Motorcycle &aBike)
void displayBike(const Motorcycle& aBike);           // prototype
void displayBikes(const vector<Motorcycle>& bikes);  // prototype

void fillBikeVectorFromStream(ifstream& bikeStream, vector<Motorcycle>& bikes);

int main() {
  Motorcycle bike{"Harley", 1200, "cruiser"};

  vector<Motorcycle> bikes;

  ifstream bikeStream("bikes.txt");
  if (!bikeStream) {
    cerr << "Failed to open ...";
    exit(1);
  }

  // while (getline(bikeStream, line))
  fillBikeVectorFromStream(bikeStream, bikes);
  bikeStream.close();

  // for (size_t i = 0; i < bikes.size(); i++) {
  //   displayBike(bikes[i]);
  // }
  for (const Motorcycle& aBike : bikes) {
    displayBike(aBike);
  }
}

void displayBike(const Motorcycle& aBike) {
  cout << aBike.brand << ' ' << aBike.cc << ' ' << aBike.model;
}

void displayBikes(const vector<Motorcycle>& bikes) {
  for (const Motorcycle& aBike : bikes) {
    displayBike(aBike);
  }
}

void fillBikeVectorFromStream(ifstream& bikeStream, vector<Motorcycle>& bikes) {
  string brand, model;
  int cc;
  while (bikeStream >> brand >> cc >> model) {
    Motorcycle aBike{brand, cc, model};
    bikes.push_back(aBike);
  }
}
