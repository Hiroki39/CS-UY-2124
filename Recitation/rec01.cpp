#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// display the values in a vector
void display_vector(const vector<int> &v) {
  for (int value : v) {
    cout << value << " ";
  }
  cout << endl;
}

// double the values in a vectors in two methods
void double_val_in_vector1(vector<int> &v) {
  for (size_t i = 0; i < v.size(); i++) {
    v[i] *= 2;
  }
}

void double_val_in_vector2(vector<int> &v) {
  for (int &value : v) {
    value *= 2;
  }
}

int main() {
  // output a message in two methods
  std::cout << "hello, world!" << std::endl;
  cout << "hello, world!" << endl;

  int x; // undefined variable
  cout << "x(undefined): " << x << endl;

  // define y, z, pie and display their size
  int y = 17;
  int z = 2000000017;
  double pie = 3.14159;
  cout << "size of y: " << sizeof(y) << endl;
  cout << "size of z: " << sizeof(z) << endl;
  cout << "size of pie: " << sizeof(pie) << endl;

  // x = "felix";
  // assigning to 'int' from incompatible type 'const char [6]'
  // compilation error

  // check if y is between 10 and 20
  if (y <= 20 && y >= 10) {
    cout << "y is between 10 and 20" << endl;
  } else {
    cout << "y is not between 10 and 20" << endl;
  }

  // print values from 10 to 20 using 3 different kinds of loops
  cout << "output of for loop: ";
  for (int i = 10; i <= 20; i++) {
    cout << i << " ";
  }
  cout << endl;

  cout << "output of while loop: ";
  int i = 10;
  while (i <= 20) {
    cout << i << " ";
    i++;
  }
  cout << endl;

  cout << "output of do-while loop: ";
  i = 10;
  do {
    cout << i << " ";
    i++;
  } while (i <= 20);
  cout << endl;

  // ask for the filename until the file is succesfully opened
  ifstream ifs;
  do {
    string filename;
    cout << "input filename: ";
    cin >> filename;
    ifs.open(filename);
  } while (!ifs);

  // read the file word by word
  string word;
  cout << "printing words in jabberwocky.txt..." << endl;
  while (ifs >> word) {
    cout << word << endl;
  }
  ifs.close();

  // define a vector to hold ints and fill it with even integer from 10 to 100
  vector<int> even_ints;
  for (int i = 10; i <= 100; i += 2) {
    even_ints.push_back(i);
  }

  // print values in the vector in two methods
  cout << "output of for loop with indices: ";
  for (size_t i = 0; i < even_ints.size(); i++) {
    cout << even_ints[i] << " ";
  }
  cout << endl;

  cout << "output of ranged-for loop: ";
  for (int value : even_ints) {
    cout << value << " ";
  }
  cout << endl;

  // print values in reverse
  cout << "output of for loop with indices in reverse: ";
  for (size_t i = 0; i < even_ints.size(); i++) {
    cout << even_ints[even_ints.size() - i - 1] << " ";
  }
  cout << endl;

  // define a vector with primes less than 20 and print those primes
  vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19};
  for (int value : primes) {
    cout << value << " ";
  }
  cout << endl;

  // test functions
  cout << "printing vector with function: ";
  display_vector(primes);

  cout << "doubling values in vector with traditional loop: ";
  double_val_in_vector1(primes);
  display_vector(primes);

  cout << "doubling values in vector with ranged-for loop: ";
  double_val_in_vector2(primes);
  display_vector(primes);
}
