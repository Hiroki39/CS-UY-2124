#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  const int ROWS = 10;
  const int COLS = 10;
  vector<vector<int>> mat;

  for (int r = 0; r < ROWS; ++r) {
    mat.push_back(vector<int>(COLS));
    for (int c = 0; c < COLS; ++c) {
      mat[r][c] = r * ROWS + c;
    }
  }

  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; ++c) {
      cout << mat[r][c] << ' ';
    }
    cout << endl;
  }
}
