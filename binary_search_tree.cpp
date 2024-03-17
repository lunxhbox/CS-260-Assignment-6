#include <iostream>
#include <vector>

using namespace std;

// Node structure for BST
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BST {
private:
    Node* root;

    // Helper function for adding a value recursively
    void addRecursive(Node*& node, int value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value <= node->value) {
            addRecursive(node->left, value);
        } else {
            addRecursive(node->right, value);
        }
    }

    // Helper function for finding the minimum value node in a subtree
    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    // Helper function for removing a value recursively
    Node* removeRecursive(Node*& node, int value) {
        if (!node) {
            return node;
        }
        if (value < node->value) {
            node->left = removeRecursive(node->left, value);
        } else if (value > node->value) {
            node->right = removeRecursive(node->right, value);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->value = temp->value;
            node->right = removeRecursive(node->right, temp->value);
        }
        return node;
    }

    // Helper function for in-order traversal recursively
    void inOrderTraversalRecursive(Node* node, vector<int>& result) {
        if (!node) {
            return;
        }
        inOrderTraversalRecursive(node->left, result);
        result.push_back(node->value);
        inOrderTraversalRecursive(node->right, result);
    }

public:
    BST() : root(nullptr) {}

    // Public function to add a value to the BST
    void add(int value) {
        addRecursive(root, value);
    }

    // Public function to remove a value from the BST
    void remove(int value) {
        root = removeRecursive(root, value);
    }

    // Public function for in-order traversal
    vector<int> inOrderTraversal() {
        vector<int> result;
        inOrderTraversalRecursive(root, result);
        return result;
    }
};

// Test function for BST
void testBST() {
    BST bst;

    // Test Add Function
    bst.add(5);
    bst.add(3);
    bst.add(7);
    if (bst.inOrderTraversal() != vector<int>{3, 5, 7}) {
        cout << "Test Add Function failed." << endl;
        return;
    }

    // Test Remove Function
    bst.remove(3);
    if (bst.inOrderTraversal() != vector<int>{5, 7}) {
        cout << "Test Remove Function failed." << endl;
        return;
    }

    // Test In-Order Traversal
    bst.add(4);
    bst.add(2);
    bst.add(6);
    if (bst.inOrderTraversal() != vector<int>{2, 4, 5, 6, 7}) {
        cout << "Test In-Order Traversal failed." << endl;
        return;
    }

    cout << "All tests passed successfully!" << endl;
}

int main() {
    testBST();
    return 0;
}
