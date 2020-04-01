#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include <fstream>
#include <iostream>
#include <string>

namespace WarriorCraft {

    class Noble;

    // Simulate the behavior of Warrior
    class Warrior {
        // friend funtion prorotype
        friend std::ostream& operator<<(std::ostream& os,
                                        const Warrior& somewarrior);

    public:
        // constructor
        Warrior(const std::string& theName, int theStrength);

        // getters and setters
        const std::string& getName() const;
        int getStrength() const;
        void setStrength(int theStrength);
        void setLord(Noble* nobleptr);
        Noble* getLord() const;

        // let the warrior runaway
        bool runaway();

    private:
        // private variables of Warrior class
        std::string name;
        int strength;
        Noble* lord;
    };  // class Warrior

}  // namespace WarriorCraft

#endif
