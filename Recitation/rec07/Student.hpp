#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Course;
    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);

    public:
        // Student methods needed by Registrar
        Student(const std::string& theName);
        const std::string& getName() const;
        void setName(const std::string& newName);
        bool addCourse(Course* coursep);

        // Student method needed by Course
        void removedFromCourse(Course* coursep);
        void dropFromCourses();

    private:
        std::string name;
        std::vector<Course*> courses;
    };
}  // namespace BrooklynPoly
#endif
