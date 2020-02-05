#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// The structure that stores the word and its position
struct Word {
  string token;
  vector<int> position;
};

int main() {
  string token;
  ifstream ifs("input.txt");
  while (ifs >> token) {
    // Have I seen the token
    int where = findToken(token, words); // return words.size if token not found
    // If not then add a word for it

    // If I have then add the position to the Word object
  }
}
