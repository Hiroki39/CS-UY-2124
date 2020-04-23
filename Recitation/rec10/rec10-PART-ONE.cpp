#include <iostream>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const { cout << "To make a sound... "; }
};

class Percussion : public Instrument {
public:
    using Instrument::Instrument;
    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};

class Drum : public Percussion {
    using Percussion::Percussion;
};

class Cymbal : public Percussion {
    using Percussion::Percussion;
};

class Brass : public Instrument {
public:
    Brass(int mouthpiece) : mouthpiece(mouthpiece) {}
    void makeSound() const override {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }

private:
    int mouthpiece;
};

class Trombone : public Brass {
    using Brass::Brass;
};

class Trumpet : public Brass {
    using Brass::Brass;
};

class String : public Instrument {
public:
    String(int pitch) : pitch(pitch) {}
    void makeSound() const override {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }

private:
    int pitch;
};

class Cello : public String {
    using String::String;
};

class Violin : public String {
    using String::String;
};

class MILL {
public:
    void receiveInstr(Instrument& instr) {
        instr.makeSound();
        for (Instrument*& instrp : inventory) {
            if (!instrp) {
                instrp = &instr;
                return;
            }
        }
        inventory.push_back(&instr);
    }

    void dailyTestPlay() const {
        for (Instrument* instrp : inventory) {
            if (instrp) {
                instrp->makeSound();
            }
        }
    }

    Instrument* loanOut() {
        for (Instrument*& instrp : inventory) {
            if (instrp) {
                Instrument* temp_instrp = instrp;
                instrp = nullptr;
                return temp_instrp;
            }
        }
        return nullptr;
    }

private:
    vector<Instrument*> inventory;
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr)
            instr->makeSound();
        else
            cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};

// PART ONE
int main() {
    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    // // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;

    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    cout << "Daily test -------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << endl << endl;

    groucho.testPlay();
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";

    // // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());

    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << endl;
}
