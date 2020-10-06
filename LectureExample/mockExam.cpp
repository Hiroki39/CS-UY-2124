#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Performer {
public:
    Performer(const string& name) : name(name), hired(false) {}

    virtual void perform() const = 0;
    bool getHiredStatus() const { return hired; }
    void changeHiredStatus() { hired = !hired; }

protected:
    string getName() const { return name; }

private:
    string name;
    bool hired;
};

class Actor : public Performer {
public:
    Actor(const string& name, const string& scripts)
        : Performer(name), scripts(scripts) {}
    void perform() const {
        cout << "I am " << getName() << ". " << scripts << endl;
    }

private:
    string scripts;
};

class Mime : public Performer {
public:
    Mime(const string& name) : Performer(name) {}
    void perform() const { cout << "(silence)" << endl; }
};

class Company {
public:
    bool hire(Performer& performer) {
        if (!performer.getHiredStatus()) {
            performers.push_back(&performer);
            performer.changeHiredStatus();
            return true;
        }
        return false;
    }

    void showtime() {
        for (Performer* performerp : performers) {
            performerp->perform();
        }
    }

private:
    vector<Performer*> performers;
};

int main() {
    Company troupe;
    Company otherTroupe;
    Actor frog("Froggie", "Hiya, kids!");
    Mime red("Red Skelton");
    Actor bogie("Humphrey Bogart", "Play it again.");
    troupe.hire(frog);
    otherTroupe.hire(frog);  // ​Nothing​ happens​. Froggie was already
                             // hired. troupe.hire(red);
    troupe.hire(bogie);
    troupe.showtime();
}
