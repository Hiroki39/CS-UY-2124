// Doubly linked list
// Test code

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    struct Node;
    friend ostream& operator<<(ostream& os, const List& rhs) {
        for (int data : rhs) {
            os << data << ' ';
        }
        return os;
    }

public:
    class Iterator {
        friend List;

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return lhs.currNode != rhs.currNode;
        }

    public:
        Iterator(Node* p) : currNode(p) {}
        Iterator& operator++() {
            currNode = currNode->next;
            return *this;
        }
        Iterator& operator--() {
            currNode = currNode->prior;
            return *this;
        }
        int& operator*() const { return currNode->data; }

    private:
        Node* currNode;
    };

    class Const_Iterator {
        friend List;

        friend bool operator!=(const Const_Iterator& lhs,
                               const Const_Iterator& rhs) {
            return lhs.currNode != rhs.currNode;
        }

    public:
        Const_Iterator(Node* p) : currNode(p) {}
        Const_Iterator& operator++() {
            currNode = currNode->next;
            return *this;
        }
        Const_Iterator& operator--() {
            currNode = currNode->prior;
            return *this;
        }
        const int& operator*() const { return currNode->data; }

    private:
        Node* currNode;
    };

    List() : theSize(0), header(new Node()), trailer(new Node()) {
        header->next = trailer;
        trailer->prior = header;
    }

    List(const List& rhs) : List() {
        for (int data : rhs) {
            push_back(data);
        }
    }

    List& operator=(const List& rhs) {
        if (&rhs != this) {
            clear();
            for (int data : rhs) {
                push_back(data);
            }
        }
        return *this;
    }

    ~List() {
        cout << "~List()" << endl;
        clear();
        delete header;
        delete trailer;
    }

    Iterator insert(const Iterator& nextIter, int data) {
        Node* nextNode = nextIter.currNode;
        nextNode->prior = new Node(data, nextNode->prior, nextNode);
        nextNode->prior->prior->next = nextNode->prior;
        ++theSize;
        return Iterator(nextNode->prior);
    }

    void push_front(int data) { insert(begin(), data); }
    void push_back(int data) { insert(end(), data); }

    Iterator erase(const Iterator& victimIter) {
        Node* victimNode = victimIter.currNode;
        victimNode->prior->next = victimNode->next;
        victimNode->next->prior = victimNode->prior;
        Iterator nextIter(victimNode->next);
        delete victimNode;
        --theSize;
        return nextIter;
    }

    void pop_front() {
        if (theSize) {
            erase(begin());
        }
    }

    void pop_back() {
        if (theSize) {
            erase(--end());
        }
    }

    int& front() { return header->next->data; }
    int front() const { return header->next->data; }

    int& back() { return trailer->prior->data; }
    int back() const { return trailer->prior->data; }

    Iterator begin() { return Iterator(header->next); }
    Const_Iterator begin() const { return Const_Iterator(header->next); }

    Iterator end() { return Iterator(trailer); }
    Const_Iterator end() const { return Const_Iterator(trailer); }

    int size() const { return theSize; }

    int operator[](size_t index) const {
        Const_Iterator iter = begin();
        for (size_t i = 0; i < index; ++i) {
            ++iter;
        }
        return *iter;
    }

    int& operator[](size_t index) {
        Iterator iter = begin();
        for (size_t i = 0; i < index; ++i) {
            ++iter;
        }
        return *iter;
    }

    void clear() {
        Iterator iter = begin();
        while (iter != end()) {
            iter = erase(iter);
        }
    }

private:
    struct Node {
        Node(int data = 0, Node* prior = nullptr, Node* next = nullptr)
            : data(data), prior(prior), next(next) {}
        int data;
        Node* prior;
        Node* next;
    };
    int theSize;
    Node* header;
    Node* trailer;
};

bool operator==(const List::Iterator& lhs, const List::Iterator& rhs) {
    return !(lhs != rhs);
}

bool operator==(const List::Const_Iterator& lhs,
                const List::Const_Iterator& rhs) {
    return !(lhs != rhs);
}

// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size() << ", front: " << myList.front()
         << ", back(): " << myList.back() << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {
    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i * i << ");\n";
        myList.push_back(i * i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i * i << ");\n";
        myList.push_front(i * i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i * i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) myList.push_back(i * i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.push_back(i * i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    // for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i * i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i * i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i * i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
