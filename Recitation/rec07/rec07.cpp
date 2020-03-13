/*
  rec07.cpp
  CS2124
  Hongyi Zheng
  Yes, you may add other methods.
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
  friend ostream& operator<<(ostream& os, const Course& rhs);

public:
  // Course methods needed by Registrar
  Course(const string& courseName);
  const string& getName() const;
  bool addStudent(Student* studentp);
  void removeStudentsFromCourse();

private:
  string name;
  vector<Student*> students;
};

class Student {
  friend ostream& operator<<(ostream& os, const Student& rhs);

public:
  // Student methods needed by Registrar
  Student(const string& theName);
  const string& getName() const;
  bool addCourse(Course* coursep);

  // Student method needed by Course
  void removedFromCourse(Course* coursep);

private:
  string name;
  vector<Course*> courses;
};

class Registrar {
  friend ostream& operator<<(ostream& os, const Registrar& rhs);

public:
  Registrar();
  bool addCourse(const string& courseName);
  bool addStudent(const string& studentName);
  bool enrollStudentInCourse(const string& studentName,
                             const string& courseName);
  bool cancelCourse(const string& courseName);
  void purge();

private:
  size_t findStudent(const string& studentName) const;
  size_t findCourse(const string& courseName) const;

  vector<Course*> courses;
  vector<Student*> students;
};

int main() {
  Registrar registrar;

  cout << "No courses or students added yet\n";
  cout << registrar << endl;

  cout << "AddCourse CS101.001\n";
  registrar.addCourse("CS101.001");
  cout << registrar << endl;

  cout << "AddStudent FritzTheCat\n";
  registrar.addStudent("FritzTheCat");
  cout << registrar << endl;

  cout << "AddCourse CS102.001\n";
  registrar.addCourse("CS102.001");
  cout << registrar << endl;

  cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
  registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
  cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
  registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
  cout << registrar << endl;

  cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
  cout << "Should fail, i.e. do nothing, "
       << "since Bullwinkle is not a student.\n";
  registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
  cout << registrar << endl;

  cout << "CancelCourse CS102.001\n";
  registrar.cancelCourse("CS102.001");
  cout << registrar << endl;

  /*
  // [OPTIONAL - do later if time]
  cout << "ChangeStudentName FritzTheCat MightyMouse\n";
  registrar.changeStudentName("FritzTheCat", "MightyMouse");
  cout << registrar << endl;

  cout << "DropStudentFromCourse MightyMouse CS101.001\n";
  registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
  cout << registrar << endl;

  cout << "RemoveStudent FritzTheCat\n";
  registrar.removeStudent("FritzTheCat");
  cout << registrar << endl;
  */

  cout << "Purge for start of next semester\n";
  registrar.purge();
  cout << registrar << endl;
}

// Course codes
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

void Course::removeStudentsFromCourse() {
  for (Student* studentp : students) {
    studentp->removedFromCourse(this);
  }
  students.clear();
}

// Student codes
ostream& operator<<(ostream& os, const Student& rhs) {
  os << rhs.name << ":";
  if (rhs.courses.empty()) {
    os << " No Courses";
  } else {
    for (Course* coursep : rhs.courses) {
      os << " " << coursep->getName();
    }
  }
  os << endl;
  return os;
}

// Student methods needed by Registrar
Student::Student(const string& theName) : name(theName) {}
const string& Student::getName() const { return name; }

bool Student::addCourse(Course* add_coursep) {
  for (Course* coursep : courses) {
    if (coursep->getName() == add_coursep->getName()) {
      return false;
    }
  }
  courses.push_back(add_coursep);
  return true;
}

// Student method needed by Course
void Student::removedFromCourse(Course* removed_coursep) {
  size_t i;
  for (i = 0; i < courses.size(); i++) {
    if (courses[i] == removed_coursep) {
      break;
    }
  }
  courses[i] = courses[courses.size() - 1];
  courses.pop_back();
}

// Registar codes
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
