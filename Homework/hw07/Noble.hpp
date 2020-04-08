#ifndef NOBLE_HPP
#define NOBLE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {

    class Protector;

    // Simulate the behavior of Noble
    class Noble {
    public:
        // constructor
        Noble(const std::string& theName);

        // getters and setters
        const std::string& getName() const;

        void battle(Noble& enemy);  // Bbttle between Nobles
        void die();  // change the status of "alive" and set strength to 0

        // pure virtual methods
        virtual int getStrength() const = 0;
        // if the instance is a Lord, update strength of every Protector
        // if it is a PersonWithStrengthToFight, update itself's strength
        virtual void updateStrength(int winner_strength,
                                    int loser_strength) = 0;
        // if the instance is a Lord, call defend() for every Protector
        // if it is a PersonWithStrengthToFight, output "Ugh!"
        virtual void defend() const = 0;

    protected:  // protected getter and setter
        void changeAliveStatus();
        bool getAliveStatus() const;

    private:  // variables of Noble class
        std::string name;
        bool alive;
    };  // class Noble

    class Lord : public Noble {
    public:
        Lord(const std::string& theName);  // constructor

        int getStrength() const override;
        // multiply strength of each protector with the ratio
        void updateStrength(int winner_strength, int loser_strength) override;
        void defend() const override;  // call defend() for every Protector
        // hire/fire a protector
        bool hire(Protector& someprotector);
        bool fire(Protector& someprotector);
        // attempt to remove a protector (fire/runaway)
        bool remove(Protector& someprotector);

    private:  // variables of Lord class
        std::vector<Protector*> army;
    };  // class Lord

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& theName,
                                  int theStrength);  // constructor

        // getter and setter
        int getStrength() const override;
        void updateStrength(int winner_strength, int loser_strength) override;

        void defend() const override;

    private:  // variables of PersonWithStrengthToFight class
        int strength;
    };  // class PersonWithStrengthToFight

}  // namespace WarriorCraft

#endif
