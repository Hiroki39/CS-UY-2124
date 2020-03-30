#include <fstream>
#include <iostream>
#include <string>
#include "Rational.hpp"
using namespace std;

namespace CS2124 {
  // Rational Implemention Codes
  ostream& operator<<(ostream& os, const Rational& rhs) {
    os << rhs.numerator << "/" << rhs.denominator;
    return os;
  }
  istream& operator>>(istream& is, Rational& rhs) {
    char skip;
    is >> rhs.numerator >> skip >> rhs.denominator;
    rhs.normalize();
    return is;
  }

  Rational::Rational(int numerator, int denominator)
      : numerator(numerator), denominator(denominator) {
    normalize();
  }

  // op+= method
  Rational& Rational::operator+=(const Rational& rhs) {
    numerator = rhs.denominator * numerator + rhs.numerator * denominator;
    denominator *= rhs.denominator;
    normalize();
    return *this;
  }

  // pre&post increment operator methods
  Rational& Rational::operator++() {
    numerator += denominator;
    return *this;
  }
  Rational Rational::operator++(int dummy) {
    Rational original(*this);
    numerator += denominator;
    return original;
  }

  // bool operator method
  Rational::operator bool() const { return numerator != 0; }

  void Rational::normalize() {
    int gcd = greatestCommonDivisor(numerator, denominator);
    numerator /= gcd;       // devide numerator&denominator with
    denominator /= gcd;     // greatest common divisor of them
    if (denominator < 0) {  // if the denominator is negative, flip
      denominator *= -1;    // the sign of both denominator and numerator
      numerator *= -1;
    }
  }

  int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
      int temp = x % y;
      x = y;
      y = temp;
    }
    return x;
  }

  // op+ non-member
  Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result += rhs;
    return result;
  }

  // pre & post decrement non-member
  Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
  }

  Rational operator--(Rational& rhs, int dummy) {
    Rational original(rhs);
    rhs += -1;
    return original;
  }

  // == & != non-member
  bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator == rhs.numerator && lhs.numerator == rhs.denominator;
  }
  bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
  }

  // op< non-member
  bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.numerator / lhs.denominator < rhs.numerator / rhs.denominator;
  }
  // op<=, >, >= non-friend non-member
  bool operator<=(const Rational& lhs, const Rational& rhs) {
    return lhs < rhs || lhs == rhs;
  }
  bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs <= rhs);
  }
  bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
  }
}  // namespace CS2124
