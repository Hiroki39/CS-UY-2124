#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void addOne(int val) { ++val; }

int addOneV2(int val) {
  ++val;
  return val;
}

void addOneRef(int& val) { ++val; }

// void printstring(string s)
// void printstring(string &s)
void printstring(const string& s) {
  for (size_t i = 0; i < s.size(); ++i) {
    cout << s[i] << ' ';
  }
  cout << endl;
}

int main() {
  int x = 12;

  addOne(x);
  cout << x << endl;

  x = addOneV2(x);
  cout << x << endl;

  addOneRef(x);
  cout << x << endl;

  string a = "hi";
  printstring(a);
}
