/*
  rec07.cpp
  CS2124
  Hongyi Zheng
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;  // class prototype

class Course {  // friend function prototype
  friend ostream& operator<<(ostream& os, const Course& rhs);

public:
  // Course methods needed by Registrar
  Course(const string& courseName);
  const string& getName() const;
  bool addStudent(Student* studentp);
  bool dropStudent(Student* drop_studentp);
  void removeStudentsFromCourse();

private:
  string name;
  vector<Student*> students;
};  // Course class

class Student {
  friend ostream& operator<<(ostream& os, const Student& rhs);

public:
  // Student methods needed by Registrar
  Student(const string& theName);
  const string& getName() const;
  void setName(const string& newName);
  bool addCourse(Course* coursep);

  // Student method needed by Course
  void removedFromCourse(Course* coursep);
  void dropFromCourses();

private:
  string name;
  vector<Course*> courses;
};  // Student Class

class Registrar {
  friend ostream& operator<<(ostream& os, const Registrar& rhs);

public:
  Registrar();
  bool addCourse(const string& courseName);
  bool addStudent(const string& studentName);
  bool enrollStudentInCourse(const string& studentName,
                             const string& courseName);
  bool cancelCourse(const string& courseName);
  bool changeStudentName(const string& oldName, const string& newName);
  bool dropStudentFromCourse(const string& studentName,
                             const string& courseName);
  bool removeStudent(const string& studentName);
  void purge();

private:
  size_t findStudent(const string& studentName) const;
  size_t findCourse(const string& courseName) const;

  vector<Course*> courses;
  vector<Student*> students;
};  // Registar Class

int main() {  // test code
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

  cout << "ChangeStudentName FritzTheCat MightyMouse\n";
  registrar.changeStudentName("FritzTheCat", "MightyMouse");
  cout << registrar << endl;

  cout << "DropStudentFromCourse MightyMouse CS101.001\n";
  registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
  cout << registrar << endl;

  cout << "RemoveStudent MightyMouse\n";
  registrar.removeStudent("MightyMouse");
  cout << registrar << endl;

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

// Student codes
// output operator overload
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
// Constructor, getter and setter
Student::Student(const string& theName) : name(theName) {}
const string& Student::getName() const { return name; }
void Student::setName(const string& newName) { name = newName; }

// enroll Student into a course
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
// remove student from course (only used when a class is cancelled)
void Student::removedFromCourse(Course* removed_coursep) {
  size_t i;
  for (i = 0; i < courses.size(); i++) {
    if (courses[i] == removed_coursep) {
      break;
    }
  }
  courses[i] = courses.back();
  courses.pop_back();
}

// remove student from course when course is not deleted
void Student::dropFromCourses() {
  for (Course* coursep : courses) {
    coursep->dropStudent(this);
  }
  courses.clear();
}

// Registar codes
// output operator overlpad
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

// constructor
Registrar::Registrar() {}

// add a new course
bool Registrar::addCourse(const string& courseName) {
  if (findCourse(courseName) == courses.size()) {
    courses.push_back(new Course(courseName));
    return true;
  }
  return false;
}
// add a new student
bool Registrar::addStudent(const string& studentName) {
  if (findStudent(studentName) == students.size()) {
    students.push_back(new Student(studentName));
    return true;
  }
  return false;
}

// enroll student into a course
bool Registrar::enrollStudentInCourse(const string& studentName,
                                      const string& courseName) {
  size_t courseindex = findCourse(courseName);
  size_t studentindex = findStudent(studentName);
  if (courseindex < courses.size() && studentindex < students.size()) {
    return courses[courseindex]->addStudent(students[studentindex]);
  }
  return false;
}

// cancel a course
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

// change a student's name
bool Registrar::changeStudentName(const string& oldName,
                                  const string& newName) {
  size_t studentindex = findStudent(oldName);
  if (studentindex < students.size()) {
    students[studentindex]->setName(newName);
    return true;
  }
  return false;
}

// drop a stuent from a course
bool Registrar::dropStudentFromCourse(const string& studentName,
                                      const string& courseName) {
  size_t courseindex = findCourse(courseName);
  size_t studentindex = findStudent(studentName);
  if (courseindex < courses.size() && studentindex < students.size()) {
    courses[courseindex]->dropStudent(students[studentindex]);
    courses[courseindex] =
        courses.back();  // replace dropped student with the last student in the
                         // vector and pop the last element
    courses.pop_back();
    return true;
  }
  return false;
}

// drop student from all enrolled courses and delete that student
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

// delete all courses and students
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

// find a student with name and return the index
size_t Registrar::findStudent(const string& studentName) const {
  for (size_t i = 0; i < students.size(); i++) {
    if (students[i]->getName() == studentName) {
      return i;
    }
  }
  return students.size();
}

// find a course with name and return the index
size_t Registrar::findCourse(const string& courseName) const {
  for (size_t i = 0; i < courses.size(); i++) {
    if (courses[i]->getName() == courseName) {
      return i;
    }
  }
  return courses.size();
}
