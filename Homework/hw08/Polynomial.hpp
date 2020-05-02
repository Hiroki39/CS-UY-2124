#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <iostream>
#include <vector>

namespace Algebra {

    class Polynomial {
        struct Term;

        // non-member friend functions
        friend void printTerm(Polynomial::Term* termptr, int degree);
        friend std::ostream& operator<<(std::ostream& os,
                                        const Polynomial& rhs);
        friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);

    public:
        // constructors
        Polynomial();
        Polynomial(const std::vector<int>& coefficients);
        Polynomial(const Polynomial& rhs);

        // member operators
        Polynomial& operator+=(const Polynomial& rhs);
        Polynomial& operator=(const Polynomial& rhs);

        // add/delete Terms
        void addLowestTerm(int data);
        Polynomial::Term* addHighestTerm(int data, Term* curr_highest);
        void clearLeadingZeroes();
        void clearPolynomial(Term* curr_term);

        // evaluation
        int evaluate(int val) const;

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
