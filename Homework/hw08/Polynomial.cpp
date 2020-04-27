#include "polynomial.hpp"
using namespace std;

namespace Algebra {
    // constructors
    Polynomial::Polynomial() : headptr(new Term()), degree(0) {}

    Polynomial::Polynomial(const std::vector<int>& coefficients)
        : headptr(nullptr), degree(-1) {
        bool nonzero_leading_coefficient = false;
        for (int coefficient : coefficients) {
            if (!nonzero_leading_coefficient)
                if (coefficient) nonzero_leading_coefficient = true;
            if (nonzero_leading_coefficient) addLowestTerm(coefficient);
        }
        if (!nonzero_leading_coefficient) addLowestTerm(0);
    }

    // member operators
    Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
        Term* zeroterm_startpoint = nullptr;
        Term* lhs_curr = headptr;
        Term* rhs_curr = rhs.headptr;
        while (lhs_curr) {
            if (!rhs_curr) {
                zeroterm_startpoint = nullptr;
                break;
            }
            lhs_curr->coefficient += rhs_curr->coefficient;
            zeroterm_startpoint = (lhs_curr->coefficient) ? nullptr : lhs_curr;
            lhs_curr = lhs_curr->next;
            rhs_curr = rhs_curr->next;
        }
        if (zeroterm_startpoint) clearPolynomial(zeroterm_startpoint);
        return *this;
    }
    Polynomial& Polynomial::operator=(const Polynomial& rhs) {}

    void Polynomial::addLowestTerm(int data) {
        headptr = new Term(data, headptr);
        ++degree;
    }

}  // namespace Algebra
