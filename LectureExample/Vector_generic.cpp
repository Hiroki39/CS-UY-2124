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

template <typename George>  // George is only a dummy name
class Vector {
public:
    class Iterator {
        // non-member
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.valPtr != rhs.valPtr;
        }

    public:
        Iterator(George* p) : valPtr(p) {}
        Iterator& operator++() {  // ++iter
            valPtr++;
            return *this;
        }
        // dereference operator
        George& operator*() { return *valPtr; }

    private:
        George* valPtr;
    };

    class Const_Iterator {
        // non-member
        friend bool operator!=(const Const_Iterator& lhs,
                               const Const_Iterator& rhs) {
            return lhs.valPtr != rhs.valPtr;
        }

    public:
        Const_Iterator(George* p) : valPtr(p) {}
        Const_Iterator& operator++() {  // ++iter
            valPtr++;
            return *this;
        }
        // dereference operator
        const George& operator*() { return *valPtr; }

    private:
        George* valPtr;
    };
    Vector() : theSize(0), theCapacity(8), data(new George[theCapacity]) {}
    // Vector(size_t size, int value = 0) {}
    ~Vector() {
        // delete data; this will only delete one integer!
        // data is actually a pointer to Geroge
        delete[] data;
    }

    explicit Vector(size_t size, George value = George())
        : theSize(size), theCapacity(size), data(new George[theCapacity]) {
        for (size_t i = 0; i < theSize; i++) {
            data[i] = value;
        }
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
            data = new George[rhs.theCapacity];
            // copy over any information
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for (size_t i = 0; i < theSize; i++) {
                data[i] = rhs.data[i];
            }
        }
        return *this;
    }

    void push_back(George val) {
        if (theSize == theCapacity) {  // no more free space
            if (theCapacity == 0) {
                delete[] data;
                data = new George[1];
                theCapacity = 1;
            } else {
                int* oldData = data;  // remember where the old data is
                data = new George[2 * theCapacity];
                for (size_t i = 0; i < theCapacity; i++) {
                    data[i] = oldData[i];
                }
                delete[] oldData;
                theCapacity *= 2;
            }
        }
        data[theSize] = val;
        theSize++;
    }

    size_t size() const { return theSize; }
    void clear() { theSize = 0; }
    void pop_back() { theSize--; }
    // Operator overload for square brackets (v[index])
    George operator[](size_t index) const { return data[index]; }
    // v[index] = val;
    George& operator[](size_t index) {
        return data[index];
    }  // reference return

    // overload begin() and end() with const and non-const version

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + theSize); }

    Const_Iterator begin() const { return Const_Iterator(data); }
    Const_Iterator end() const { return Const_Iterator(data + theSize); }

private:
    size_t theSize;  // C++ does not allow to have field & method with same name
    size_t theCapacity;
    George* data;
};

// void printVec(const Vector& v) {
// void printVec(const Vector<int>& v) {
template <typename Mary>
void printVec(const Vector<Mary>& v) {
    cout << "[ ";
    for (int val : v) {
        cout << val << " ";
    }

    for (Mary m : v) {
        cout << m << ' ';
    }
}

int main() {
    Vector<int> v;
    v.push_back(17);
    v.push_back(42);
    v.push_back(6);
    v.push_back(28);

    Vector<int> a = v;

    Vector<double> vecDouble;

    printVec(v);

    // v = 17;
    // the compiler would interpret it as Vector(17), but we need to make
    // it reporting an error!

    v[0] = 100;

    // Vector v2 = v;
    Vector<int> v2 = v;

    for (int val : v2) {
        cout << val << ' ';
    }
    cout << endl;
    // equivalent to
    // for (const int* p = v.begin(); p != v.end(); ++p) {
    //     int temp = *p;
    //     cout << temp << ' ';
    // }
    // cout << endl;

    for (int& val : v2) {
        val += 2;
    }
    printVec(v2);
    // equivalent to
    for (Vector<int>::Iterator iter = v2.begin(); iter != v2.end(); ++iter) {
        *iter += 2;
    }
}
