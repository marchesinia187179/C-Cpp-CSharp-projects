#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
}; typedef struct node node;

// Creates a new node with the specified data and
// pays attention to memory allocation (checking for malloc failures).
node *createNode(int data) {
    node *newNode = malloc(sizeof(node));
    if(newNode == NULL) {
        fprintf(stderr, "Error in creating new node: malloc failed\n");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Recursively traverses the tree to find the correct insertion point
// according to BST rules, and creates a new node there.
void addNode(node **currentNode, int data) {
    if (*currentNode == NULL) {
        *currentNode = createNode(data);
        return;
    }

    if (data < (*currentNode)->data) {
        addNode(&(*currentNode)->left, data);
    } else {
        addNode(&(*currentNode)->right, data);
    }
}

// Prints the entire tree using an In-order traversal,
// which outputs the node data in sorted ascending order.
void printTree(const node *node) {
    if (node == NULL) return;
    printTree(node->left);
    printf("%d ", node->data);
    printTree(node->right);
}

// Recursively deallocates the entire tree using a Post-order traversal.
// Frees child nodes (left and right) before freeing the parent node.
void freeTree(node *node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main(void) {
    node *root = createNode(10);
    addNode(&root, 20);
    addNode(&root, 40);
    addNode(&root, 50);
    addNode(&root, -30);

    printTree(root);

    freeTree(root);
    return 0;
}