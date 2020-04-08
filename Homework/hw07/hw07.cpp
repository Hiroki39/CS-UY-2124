/*
    hw07.cpp
    Sec C, April 5, 2020
    Hongyi Zheng
    Simulate battles between Nobles(Lord and PersonWithStrengthToFight) and
    Lord's Protectors, add defend() method for Nobles and Protectors, remove
    some redundant code.
    In the hire() method, if an attempt to hire fails, it will not only return
    false but also output a sentence indicating the reason of failure. Thus the
    output of this test file will have a few more lines than the standard
    output.
*/
#include "Noble.hpp"
#include "Protector.hpp"
using namespace std;
using namespace WarriorCraft;

int main() {  // test code
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hire(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hire(hardy);
    janet.hire(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hire(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hire(pethora);
    janet.hire(thora);
    sam.hire(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
