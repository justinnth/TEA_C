//
// Created by Justin North on 2018-12-11.
//

#ifndef TEA_REDBLACKTREE_H
#define TEA_REDBLACKTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

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

void replace_node(ARN n, ARN enfant);
void delete_one_child(ARN tree);
void delete_case1(ARN tree);
void delete_case2(ARN tree);
void delete_case3(ARN tree);
void delete_case4(ARN tree);
void delete_case5(ARN tree);
void delete_case6(ARN tree);

ARN recherche(ARN racine, int item);

void liberer(ARN tree);

#endif //TEA_REDBLACKTREE_H
