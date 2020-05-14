#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

// Bounded Buffer (also a stack)
class BB {
    friend ostream& operator<<(ostream& os, const BB& bb) {
        bb.mut.lock();
        for (int val : bb.buf) cout << val << ' ';
        bb.mut.unlock();
        return os;
    }

public:
    void add(int val) {
        unique_lock<mutex> lk(mut);  // similar to lock_guard
        buf.push_back(val);
        isEmpty.notify_all();
    }

    int remove() {
        unique_lock<mutex> lk(mut);
        while (!buf.size()) {  // if stack is empty
            isEmpty.wait(lk);  // wait until there is something on the stack
        }
        int val = buf.back();
        buf.pop_back();
        return val;
    }

private:
    vector<int> buf;
    mutable mutex mut;
    condition_variable isEmpty;
};

int main() {}
