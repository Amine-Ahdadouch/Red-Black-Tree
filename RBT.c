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

// rotate left from two given pointers root and (parent or grandparent) depand on the case
void rot_left(struct rbt **root, struct rbt **x)
{
    struct rbt* y = (*x)->right;
    (*x)->right = y->left;

    if(y->left!=NULL)
        y->left->parent = *x;

    y->parent = (*x)->parent;

    if((*x)->parent == NULL)
        *root = y;

    else if(*x == (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->left = *x;

    (*x)->parent = y;

}
// rotate right from two given pointers root and (parent or grandparent) depand on the case
void rot_right(struct rbt **root, struct rbt **x)
{
    struct rbt* y = (*x)->left;
    (*x)->left = y->right;

    if(y->right!=NULL)
        y->right->parent = *x;

    y->parent = (*x)->parent;

    if((*x)->parent==NULL)
        *root = y;

    else if((*x)== (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->right = *x;
    (*x)->parent = y;

}

// iterate through the red black red and fix it either by coloring or rotating nodes using pointers
void insertFixup(struct rbt **root, struct rbt **z){
    struct rbt *grandparent = NULL;
    struct rbt *parentpt = NULL;

    while(((*z) != *root) && ((*z)->color != BLACK) && ((*z)->parent->color == RED))
    {
        // getting parent and grandparent
        parentpt = (*z)->parent;
        grandparent = (*z)->parent->parent;

        // z parent is a left child of grandparent
        if(parentpt == grandparent->left)
        {
            struct rbt* uncle = grandparent->right;

            // case 1.1: uncle is red juste recolor
            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            }

            // uncle is black
            else
            {
                // z uncle is black and z is a right child of parent rotate left the parent
                if((*z) == parentpt->right)
                {
                    rot_left(root, &parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }
                // z s uncle is black and z is a left child of parent rotate right the grandparent
                rot_right(root, &grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }

        // do the same thing but with the opposite case 
        else
        {
            struct rbt* uncle = grandparent->left;

            if(uncle!=NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                (*z) = grandparent;
            }

            else
            {
                if((*z) == parentpt->left)
                {
                    rot_right(root, &parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                rot_left(root, &grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }
    }
    // root color is black 
    (*root)->color = BLACK;

}
// normal insert function, insert a node to the tree and use fix function to fix the tree
struct rbt *insertNode(struct rbt *root, int value){
    struct rbt *z = createNode(value);
    struct rbt *y = NULL;
    struct rbt *x = root;
    while(x != NULL)
    {
        y = x;
        if(z->value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if(y==NULL)
        root = z;
    else if(z->value < y->value)
        y->left = z;
    else
        y->right = z;
    insertFixup(&root, &z);
    return root;
}

// print the tree and colors from a given root
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