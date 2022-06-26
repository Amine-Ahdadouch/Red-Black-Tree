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

enum color_rbt
{
    RED,
    BLACK
};

struct rbt
{
    int value;
    struct rbt *father;
    struct rbt *left;
    struct rbt *right;
    enum color_rbt color;
};

// Create a red-black tree
struct rbt *createNode(int value);
int getBlackHeight(struct rbt *parent);
struct rbt *rot_left(struct rbt *parent);
struct rbt *rot_right(struct rbt *parent);
struct rbt *insertNode(struct rbt *root, int value);

#endif