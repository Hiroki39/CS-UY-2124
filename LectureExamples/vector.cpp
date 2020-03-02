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
    // data is actually a pointer to int
    delete[] data;
  }
  Vector(const Vector& rhs)
      : theSize(rhs.theSize),
        theCapacity(rhs.theCapacity),
        data(new int[rhs.theCapacity]) {
    for (size_t i = 0; i < theSize; i++) {
      data[i] = rhs.data[i];
    }
  }
  Vector& operator=(const Vector& rhs) {
    // Self assignment
    if (&rhs != this) {
      // free up our resources
      delete[] data;
      // allocate new resources
      data = new int[theCapacity];
      // copy over any information
      theSize = rhs.theSize;
      theCapacity = rhs.theCapacity;
      for (size_t i = 0; i < theSize; i++) {
        data[i] = rhs.data[i];
      }
    }
    return *this;
  }
  void push_back(int val) {
    if (theSize == theCapacity) {  // no more free space
      int* oldData = data;         // remember where the old data is
      data = new int[2 * theCapacity];
      for (size_t i = 0; i < theCapacity; i++) {
        data[i] = oldData[i];
      }
      delete[] oldData;
      theCapacity *= 2;
    }
    data[theSize] = val;
    theSize++;
  }
  size_t size() const { return theSize; }
  void clear() { theSize = 0; }
  void pop_back() { theSize--; }
  // Operator overload for square brackets (v[index])
  int operator[](size_t index) const { return data[index]; }
  // v[index] = val;
  int& operator[](size_t index) { return data[index]; }  // reference return

private:
  size_t theSize;  // C++ does not allow to have field & method with same name
  size_t theCapacity;
  int* data;
};

int main() {
  Vector v;  // not templated. Our vector can only hold ints.
  v.push_back(17);
  v.push_back(42);
  v.push_back(6);
  v.push_back(28);
}
