#ifndef NOBLE_HPP
#define NOBLE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {

    class Warrior;

    // Simulate the behavior of Noble
    class Noble {
        // friend funtion prorotype
        friend std::ostream& operator<<(std::ostream& os,
                                        const Noble& somenoble);

    public:
        // constructor
        Noble(const std::string& theName);

        // getters and setters
        const std::string& getName() const;
        int getArmyStrength() const;
        // multiply strength of each warrior with the ratio
        void updateArmyStrength(int winner_strength, int loser_strength);
        // change the status of "alive" and change strength of all Warriors to 0
        void die();
        // hire/fire a warrior
        bool hire(Warrior& somewarrior);
        bool fire(Warrior& somewarrior);
        // attempt to remove a warrior (fire/runaway)
        bool remove(Warrior& somewarrior);
        void battle(Noble& enemy);  // battle between Nobles

    private:
        // private variables of Noble class
        std::string name;
        std::vector<Warrior*> army;
        bool alive;
    };  // class Noble

}  // namespace WarriorCraft

#endif
