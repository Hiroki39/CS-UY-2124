#include <iostream>
#include <string>
#include <vector>
#include "Course.hpp"
#include "Registar.hpp"
#include "Student.hpp"
using namespace std;

namespace BrooklynPoly {
  // Registar Implemention Codes
  ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registar's Report" << endl;
    os << "Courses:" << endl;
    for (Course* coursep : rhs.courses) {
      os << *coursep;
    }
    os << "Students:" << endl;
    for (Student* studentp : rhs.students) {
      os << *studentp;
    }
    return os;
  }

  Registrar::Registrar() {}

  bool Registrar::addCourse(const string& courseName) {
    if (findCourse(courseName) == courses.size()) {
      courses.push_back(new Course(courseName));
      return true;
    }
    return false;
  }
  bool Registrar::addStudent(const string& studentName) {
    if (findStudent(studentName) == students.size()) {
      students.push_back(new Student(studentName));
      return true;
    }
    return false;
  }

  bool Registrar::enrollStudentInCourse(const string& studentName,
                                        const string& courseName) {
    size_t courseindex = findCourse(courseName);
    size_t studentindex = findStudent(studentName);
    if (courseindex < courses.size() && studentindex < students.size()) {
      return courses[courseindex]->addStudent(students[studentindex]);
    }
    return false;
  }

  bool Registrar::cancelCourse(const string& courseName) {
    size_t courseindex = findCourse(courseName);
    if (courseindex < courses.size()) {
      courses[courseindex]->removeStudentsFromCourse();
      delete courses[courseindex];
      courses[courseindex] = courses[courses.size() - 1];
      courses.pop_back();
      return true;
    }
    return false;
  }

  bool Registrar::changeStudentName(const string& oldName,
                                    const string& newName) {
    size_t studentindex = findStudent(oldName);
    if (studentindex < students.size()) {
      students[studentindex]->setName(newName);
      return true;
    }
    return false;
  }

  bool Registrar::dropStudentFromCourse(const string& studentName,
                                        const string& courseName) {
    size_t courseindex = findCourse(courseName);
    size_t studentindex = findStudent(studentName);
    if (courseindex < courses.size() && studentindex < students.size()) {
      courses[courseindex]->dropStudent(students[studentindex]);
      courses[courseindex] = courses.back();
      courses.pop_back();
      return true;
    }
    return false;
  }

  bool Registrar::removeStudent(const string& studentName) {
    size_t studentindex = findStudent(studentName);
    if (studentindex < students.size()) {
      students[studentindex]->dropFromCourses();
      delete students[studentindex];
      students[studentindex] = students.back();
      students.pop_back();
      return true;
    }
    return false;
  }

  void Registrar::purge() {
    for (Student* studentp : students) {
      delete studentp;
    }
    students.clear();
    for (Course* coursep : courses) {
      delete coursep;
    }
    courses.clear();
  }

  size_t Registrar::findStudent(const string& studentName) const {
    for (size_t i = 0; i < students.size(); i++) {
      if (students[i]->getName() == studentName) {
        return i;
      }
    }
    return students.size();
  }

  size_t Registrar::findCourse(const string& courseName) const {
    for (size_t i = 0; i < courses.size(); i++) {
      if (courses[i]->getName() == courseName) {
        return i;
      }
    }
    return courses.size();
  }

}  // namespace BrooklynPoly
