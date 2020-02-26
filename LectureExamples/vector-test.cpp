#include <iostream>
#include <vector>
using namespace std;

int main() {
  // vector v1 for size 7 with every value equals to 42
  vector<int> v1(7, 42);
  vector<int> v;
  cout << "v.size():" << v.size() << endl;

  v.push_back(17);
  v.push_back(42);
  cout << "v.size():" << v.size() << endl;

  // for (size_t i = 0; i < v.size(); ++i) {
  //  cout << v[i] << ' ';
  // }
  for (int value : v) {
    cout << value << ' ';
  }
  cout << endl;

  v.clear();
  cout << "v.size():" << v.size() << endl;
}
