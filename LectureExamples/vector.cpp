/*
  Vector Class
  Demonstrates:
    Good example of copy control
    Dynamic arrays and pointer arithmetic
    Square bracket operator
    Implementation of an important data structure
*/
#include <iostream>
using namespace std;

class Vector {
public:
  Vector() : theSize(0), theCapacity(8), data(new int[theCapacity]) {}
  // Vector(size_t size, int value = 0) {}
  ~Vector() {
    // delete data; this will only delete one integer!
    delete[] data;
  }
  // Vector(const Vector& rhs)
  // Vecyor& operator=(const Vector& rhs)
  size_t size() const { return theSize; }
  void clear() { theSize = 0; }
  void pop_back() { theSize--; }
  // Square brackets
private:
  size_t theSize;
  size_t theCapacity;
  int* data;
};

int main() {
  Vector v;  // not templated. Our vector can only hold ints.
}
