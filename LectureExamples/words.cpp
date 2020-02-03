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
  while (ifs >> token) {
    // Have I seen the token

    // If not then add a word for it

    // If I have then add the position to the Word object
  }
}
