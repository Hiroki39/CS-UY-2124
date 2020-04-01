#include <iostream>
#include <string>
#include "Course.hpp"
#include "Student.hpp"
using namespace std;

namespace BrooklynPoly {
    // Course Implementation Codes
    ostream& operator<<(ostream& os, const Course& rhs) {
        os << rhs.name << ":";
        if (rhs.students.empty()) {
            os << " No Students";
        } else {
            for (Student* studentp : rhs.students) {
                os << " " << studentp->getName();
            }
        }
        os << endl;
        return os;
    }

    Course::Course(const string& courseName) : name(courseName) {}
    const string& Course::getName() const { return name; }

    bool Course::addStudent(Student* studentp) {
        if (studentp->addCourse(this)) {
            students.push_back(studentp);
            return true;
        }
        return false;
    }

    bool Course::dropStudent(Student* drop_studentp) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i] == drop_studentp) {
                students[i]->removedFromCourse(this);
                students[i] = students.back();
                students.pop_back();
                return true;
            }
        }
        return false;
    }

    void Course::removeStudentsFromCourse() {
        for (Student* studentp : students) {
            studentp->removedFromCourse(this);
        }
        students.clear();
    }
}  // namespace BrooklynPoly
