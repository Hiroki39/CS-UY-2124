/*
    hw08.cpp
    Sec C, May 4, 2020
    Hongyi Zheng
    The Polynomial Class
*/
#include "Polynomial.hpp"
using namespace std;

namespace Algebra {
    // Polynomial implementation code

    // non-member friend functions

    // helper function of << operatorfunction, output Polynomial recursively
    void printTerm(Polynomial::Term* termptr, int degree) {
        if (termptr->next) {
            printTerm(termptr->next, degree + 1);
            if (termptr->coefficient) cout << " + ";
        }
        if (termptr->coefficient) {
            if (termptr->coefficient != 1 || degree == 0)
                cout << termptr->coefficient;
            if (degree > 0) {
                cout << "x";
                if (degree > 1) cout << "^" << degree;
            }
        } else if (!termptr->next)
            cout << 0;
    }

    // << operator overload, calls the helper function
    ostream& operator<<(ostream& os, const Polynomial& rhs) {
        printTerm(rhs.headptr, 0);
        return os;
    }

    // == operator overload
    bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
        if (lhs.degree != rhs.degree)
            return false;  // comparing Term by Term only if degrees are equal
        Polynomial::Term* lhs_curr = lhs.headptr;
        Polynomial::Term* rhs_curr = rhs.headptr;
        while (lhs_curr) {
            if (lhs_curr->coefficient != rhs_curr->coefficient) return false;
            lhs_curr = lhs_curr->next;
            rhs_curr = rhs_curr->next;
        }
        return true;
    }

    // non-member non-friend operators

    // + operator overload, calls the += method
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
        Polynomial result(lhs);
        return result += rhs;
    }

    // != operator overload, calls the == function
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
        return !(lhs == rhs);
    }

    // constructors

    // defualt constructor; gives a zero Polynomial
    Polynomial::Polynomial() : headptr(new Term()), degree(0) {}

    // constructor taking a vector of coefficients
    Polynomial::Polynomial(const std::vector<int>& coefficients)
        : headptr(nullptr), degree(-1) {
        for (int coefficient : coefficients) addLowestTerm(coefficient);
        clearLeadingZeroes();
    }

    // copy constructor
    Polynomial::Polynomial(const Polynomial& rhs)
        : headptr(nullptr), degree(0) {
        Term* curr_term = rhs.headptr;
        Term* lhs_prior = nullptr;
        while (curr_term) {
            lhs_prior = addHighestTerm(curr_term->coefficient, lhs_prior);
            curr_term = curr_term->next;
        }
    }

    // member operators

    // += operator overload
    Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
        Term* lhs_curr = headptr;
        Term* rhs_curr = rhs.headptr;
        Term* lhs_prior;
        while (lhs_curr) {
            if (!rhs_curr) break;  // if the degree of rhs Polynomial is lower
            lhs_curr->coefficient += rhs_curr->coefficient;
            if (!lhs_curr->next)
                lhs_prior = lhs_curr;  // save the address of the last lhs Term
                                       // for later usage
            lhs_curr = lhs_curr->next;
            rhs_curr = rhs_curr->next;
        }
        while (rhs_curr) {  // if the degree of rhs Polynomial is higher
            lhs_prior = addHighestTerm(rhs_curr->coefficient, lhs_prior);
            rhs_curr = rhs_curr->next;
        }
        clearLeadingZeroes();
        return *this;
    }

    // =(assigment) operator overload
    Polynomial& Polynomial::operator=(const Polynomial& rhs) {
        if (this != &rhs) {            // check for self-assigment
            clearPolynomial(headptr);  // delete current Polynomial
            degree = 0;
            Term* curr_term = rhs.headptr;
            Term* lhs_prior = nullptr;
            while (curr_term) {
                lhs_prior = addHighestTerm(curr_term->coefficient, lhs_prior);
                curr_term = curr_term->next;
            }
        }
        return *this;
    }

    // add current lowest Term to the Polynomial
    void Polynomial::addLowestTerm(int data) {
        headptr = new Term(data, headptr);
        ++degree;
    }

    // add the current highest Term to the Polynomial, return a poinnter to the
    // newly added Term to make it useful in while loop
    Polynomial::Term* Polynomial::addHighestTerm(int data, Term* curr_highest) {
        if (!curr_highest) {  // if a nullptr is passed in
            headptr = new Term(data);
            return headptr;
        }
        curr_highest->next = new Term(data);
        ++degree;
        return curr_highest->next;
    }

    // clear the leading zeroes in the polynomial
    void Polynomial::clearLeadingZeroes() {
        Term* curr_term = headptr;
        Term* prior = nullptr;
        while (curr_term->next) {
            if (!curr_term->next->coefficient) {
                // store the address of the first zero Term among consectutive
                // zero Terms
                if (!prior) prior = curr_term;
            } else {
                // if the coefficient of the current termis not zero, reset the
                // address of the first zero Term
                if (prior) prior = nullptr;
            }
            curr_term = curr_term->next;
        }
        if (prior) {  // if there are leading zeroes
            clearPolynomial(prior->next);
            prior->next = nullptr;
        }
    }

    // evaluate tbe polynomial
    int Polynomial::evaluate(int val) const {
        int result = 0;
        int curr_degree = 0;
        Term* curr_term = headptr;
        while (curr_term) {  // sum up the value of each term
            if (curr_term->coefficient) {
                int term_val = curr_term->coefficient;
                for (int i = 0; i < curr_degree; ++i) {
                    term_val *= val;
                }
                result += term_val;
            }
            curr_term = curr_term->next;
            ++curr_degree;
        }
        return result;
    }

    void Polynomial::clearPolynomial(Term* curr_term) {
        while (curr_term) {
            Term* prior =
                curr_term;  // store the address of the term to be deleted
            curr_term = curr_term->next;  // bump the current pointer
            delete prior;
            --degree;
        }
        curr_term = nullptr;
    }

    // destructor
    Polynomial::~Polynomial() { clearPolynomial(headptr); }

    // nested Term struct constructor
    Polynomial::Term::Term(int coefficient, Term* next)
        : coefficient(coefficient), next(next) {}
}  // namespace Algebra
