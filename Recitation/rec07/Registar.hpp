#ifndef REGISTAR_HPP
#define REGISTAR_HPP

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
  class Course;
  class Student;

  class Registrar {
    friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);

  public:
    Registrar();
    bool addCourse(const std::string& courseName);
    bool addStudent(const std::string& studentName);
    bool enrollStudentInCourse(const std::string& studentName,
                               const std::string& courseName);
    bool cancelCourse(const std::string& courseName);
    bool changeStudentName(const std::string& oldName,
                           const std::string& newName);
    bool dropStudentFromCourse(const std::string& studentName,
                               const std::string& courseName);
    bool removeStudent(const std::string& studentName);
    void purge();

  private:
    size_t findStudent(const std::string& studentName) const;
    size_t findCourse(const std::string& courseName) const;

    std::vector<Course*> courses;
    std::vector<Student*> students;
  };

}  // namespace BrooklynPoly
#endif
