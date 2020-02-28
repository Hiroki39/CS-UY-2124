#include <iostream>
#include <vector>
using namespace std;

class Section;
class StudentRecord {
  friend ostream& operator<<(ostream& os, const Section& sec);

public:
  StudentRecord(const string& theStudentName)
      : studentname(theStudentName), grades(14, -1) {}
  string getStudentName() const { return studentname; }
  void setStudentGrade(int theGrade, int labCount) {
    grades[labCount - 1] = theGrade;
  }

private:
  string studentname;
  vector<int> grades;
};

class Section {
  friend ostream& operator<<(ostream& os, const Section& sec);

public:
  class TimeSlot {
    friend ostream& operator<<(ostream& os, const Section& sec);

  public:
    TimeSlot(const string& theDay, int theStartTime)
        : day(theDay), starttime(theStartTime) {}

  private:
    string day;
    int starttime;
  };

  Section(const string& theSecName, const string& theDay, int theStartTime)
      : secname(theSecName), slot(theDay, theStartTime) {}
  Section(const Section& anotherSection)
      : secname(anotherSection.secname), slot(anotherSection.slot) {
    for (size_t i = 0; i < anotherSection.records.size(); i++) {
      records.emplace_back(new StudentRecord(*anotherSection.records[i]));
    }
  }

  vector<StudentRecord*>& getRecord() { return records; }
  void addStudent(const string& theStudentName) {
    records.emplace_back(new StudentRecord(theStudentName));
  }

  ~Section() {
    cout << "section " << secname << " is being deleted" << endl;
    for (StudentRecord*& recordp : records) {
      cout << "deleting " << recordp->getStudentName() << endl;
      delete recordp;
    }
  }

private:
  string secname;
  TimeSlot slot;
  vector<StudentRecord*> records;
};

class LabWorker {
  friend ostream& operator<<(ostream& os, const LabWorker& worker);

public:
  LabWorker(const string& theName) : name(theName), sec(nullptr) {}
  void addSection(Section& theSec) { sec = &theSec; }
  void addGrade(const string& theStudentName, int theGrade, int labCount) {
    for (StudentRecord*& recordp : sec->getRecord()) {
      if (recordp->getStudentName() == theStudentName) {
        recordp->setStudentGrade(theGrade, labCount);
      }
    }
  }

private:
  string name;
  Section* sec;
};

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {
  cout << "Test 1: Defining a section\n";
  Section secA2("A2", "Tuesday", 16);
  cout << secA2 << endl;

  cout << "\nTest 2: Adding students to a section\n";
  secA2.addStudent("John");
  secA2.addStudent("George");
  secA2.addStudent("Paul");
  secA2.addStudent("Ringo");
  cout << secA2 << endl;

  cout << "\nTest 3: Defining a lab worker.\n";
  LabWorker moe("Moe");
  cout << moe << endl;

  cout << "\nTest 4: Adding a section to a lab worker.\n";
  moe.addSection(secA2);
  cout << moe << endl;

  cout << "\nTest 5: Adding a second section and lab worker.\n";
  LabWorker jane("Jane");
  Section secB3("B3", "Thursday", 11);
  secB3.addStudent("Thorin");
  secB3.addStudent("Dwalin");
  secB3.addStudent("Balin");
  secB3.addStudent("Kili");
  secB3.addStudent("Fili");
  secB3.addStudent("Dori");
  secB3.addStudent("Nori");
  secB3.addStudent("Ori");
  secB3.addStudent("Oin");
  secB3.addStudent("Gloin");
  secB3.addStudent("Bifur");
  secB3.addStudent("Bofur");
  secB3.addStudent("Bombur");
  jane.addSection(secB3);
  cout << jane << endl;

  cout << "\nTest 6: Adding some grades for week one\n";
  moe.addGrade("John", 17, 1);
  moe.addGrade("Paul", 19, 1);
  moe.addGrade("George", 16, 1);
  moe.addGrade("Ringo", 7, 1);
  cout << moe << endl;

  cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
  moe.addGrade("John", 15, 3);
  moe.addGrade("Paul", 20, 3);
  moe.addGrade("Ringo", 0, 3);
  moe.addGrade("George", 16, 3);
  cout << moe << endl;

  cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
       << "those students (or rather their records?)\n";

  cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
       << "then make sure the following call works properly, i.e. no memory "
          "leaks\n";
  doNothing(secA2);
  cout << "Back from doNothing\n\n";

}  // main

// operator overload for LabWorker
ostream& operator<<(ostream& os, const LabWorker& worker) {
  if (!worker.sec) {
    os << worker.name << " does not have a section" << endl;
    return os;
  } else {
    os << worker.name << " has " << *worker.sec;
    return os;
  }
}

// operator overload for Section
ostream& operator<<(ostream& os, const Section& sec) {
  os << "Section " << sec.secname << ", Time slot: [Day: " << sec.slot.day
     << ", Start time: ";
  if (sec.slot.starttime > 12) {
    os << sec.slot.starttime - 12 << "pm";
  } else {
    os << sec.slot.starttime << "am";
  }
  os << "], Students:" << endl;
  for (StudentRecord* recordp : sec.records) {
    os << "Name: " << recordp->studentname << ", Grades:";
    for (int curr_grade : recordp->grades) {
      os << " " << curr_grade;
    }
    os << endl;
  }
  return os;
}
