#ifndef RBT_H
#define RBT_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

/*
struct to_print
{
    char node_name;      // value + color
    struct to_print *tp; // fils
};
*/
// enum for color of a node
enum color_rbt
{
    RED,
    BLACK
};

// red black tree node structure
struct rbt
{
    int value;
    struct rbt *parent;
    struct rbt *left;
    struct rbt *right;
    enum color_rbt color;
};

// create a red black tree node
struct rbt *createNode(int value);

// rotate left from two given pointers root and (parent or grandparent)
void rot_left(struct rbt **root, struct rbt **x);

// rotate right from two given pointers root and (parent or grandparent)
void rot_right(struct rbt **root, struct rbt **x);

// fix the red black tree after inserting a node
void insertFixup(struct rbt **root, struct rbt **z);

// normal insert a node to red black tree
struct rbt *insertNode(struct rbt *root, int value);

// print function to visualize the tree
void printTree(struct rbt *root);

#endif