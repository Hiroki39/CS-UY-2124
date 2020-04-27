#include <iostream>
#include <vector>
using namespace std;

class Bit {
    friend ostream& operator<<(ostream& os, const Bit& theBit) {
        os << "Name: " << theBit.name << "; Boss: ";
        if (!theBit.employer) {
            os << "none";
        } else {
            os << theBit.employer->name;
        }
        os << "; Bits:";
        if (theBit.employee.empty()) {
            os << "none";
        } else {
            for (size_t i = 0; i < theBit.employee.size(); i++) {
                os << " " << theBit.employee[i]->name;
            }
        }
        os << endl;
        return os;
    }

public:
    Bit(const string& name) : name(name), employer(nullptr) {}
    bool hire(Bit& hired) {
        if ((!hired.employer) && (&hired != this) && (&hired != employer)) {
            if (hired.employer != this) {
                hired.employer = this;
                employee.push_back(&hired);
            }
            return true;
        }
        return false;
    }
    bool quit() {
        if (employer) {
            for (size_t i = 0; i < employer->employee.size(); i++) {
                if (employer->employee[i] == this) {
                    employer->employee[i] = employer->employee.back();
                    employer->employee.pop_back();
                    break;
                }
            }
            employer = nullptr;
            return true;
        }
        return false;
    }

private:
    string name;
    Bit* employer;
    vector<Bit*> employee;
};

int main() {
    Bit moe("Moe");
    Bit larry("Larry");
    Bit curly("Curly");
    Bit curly2("Curly");
    larry.hire(moe);  // Returns true
    cout << larry << endl;
    larry.hire(curly);   // Returns true
    larry.hire(curly2);  // Returns true. Now we have two chips named
    // Curly in the team
    cout << larry << endl;
    moe.hire(larry);  // Returns false. Can't hire own boss
    moe.hire(moe);    // Returns false. Can't hire self
    moe.quit();       // Returns true.
    cout << moe << endl;
    moe.hire(larry);  // Returns true.
    cout << moe << endl;
    curly2.hire(moe);  // Returns true. We are allowed to have a cycle
    cout << moe << endl;
    cout << larry << endl;
    cout << curly2 << endl;
}
