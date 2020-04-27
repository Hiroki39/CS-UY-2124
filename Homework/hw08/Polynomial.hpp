#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <iostream>
#include <vector>

namespace Algebra {

    struct Term;

    class Polynomial {
        // non-member friend operators
        friend std::ostream operator<<(std::ostream& os, const Polynomial& rhs);
        friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);

    public:
        // constructors
        Polynomial();
        Polynomial(const std::vector<int>& coefficients);
        Polynomial(const Polynomial& rhs);

        // member operators
        Polynomial& operator+=(const Polynomial& rhs);
        Polynomial& operator=(const Polynomial& rhs);

        void addLowestTerm(int data);

        int eval(int val) const;

        void clearPolynomial(Term* startpoint);

        // destructor
        ~Polynomial();

    private:
        // nested Term struct
        struct Term {
            // constructor
            Term(int coefficient = 0, Term* next = nullptr);

            // public variables
            int coefficient;
            Term* next;
        };

        Term* headptr;
        int degree;
    };

    // non-member non-friend operators
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

}  // namespace Algebra

#endif
