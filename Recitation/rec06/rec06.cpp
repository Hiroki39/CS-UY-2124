/*
  Recitation 06
  CS2124
  Hongyi Zheng
  Focus: Dynamic arrays and copy control
 */
#include <iostream>
#include <string>
using namespace std;

class Position {
    // output operator overload for Position class
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }

public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }

private:
    string title;
    double salary;
};  // class Position

class Entry {
    // output operator overload for Entry class
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room << ' ' << rhs.phone << ", "
           << *rhs.pos;
        return os;
    }

public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {}
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }

private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
};  // class Entry

class Directory {
    // output operator for Directory class
    friend ostream& operator<<(ostream& os, const Directory& rhs) {
        for (size_t i = 0; i < rhs.size; i++) {
            cout << *rhs.entries[i] << endl;
        }
        return os;
    }

public:
    Directory()
        : size(0),
          capacity(8),
          entries(new Entry*[capacity]) {}  // intialization list
    Directory(const Directory& rhs)         // copy constructor
        : size(rhs.size),
          capacity(rhs.capacity),
          entries(new Entry*[rhs.capacity]) {
        cout << "Copy Constructor..." << endl;
        for (size_t i = 0; i < size; i++) {
            entries[i] = new Entry(*rhs.entries[i]);  // deep copy
        }
    }

    // assigment operator
    const Directory& operator=(const Directory& rhs) {
        cout << "Assigment Operator..." << endl;
        // check for self assignment
        if (&rhs != this) {
            // free up our resources
            for (size_t i = 0; i < size; i++) {
                delete entries[i];
            }
            delete[] entries;
            // allocate new resources
            entries = new Entry*[rhs.capacity];
            // copy over any information
            size = rhs.size;
            capacity = rhs.capacity;
            for (size_t i = 0; i < size; i++) {
                entries[i] = new Entry(*rhs.entries[i]);
            }
        }
        return *this;
    }

    // add a new Entry to the Directory
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity) {  // double the capacity to ensure free space
            Entry** old_entries = entries;  // keep existing data
            entries = new Entry*[2 * capacity];
            for (size_t i = 0; i < capacity; i++) {
                entries[i] = old_entries[i];  // copy over data
            }
            delete[] old_entries;
            capacity *= 2;
        }
        entries[size] = new Entry(name, room, ph, pos);  // add the Entry
        ++size;
    }

    unsigned operator[](string name) const {
        for (size_t i = 0; i < size; i++) {
            // check if entry with the name provided exists
            if (entries[i]->getName() == name) {
                return entries[i]->getPhone();
            }
        }
        return 0;  // avoid failing silently
    }

    // destructor
    ~Directory() {
        cout << "Destructor..." << endl;
        // free up space on heap
        for (size_t i = 0; i < size; i++) {
            delete entries[i];
        }
        delete[] entries;
    }

private:
    size_t size;
    size_t capacity;
    Entry** entries;
};  // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {  // test code
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    Directory d;  // Create a Directory
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;  // Using copy constructor
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;  // Assigment operator

    // Should display 1592
    cout << d2["Carmack"] << endl;
}  // main
