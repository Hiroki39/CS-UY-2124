#include <algorithm>
#include <iostream>
using namespace std;

struct TNode {
    TNode(int val, TNode* left = nullptr, TNode* right = nullptr)
        : data(val), left(left), right(right) {}
    int data;
    TNode* left;
    TNode* right;
};

int treeSum(TNode* root) {  // meaning less if passing in a nullptr!
    // if (!root->left && !root->right)
    //     return root->data;
    // else if (root->left && !root->right)
    //     return treeSum(root->left) + root->data;
    // else if (!root->left && root->right)
    //     return treeSum(root->right) + root->data;
    // else
    //     return treeSum(root->left) + treeSum(root->right) + root->data;
    int sum = root->data;
    if (root->left) sum += treeSum(root->left);
    if (root->right) sum += treeSum(root->right);
    return sum;
}

int treeSum2(TNode* root) {
    if (!root) return 0;
    return treeSum2(root->left) + treeSum2(root->left) + root->data;
}

int main() {
    TNode* tree = new TNode(1);
    tree->left = new TNode(2);
    tree->right = new TNode(3);
    tree->left->left = new TNode(4);
    tree->right->right = new TNode(5);

    TNode* tree2 = new TNode(-1);
    tree2->left = new TNode(-2);
    tree2->right = new TNode(-3);
    tree2->left->left = new TNode(-4);
    tree2->left->right = new TNode(-5);
}
