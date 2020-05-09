#include <iostream>
#include <stdexcept>
using namespace std;

struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

struct TNode {
    TNode(int data = 0, TNode* left = nullptr, TNode* right = nullptr)
        : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};

bool has_even_ones(int n) {
    if (n < 2) return 1 - n;
    if (n % 2)
        return !has_even_ones(n / 2);
    else
        return has_even_ones(n / 2);
}

Node* sum_up_lists(Node* l1, Node* l2) {
    if (!l1 && !l2)
        return nullptr;
    else if (l1 && !l2)
        return new Node(l1->data, sum_up_lists(l1->next, l2));
    else if (!l1 && l2)
        return new Node(l2->data, sum_up_lists(l2->next, l1));
    else
        return new Node(l1->data + l2->data, sum_up_lists(l1->next, l2->next));
}

int find_maximum(TNode* root) {
    if (!root) throw invalid_argument("Maximum not defined on empty tree");
    if (!root->right && !root->left)
        return root->data;
    else if (!root->right && root->left)
        return max(root->data, find_maximum(root->left));
    else if (root->right && !root->left)
        return max(root->data, find_maximum(root->right));
    else
        return max(root->data,
                   max(find_maximum(root->left), find_maximum(root->right)));
}

bool palindrome(char* word, int length) {
    if (length < 2) return true;
    if (word[0] != word[length - 1]) return false;
    return palindrome(word + 1, length - 2);
}

int towers(int n, char start, char target, char spare) {
    if (n == 0) return 0;
    int moves = 2 * towers(n - 1, start, spare, target) + 1;
    cout << "towers(" << n << ", '" << start << "', '" << target << "', '"
         << spare << "'): " << moves << endl;
    return moves;
}

void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n / 2);
        cout << 'b';
        mystery(n / 2);
    }
    cout << 'c';
}

int main() {
    cout << boolalpha;
    cout << has_even_ones(10) << endl;
    cout << has_even_ones(26) << endl;
    Node* l1 = new Node(2, new Node(3, new Node(4)));
    Node* l2 = new Node(1, new Node(5));
    cout << sum_up_lists(l1, l2)->next->next->data << endl;
    char s1[] = "racecar";
    cout << palindrome(s1, 7) << endl;
    char s2[] = "noon";
    cout << palindrome(s2, 4) << endl;
    char s3[] = "mom";
    cout << palindrome(s3, 3) << endl;
    towers(10, 'a', 'b', 'c');
    mystery(5);
    cout << endl;
    TNode* t = new TNode(3, new TNode(5, new TNode(2), new TNode(6)),
                         new TNode(1, new TNode(4), new TNode(3)));
    cout << find_maximum(t) << endl;
    try {  // catch exception
        find_maximum(nullptr);
    } catch (exception& ex) {
        cout << "caught an exception: " << ex.what() << endl;
    }
}
