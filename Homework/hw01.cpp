// decrypt texts encrypted by classic Caesar cypher algorithm
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

char decrypt_char(char chr, int step) {
  // check if the character is a lowercases letter and process it
  if (chr >= 'a' && chr <= 'z') {
    chr -= step;
    if (chr < 'a') {
      chr += 26; // wrap around
    }
  }
  return chr;
}

void decrypt_string(string &input_str, int step) {
  for (char &chr : input_str) {
    chr = decrypt_char(chr, step);
  }
}

int main() {
  // open the encrypted.txt file
  ifstream encrypted("encrypted.txt");
  if (!encrypted) {
    cerr << "failed to open enceypted.txt" << endl;
    exit(1);
  }

  string line;
  vector<string> lines;
  int step;
  encrypted >> step; // read the  first integer into the variable 'step'

  while (getline(encrypted, line)) {
    lines.push_back(line); // read following lines into the vector
  }
  encrypted.close();

  for (size_t i = 0; i < lines.size(); i++) {
    // process strings in the vecrtor in reverse
    string curr_line = lines[lines.size() - i - 1];
    decrypt_string(curr_line, step);
    cout << curr_line << endl;
  }
}
