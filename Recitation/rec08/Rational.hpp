#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <fstream>
#include <iostream>
#include <string>

namespace CS2124 {
    class Rational {
        // friend function prototypes
        friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
        friend std::istream& operator>>(std::istream& is, Rational& rhs);
        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);

    public:
        // methods prototypes
        Rational(int numerator = 0, int denominator = 1);
        Rational& operator+=(const Rational& rhs);
        Rational& operator++();
        Rational operator++(int dummy);
        explicit operator bool() const;
        void normalize();  // normalize the rational number

    private:
        int numerator;
        int denominator;
    };  // Class Rational

    // find greates common divisor of two integers
    int greatestCommonDivisor(int x, int y);
    Rational operator+(const Rational& lhs, const Rational& rhs);
    bool operator!=(const Rational& lhs, const Rational& rhs);
    bool operator<=(const Rational& lhs, const Rational& rhs);
    bool operator>(const Rational& lhs, const Rational& rhs);
    bool operator>=(const Rational& lhs, const Rational& rhs);
    Rational& operator--(Rational& rhs);
    Rational operator--(Rational& rhs, int dummy);
}  // namespace CS2124
#endif
