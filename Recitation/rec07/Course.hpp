#ifndef COURSE_HPP
#define COURSE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Student;

    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);

    public:
        // Course methods needed by Registrar
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student* studentp);
        bool dropStudent(Student* drop_studentp);
        void removeStudentsFromCourse();

    private:
        std::string name;
        std::vector<Student*> students;
    };
}  // namespace BrooklynPoly
#endif
