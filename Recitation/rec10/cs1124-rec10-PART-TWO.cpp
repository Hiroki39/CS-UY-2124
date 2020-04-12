#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const { cout << "To make a sound... "; }
    virtual void normalPlay() const = 0;
};

class Percussion : public Instrument {
public:
    // using Instrument::Instrument;
    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};

class Drum : public Percussion {
    // using Percussion::Percussion;
    void normalPlay() const override { cout << "Boom"; }
};

class Cymbal : public Percussion {
    using Percussion::Percussion;
    void normalPlay() const override { cout << "Crash"; }
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
    void normalPlay() const override { cout << "Blat"; }
};

class Trumpet : public Brass {
    using Brass::Brass;
    void normalPlay() const override { cout << "Toot"; }
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
    void normalPlay() const override { cout << "Squawk"; }
};

class Violin : public String {
    using String::String;
    void normalPlay() const override { cout << "Screech"; }
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
                Instrument* result(instrp);
                instrp = nullptr;
                return result;
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

    void play() const {
        if (instr) {
            instr->normalPlay();
        }
    }

private:
    Instrument* instr;
};

class Orch {
public:
    void addPlayer(Musician& member) { members.push_back(&member); }
    void play() const {
        for (Musician* member : members) {
            member->play();
        }
        cout << endl;
    }

private:
    vector<Musician*> members;
};
// PART TWO
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    // Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    // The orchestra performs
    cout << "orch performs\n";
    orch.play();

    // Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    // Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    // Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    // Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());
    // Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    // The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // Ralph joins the orchestra.
    orch.addPlayer(ralph);

    // The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    // The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // Morgan joins the orchestra.
    orch.addPlayer(morgan);

    // The orchestra performs.
    cout << "orch performs\n";
    orch.play();

}  // main
