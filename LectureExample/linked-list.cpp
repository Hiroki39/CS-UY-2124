#include <iostream>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

/*
    listDisplay(Node* headPtr)
    listInsert / Remove / Append
    listLength
    listClear
    listDuplicate
 */

void listDisplay(Node* headPtr) {
    for (Node* p = headPtr; p != nullptr; p = p->next) {
        cout << p->data << ' ';
    }
    cout << endl;
}

int listLength(Node* headPtr) {
    Node* p = headPtr;
    int counter = 0;
    // while ( p != nullptr )
    while (p) {
        ++counter;
        p = p->next;
    }
    return counter;
}

void listAddHead(Node*& headPtr, int data) {
    // 1.create a node for the data
    // Node* p = new Node(data);
    // 2.make the node point to the old head node
    // p->next = headPtr;
    // Node* p = new Node(data, headPtr);
    // 3.set the headPtr to point to this new node
    // headPtr = p;
    headPtr = new Node(data, headPtr);
}

void listRemoveHead(Node*& headPtr) {
    if (headPtr == nullptr) {
    } else {
        // remember the address of the second node
        Node* second = headPtr->next;
        // delete the first node
        delete headPtr;
        // make the head pointer point to the second node
        headPtr = second;
    }
}

void listAdd(Node* prior, int data) {
    // create a node for the data
    // make the node point to the node after prior
    // make prior's node point to the new node
    prior->next = new Node(data, prior->next);
}

void listRemove(Node* prior) {
    Node* victim = prior->next;
    // reconnect prior's node to node after the victim
    prior->next = victim->next;
    // free up the node after prior
    delete victim;
}

Node* listFindTail(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;
    Node* p = headPtr;
    while (p->next) {
        p = p->next;
    }
    return p;
}

void listAddTail(Node*& headPtr, int data) {
    if (headPtr == nullptr) {
        headPtr = new Node(data);
    } else {
        // 1. go to the end
        Node* tail = listFindTail(headPtr);
        // 2. create a node for the data
        // 3. add that node to the end
        tail->next = new Node(data);
    }
}

void listRemoveTail(Node*& headPtr, int data) {
    // handle edge cases
    if (headPtr == nullptr) {
    } else if (headPtr->next == nullptr) {  // a single node
        delete headPtr;
        headPtr = nullptr;
    } else {
        // find the penultimate node (second to last) node
        Node* penultimate = headPtr;
        while (penultimate->next->next) {
            penultimate = penultimate->next;
        }
        delete penultimate->next;
        penultimate->next = nullptr;
    }
}

void listClear(Node*& headPtr) {
    while (headPtr != nullptr) {
        listRemoveHead(headPtr);
    }
}

Node* listCopy(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;  // edge case
    Node* result = new Node(headPtr->data);
    Node* last = result;
    Node* curr = headPtr;
    while (curr) {
        last->next =
            new Node(curr->data);  // not listAddTail due to complexity!
        last = last->next;
        curr = curr->next;
    }
    return result;
}

Node* listCopyR(Node* headPtr) {
    if (headPtr == nullptr) return nullptr;  // edge case
    return new Node(headPtr->data, listCopyR(headPtr->next));
}

void listPrint(Node* p) {
    if (p == nullptr) return;
    cout << p->data << ' ';
    listPrint(p->next);  // tail recursion
}

int listLengthR(Node* p) {
    if (p == nullptr) return 0;
    return listLength(p->next) + 1;  // NOT tail recursion
}

int listLengthTail(Node* p, int len = 0) {
    if (p == nullptr) return len;
    return listLengthTail(p->next, len + 1);  // tail recursion
}  // get around the limitation of the compilers!

int main() {
    Node* myList = nullptr;
    listDisplay(myList);

    // myList = new Node(17);
    listAddHead(myList, 17);

    myList->next = new Node(28);

    for (Node* p = myList; p != nullptr; p = p->next) {
        cout << p->data << ' ';
    }
    cout << endl;
}
