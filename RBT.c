#include "RBT.h"

// Create a red black tree
struct rbt *createNode(int value) {
  struct rbt *newnode;
  newnode = (struct rbt *)malloc(sizeof(struct rbt));
  newnode->value = value;
  newnode->color = RED;
  newnode->left = newnode->right = NULL;
  return newnode;
}

// Get blackheight of a red black tree
int getBlackHeight(struct rbt *parent) {
    if (parent == NULL) {
        return 0;
    }
    if (parent->color == BLACK) {
        return 1 + getBlackHeight(parent->left) + getBlackHeight(parent->right);
    } else {
        return getBlackHeight(parent->left);
    }
}
// rotate left of a red black tree with a given parent node
struct rbt *rot_left(struct rbt *parent){
    struct rbt *resNode = parent->right;
    struct rbt *temp = resNode->left;
    resNode->left = parent;
    parent->right = temp;
    parent->father = resNode;
    if (temp != NULL){
        temp->father = parent;
    }
    return resNode;
}
// rotate right of a red black tree with a given parent node
struct rbt *rot_right(struct rbt *parent){
    struct rbt *resNode = parent->left;
    struct rbt *temp = resNode->right;
    resNode->right = parent;
    parent->left = temp;
    parent->father = resNode;
    if (temp != NULL){
        temp->father = parent;
    }
    return resNode;
}
// insert node into a red black tree
struct rbt *insertNode(struct rbt *root, int value){
    if (root  == NULL){
        return createNode(value);
    }
    if (root->value < value){
        root->right = insertNode(root->right, value);
    } else {
        root->left = insertNode(root->left, value);
    }
    // case 1 : root is the root of the tree
    if (root->father == NULL){
        root->color = BLACK;
    }
    // case 2 : inserted node uncle is red and inserted node is red (just recolor)
    if (root->color == RED && root->father->father != NULL && root->father != root->father->father->left && root->father->father->left->color == RED){
        root->father->father->color = RED;
        root->father->father->left->color = BLACK;
        root->father->father->right->color = BLACK;
    }
    // case 3 : inserted node uncle is black and inserted node is red and inserted node is left child of its father (rotations)
    if (root->color == RED && root->father->father != NULL && root->father != root->father->father->left && root->father->father->left->color == BLACK){
        if (root == root->father->left){
            root->father = rot_right(root->father);
        } else {
            root->father->color = BLACK;
            root->father->father->color = RED;
            root->father->father = rot_left(root->father->father);
        }
    }
    //case 3 reversed : inserted node uncle is black and inserted node is red and inserted node is right child of its father (rotations)
    if (root->color == RED && root->father->father != NULL && root->father != root->father->father->right && root->father->father->right->color == BLACK){
        if (root == root->father->right){
            root->father = rot_left(root->father);
        } else {
            root->father->color = BLACK;
            root->father->father->color = RED;
            root->father->father = rot_right(root->father->father);
        }
    }
    //case 4 : 
    return root;
}

void printTree(struct rbt *root){
    printf("%d ", root->value);
    if (root->color == RED) {
        printf("R");
    } else {
        printf("B");
    }
    printf("\n");
    if (root->left != NULL) {
        printTree(root->left);
    }
    if (root->right != NULL) {
        printTree(root->right);
    }
}


int main() {
    // test insertNode
    struct rbt *root = NULL;
    root = insertNode(root, 13);
    root = insertNode(root, 8);
    root = insertNode(root, 1);
    root = insertNode(root, 11);
    root = insertNode(root, 6);
    root = insertNode(root, 17);
    root = insertNode(root, 15);
    root = insertNode(root, 25);
    root = insertNode(root, 22);
    root = insertNode(root, 27);

    printTree(root);

    return 0;
}

