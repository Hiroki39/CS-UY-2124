#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Complex {
  friend ostream& operator<<(ostream& os, const Complex& rhs) {
    os << rhs.real << (rhs.imag >= 0 ? "+" : "") << rhs.imag << "i";
    return os;
  }
  friend bool operator==(const Complex& lhs, const Complex& rhs);

public:
  Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}

  // c1 += c2
  // c1.operator+=(c2)
  Complex& operator+=(const Complex& rhs) {
    real += rhs.real;
    imag += rhs.imag;
    return *this;
  }

  // ++c1
  // c1.operator++();
  Complex& operator++() {
    ++real;
    return *this;
  }
  // c1++
  // c1.operator++(0);
  Complex operator++(int dummy) {
    Complex original(*this);
    ++real;
    return original;
  }

  // no return type because this is operator bool!
  explicit operator bool() const { return real != 0 || imag != 0; }

private:
  double real, imag;
};

// Usually symmetric operator would not be a method
// c1 == c2
// c1.operator==(c2)
bool operator==(const Complex& lhs, const Complex& rhs) {
  // better than if...else...
  return lhs.real == rhs.real && lhs.real == rhs.imag;
}
// c1 != c2
// c1.operator!=(c2)
bool operator!=(const Complex& lhs, const Complex& rhs) {
  return !(lhs == rhs);  // reuse the code!
}

// c1 + c2
Complex operator+(
    const Complex& lhs,
    const Complex& rhs) {  // never return a reference to local variable!
  Complex result(lhs);
  result += rhs;
  return result;
}

int main() {
  Complex c1;         // 0 + 0i
  Complex c2(27);     // 17 + 0i
  Complex c3(3, -5);  // 3 - 5i
  cout << "c1: " << c1 << endl;
  cout << "c2: " << c2 << endl;
  cout << "c3: " << c3 << endl;
  // Testing equality and inequality operators
  cout << "c1 " << (c1 == c1 ? "==" : "!=") << " c1" << endl;
  cout << "c1 " << (c1 != c1 ? "!=" : "==") << " c1" << endl;
  cout << "c1 " << (c1 != c2 ? "!=" : "==") << " c2" << endl;
  Complex one(1);
  // the compilor does a conversion
  // operator==(one, 1);
  // operator==(one, Complex(1));
  cout << "one " << (one == 1 ? "==" : "!=") << " 1" << endl;
  // the compilor won't do a conversion if "==" is a method
  // operator==(1, one);
  // operator==(Complex(1),one)
  // cout << "1 " << (1 == one ? "==" : "!=") << " one" << endl;

  // Testing "combination opeartor" op+=
  cout << (c1 += c2) << endl;

  // Testing op+
  c1 = c2 + c3;

  // Testing pre-increment
  cout << ++c1 << " " << c1 << endl;

  // Testing post-increment
  cout << c1++ << " " << c1 << endl;

  Complex zero(0);
  cout << "zero is " << (zero ? "true" : "false") << endl;
}
