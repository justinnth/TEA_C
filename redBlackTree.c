//
// Created by Justin North on 2018-12-11.
//

#include "redBlackTree.h"

ARN create(void* item){
    if(item) {
        ARN temp = (Node*) malloc(sizeof(Node*));
        if(temp){
            temp->item = item;
            temp->color = BLACK;
            temp->left = NULL;
            temp->right = NULL;
            temp->parent = NULL;
        }
        else{
            free(temp);
            temp = NULL;
        }
        return temp;
    }
    return NULL;
}

ARN parent(ARN tree){
    return tree->parent; // NULL pour la racine
}

ARN grandparent(ARN tree){
    ARN p = parent(tree);
    if(p == NULL)
        return NULL; // Pas de parents donc pas de grand-parent
    return parent(p); // Nul si le parent est la racine
}

ARN sibling(ARN tree){
    ARN p = parent(tree);
    if(p == NULL)
        return NULL;
    if(tree == p->left)
        return p->right;
    else
        return p->left;
}

ARN uncle(ARN tree){
    ARN p = parent(tree);
    ARN gp = grandparent(tree);
    if(gp == NULL)
        return NULL; // Pas de grandparent donc pas d'oncle
    return sibling(p);
}

void rotate_left(ARN tree){
    ARN newTree = tree->right;
    ARN p = parent(tree);

    tree->right = newTree->left;
    newTree->left = tree;
    tree->parent = newTree;

    if(tree->right != NULL)
        tree->right->parent = tree;
    if(p != NULL){
        if(tree == p->left)
            p->left = newTree;
        else if(tree == p->right)
            p->right = newTree;
    }
    newTree->parent = p;
}

void rotate_right(ARN tree){
    ARN newTree = tree->left;
    ARN p = parent(tree);

    tree->left = newTree->right;
    newTree->right = tree;
    tree->parent = newTree;

    if(tree->left != NULL)
        tree->left->parent = tree;
    if(p != NULL){
        if(tree == p->left)
            p->left = newTree;
        else if(tree == p->right)
            p->right = newTree;
    }
    newTree->parent = p;
}

ARN insert(ARN racine, ARN ajout){
    // On insère le nouveau noeud dans l'arbre
    insert_recurse(racine, ajout);

    // On répare l'arbre si des propriétés des arbres rouge-noir ont été violées
    insert_repair_tree(ajout);

    racine = ajout;
    while (parent(racine) != NULL)
        racine = parent(racine);
    return racine;
}

void insert_recurse(ARN racine, ARN ajout){
    if(racine != NULL && ajout->item < racine->item){
        if(racine->left != NULL){
            insert_recurse(racine->left, ajout);
            return;
        }
        else
            racine->left = ajout;
    }
    else if(racine != NULL){
        if(racine->right != NULL){
            insert_recurse(racine->right, ajout);
            return;
        }
        else
            racine->right = ajout;
    }

    ajout->parent = racine;
    ajout->left = NULL;
    ajout->right = NULL;
    ajout->color = RED;
}

void insert_repair_tree(ARN ajout){
    if(parent(ajout) == NULL)
        insert_case1(ajout);
    else if(parent(ajout)->color == BLACK)
        insert_case2(ajout);
    else if(uncle(ajout)->color == RED)
        insert_case3(ajout);
    else
        insert_case4(ajout);

}

void insert_case1(ARN tree){
    if(parent(tree) == NULL)
        tree->color = BLACK;
}

void insert_case2(ARN tree){

}

void insert_case3(ARN tree){
    parent(tree)->color = BLACK;
    uncle(tree)->color = BLACK;
    grandparent(tree)->color = RED;
    insert_repair_tree(grandparent(tree));
}

void insert_case4(ARN tree){
    ARN p = parent(tree);
    ARN g = grandparent(tree);

    if(tree == g->left->right){
        rotate_left(p);
        tree = tree->left;
    } else if(tree == g->right->left){
        rotate_right(p);
        tree = tree->right;
    }

    insert_case5(tree);
}

void insert_case5(ARN tree){
    ARN p = parent(tree);
    ARN g = grandparent(tree);

    if(tree == p->left)
        rotate_right(g);
    else
        rotate_left(g);

    p->color = BLACK;
    g->color = RED;
}
