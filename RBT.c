#include "RBT.h"

// get blackheight of a red black tree
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
    struct rbt *temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    temp->color = parent->color;
    parent->color = RED;
    return temp;
}
// rotate right of a red black tree with a given parent node
struct rbt *rot_right(struct rbt *parent){
    struct rbt *temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    temp->color = parent->color;
    parent->color = RED;
    return temp;
}

//insertnode in a red black tree and balance the tree
struct rbt *insertNode(struct rbt *parent, int value){
    if (parent == NULL) {
        struct rbt *new_node = malloc(sizeof(struct rbt));
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->color = BLACK;
        return new_node;
    }
    if (value < parent->value) {
        if (parent->left == NULL) {
            struct rbt *new_node = malloc(sizeof(struct rbt));
            new_node->value = value;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->color = RED;
            parent->left = new_node;
        }
        else {
            parent->left = insertNode(parent->left, value);
        }
    } else if (value > parent->value) {
        if (parent->right == NULL) {
            struct rbt *new_node = malloc(sizeof(struct rbt));
            new_node->value = value;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->color = RED;
            parent->right = new_node;
        }
        else {
            parent->right = insertNode(parent->right, value);
        }
    } else {
        return parent;

    }
    // balance the tree 
    if (parent->color == RED) {

        if (parent->left != NULL && parent->left->color == RED) {
            if ( parent->left->left != NULL && parent->left->left->color == RED) {
                parent = rot_right(parent);
            } else if (parent->left->right != NULL && parent->left->right->color == RED) {
                parent->left = rot_left(parent->left);
                parent = rot_right(parent);
            }
        }
        else if (parent->right != NULL && parent->right->color == RED) {
            if (parent->right->right != NULL && parent->right->right->color == RED) {
                parent = rot_left(parent);
            } else if (parent->right->left != NULL && parent->right->left->color == RED) {
                parent->right = rot_right(parent->right);
                parent = rot_left(parent);
            }
        }
    }
    return parent;
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

