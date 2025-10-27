/*
Program: Invert Binary Tree
Problem Statement:
Given the root of a binary tree, invert the tree — that is, swap the left and right
subtrees of every node. The result should be a mirror image of the original tree.

Example:
Input Tree:             Output Tree:
       4                      4
      / \                    / \
     2   7                  7   2
    / \ / \                / \ / \
   1  3 6  9              9  6 3  1

Time Complexity: O(n)  (each node visited once)
Space Complexity: O(h) (due to recursion stack, where h = height of tree)
*/

#include <stdio.h>
#include <stdlib.h>

// Structure definition for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to invert (mirror) the binary tree
struct Node* invertTree(struct Node* root) {
    if (root == NULL)
        return NULL;

    // Swap the left and right children
    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // Recursively invert the left and right subtrees
    invertTree(root->left);
    invertTree(root->right);

    return root;
}

// Inorder traversal to display the tree
void inorder(struct Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Driver code to demonstrate inversion
int main() {
    /*
        Constructing the following tree:
                 4
                / \
               2   7
              / \ / \
             1  3 6  9
    */
    struct Node* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(7);
    root->left->left = createNode(1);
    root->left->right = createNode(3);
    root->right->left = createNode(6);
    root->right->right = createNode(9);

    printf("Inorder traversal before inversion: ");
    inorder(root);
    printf("\n");

    invertTree(root);

    printf("Inorder traversal after inversion:  ");
    inorder(root);
    printf("\n");

    return 0;
}

/*
Example Output:

Inorder traversal before inversion: 1 2 3 4 6 7 9 
Inorder traversal after inversion:  9 7 6 4 3 2 1
*/
