#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Word {
  string token;
  vector<int> position;
};

int main() {
  string token;
  ifstream ifs("input.txt");
  while (ifs >> token) {
    // Have I seen the token

    // If not then add a word for it

    // If I have then add the position to the Word object
  }
}
