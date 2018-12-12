//
// Created by Justin North on 2018-12-11.
//

#ifndef TEA_REDBLACKTREE_H
#define TEA_REDBLACKTREE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    enum {BLACK, RED} color;
    int item;
    struct node *left, *right, *parent;
}Node;

typedef Node *pt_node;

typedef pt_node ARN;

// Méthodes
ARN create(int item);

ARN parent(ARN tree);
ARN grandparent(ARN tree);
ARN sibling(ARN tree);
ARN uncle(ARN tree);

ARN insert(ARN racine, ARN ajout);
void insert_recurse(ARN racine, ARN ajout);
void insert_repair_tree(ARN ajout);

void insert_case1(ARN tree);
void insert_case2(ARN tree);
void insert_case3(ARN tree);
void insert_case4(ARN tree);
void insert_case5(ARN tree);

void rotate_left(ARN tree);
void rotate_right(ARN tree);

#endif //TEA_REDBLACKTREE_H
