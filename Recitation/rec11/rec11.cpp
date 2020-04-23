/*
    rec11.cpp
    Sec C, April 17, 2020
    Hongyi Zheng
*/
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// Node to be used a part of linked list
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// splice: insert a list into another list after the specified node
void splice(Node* headPtr, Node* prior) {
    if (!headPtr) return;
    Node* curr = headPtr;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = prior->next;
    prior->next = headPtr;
}

// isSublist: check if a list is a sublist of aonther list
Node* isSublist(Node* subHeadPtr, Node* headPtr) {
    Node* curr = headPtr;
    while (true) {
        while (curr->data != subHeadPtr->data) {
            if (!curr->next) return nullptr;
            curr = curr->next;
        }
        Node* start_node = curr;
        Node* sub_curr = subHeadPtr;
        while (sub_curr->data == curr->data) {
            if (!sub_curr->next) return start_node;
            if (!curr->next) return nullptr;
            sub_curr = sub_curr->next;
            curr = curr->next;
        }
        curr = start_node->next;
    }
}

/* The version to look for shared list if two lists do not actually share a
suffix

Node* sharedListBruteForce(Node* headPtr1, Node* headPtr2) {
    while (headPtr1) {
        Node* start = headPtr2;
        while (headPtr2) {
            if (headPtr1->data == headPtr2->data) {
                Node* start_node1 = headPtr1;
                Node* start_node2 = headPtr2;
                while (headPtr1->data == headPtr2->data) {
                    if (!headPtr1->next && !headPtr2->next) return start_node1;
                    if (!headPtr1->next || !headPtr2->next) break;
                    headPtr1 = headPtr1->next;
                    headPtr2 = headPtr2->next;
                }
                headPtr1 = start_node1;
                headPtr2 = start_node2;
            }
            headPtr2 = headPtr2->next;
        }
        headPtr2 = start;
        headPtr1 = headPtr1->next;
    }
    return nullptr;
}
*/

Node* sharedListBruteForce(Node* headPtr1, Node* headPtr2) {
    while (headPtr1) {
        Node* start = headPtr2;
        while (headPtr2) {
            if (headPtr2 == headPtr1) return headPtr1;
            headPtr2 = headPtr2->next;
        }
        headPtr1 = headPtr1->next;
        headPtr2 = start;
    }
    return nullptr;
}

Node* sharedListUsingSet(Node* headPtr1, Node* headPtr2) {
    unordered_set<Node*> addresses;
    while (headPtr1) {
        addresses.insert(headPtr1);
        headPtr1 = headPtr1->next;
    }
    while (headPtr2) {
        if (addresses.find(headPtr2) == addresses.end()) {
            headPtr2 = headPtr2->next;
        } else {
            return headPtr2;
        }
    }
    return nullptr;
}

Node* sharedListUsingLength(Node* headPtr1, Node* headPtr2) {
    int counter1 = 0;
    int counter2 = 0;
    Node* cursor1 = headPtr1;
    Node* cursor2 = headPtr2;
    while (cursor1) {
        counter1++;
        cursor1 = cursor1->next;
    }
    while (cursor2) {
        counter2++;
        cursor2 = cursor2->next;
    }
    if (counter1 > counter2) {
        for (int i = 0; i < counter1 - counter2; i++) {
            headPtr1 = headPtr1->next;
        }
    } else if (counter1 < counter2) {
        for (int i = 0; i < counter2 - counter1; i++) {
            headPtr2 = headPtr2->next;
        }
    }
    while (headPtr1) {
        if (headPtr1 == headPtr2) return headPtr1;
        headPtr1 = headPtr1->next;
        headPtr2 = headPtr2->next;
    }
    return nullptr;
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like.
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index - 1]);
    }
    return result;
}

void printList(Node* headPtr) {
    for (Node* p = headPtr; p; p = p->next) {
        cout << p->data << " ";
    }
    cout << endl;
}

void attemptMatch(Node* subHeadPtr, Node* headPtr) {
    cout << "attempt match: ";
    printList(subHeadPtr);
    Node* result = isSublist(subHeadPtr, headPtr);
    if (result) {
        printList(result);
    } else {
        cout << "Failed to match" << endl;
    }
    cout << endl;
}

int main() {  // test code
    Node* L1 = listBuild({5, 7, 9, 1});
    Node* L2 = listBuild({6, 3, 2});
    Node* Target = listBuild({7, 9, 1});

    cout << "L1: ";
    printList(L1);
    cout << "L2: ";
    printList(L2);
    cout << "Target: ";
    printList(Target);

    cout << "Splicing L2 at target in L1" << endl;
    splice(L2, isSublist(Target, L1));

    cout << "L1: ";
    printList(L1);
    cout << "L2: ";
    printList(L2);

    cout << "==================================" << endl << endl;
    cout << "Part two:" << endl;

    listClear(Target);
    Target = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Target: ";
    printList(Target);

    attemptMatch(listBuild({1}), Target);
    attemptMatch(listBuild({3, 9}), Target);
    attemptMatch(listBuild({2, 3}), Target);
    attemptMatch(listBuild({2, 4, 5, 6}), Target);
    attemptMatch(listBuild({2, 3, 2, 4}), Target);
    attemptMatch(listBuild({5, 6, 7}), Target);
    attemptMatch(listBuild({6}), Target);
    listClear(Target);

    Node* L3 = listBuild({2, 7, 2, 5, 2, 3, 3, 2, 3, 3, 4, 5});
    Node* L4 = new Node(0, L3->next->next);
    printList(sharedListBruteForce(L3, L4));
    printList(sharedListUsingSet(L3, L4));
    printList(sharedListUsingLength(L3, L4));

    listClear(L1);
    listClear(L3);
    delete L4;
}
