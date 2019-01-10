//
// Created by Justin North on 2018-12-11.
//

#include "redBlackTree.h"
#include <assert.h>

/**
 * Création d'un arbre rouge-noir
 * @param item
 * @return
 */
ARN create(int item){
    if(item) {
        ARN temp = (Node*) malloc(sizeof(Node*) * 3 + sizeof(int));
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
        printf("\nCréation d'un noeud\nValeur : %d - Couleur : BLACK", item);
        return temp;
    }
    return NULL;
}

/**
 * Retourne le parent d'un arbre
 * @param tree
 * @return
 */
ARN parent(ARN tree){
    return tree->parent; // NULL pour la racine
}

/**
 * Retourne le grandparent d'un arbre
 * @param tree
 * @return
 */
ARN grandparent(ARN tree){
    ARN p = parent(tree);
    if(p == NULL)
        return NULL; // Pas de parents donc pas de grand-parent
    return parent(p); // Nul si le parent est la racine
}

/**
 * Retourne le frere d'un arbre
 * @param tree
 * @return
 */
ARN sibling(ARN tree){
    ARN p = parent(tree);
    if(p == NULL)
        return NULL;
    if(tree == p->left)
        return p->right;
    else
        return p->left;
}

/**
 * Retourne l'oncle d'un arbre
 * @param tree
 * @return
 */
ARN uncle(ARN tree){
    ARN p = parent(tree);
    ARN gp = grandparent(tree);
    if(gp == NULL)
        return NULL; // Pas de grandparent donc pas d'oncle
    return sibling(p);
}

/**
 * Rotation à gauche
 * @param tree
 */
void rotate_left(ARN tree){
    ARN newTree = tree->right;
    ARN p = parent(tree);

    assert(newTree != NULL);

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

    printf("\nRotation à gauche");
}

/**
 * Rotation à droite
 * @param tree
 */
void rotate_right(ARN tree){
    ARN newTree = tree->left;
    ARN p = parent(tree);

    assert(newTree != NULL);

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
    printf("\nRotation à droite");
}

/**
 * Insertion d'un noeud dans l'arbre
 * @param racine
 * @param ajout
 * @return
 */
ARN insert(ARN racine, ARN ajout){
    // On insère le nouveau noeud dans l'arbre
    insert_recurse(racine, ajout);

    // On répare l'arbre si des propriétés des arbres rouge-noir ont été violées
    insert_repair_tree(ajout);

    racine = ajout;
    while (parent(racine) != NULL)
        racine = parent(racine);

    printf("\nInsertion dans l'arbre\n");
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
    else if(uncle(ajout) != NULL && uncle(ajout)->color == RED)
        insert_case3(ajout);
    else
        insert_case4(ajout);

}

void insert_case1(ARN tree){
    if(parent(tree) == NULL)
        tree->color = BLACK;
}

void insert_case2(ARN tree){ }

void insert_case3(ARN tree){
    parent(tree)->color = BLACK;
    uncle(tree)->color = BLACK;
    grandparent(tree)->color = RED;
    insert_repair_tree(grandparent(tree));
}

void insert_case4(ARN tree){
    ARN p = parent(tree);
    ARN g = grandparent(tree);

    if(g->left != NULL && tree == g->left->right){
        rotate_left(p);
        tree = tree->left;
    } else if(g->right != NULL && tree == g->right->left){
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

void replace_node(ARN racine, ARN fils){
    fils->parent = racine->parent;
    if(racine == racine->parent->left)
        racine->parent->left = fils;
    else
        racine->parent->right = fils;
}

void delete_one_child(ARN tree){
    ARN enfant;
    if(tree->right == NULL)
        enfant = tree->left;
    enfant = tree->right;

    replace_node(tree, enfant);

    if (tree->color == BLACK){
        if (enfant->color == RED)
            enfant->color = BLACK;
        else
            delete_case1(enfant);
    }
    free(tree);
}

void delete_case1(ARN tree){
    if(tree->parent != NULL)
        delete_case2(tree);
}

void delete_case2(ARN tree){
    ARN s = sibling(tree);

    if (s->color == RED){
        tree->parent->color = RED;
        s->color = BLACK;
        if (tree == tree->parent->left)
            rotate_left(tree->parent);
        else
            rotate_right(tree->parent);
    }

    delete_case3(tree);
}

void delete_case3(ARN tree){
    ARN s = sibling(tree);

    if ((tree->parent->color == BLACK) && (s->color == BLACK) && (s->left->color == BLACK) && (s->right->color == BLACK)){
        s->color = RED;
        delete_case1(tree->parent);
    }
    else
        delete_case4(tree);
}

void delete_case4(ARN tree){
    ARN s = sibling(tree);

    if ((tree->parent->color == RED) && (s->color == BLACK) && (s->left->color == BLACK) && (s->right->color == BLACK)){
        s->color = RED;
        tree->parent->color = BLACK;
    }
    else
        delete_case5(tree);
}

void delete_case5(ARN tree){
    ARN s = sibling(tree);

    if (s->color == BLACK){
        if((tree == tree->parent->left) && (s->right->color == BLACK) && (s->left->color == RED)){
            s->color = RED;
            s->left->color = BLACK;
            rotate_right(s);
        }
        else if((tree = tree->parent->right) && (s->left->color == BLACK) && (s->right->color == RED)){
            s->color = RED;
            s->right->color = BLACK;
            rotate_left(s);
        }
    }
    delete_case6(tree);
}

void delete_case6(ARN tree){
    ARN s = sibling(tree);

    s->color = tree->parent->color;
    tree->parent->color = BLACK;

    if(tree == tree->parent->left){
        s->right->color = BLACK;
        rotate_left(tree->parent);
    }
    else{
        s->left->color = BLACK;
        rotate_right(tree->parent);
    }
}

ARN recherche(ARN racine, int item){
    if(racine == NULL)
        return NULL;

    ARN tmp = racine;
    while (tmp != NULL){
        if(item < tmp->item){
            if (tmp->left == NULL)
                break;
            else
                tmp = tmp->left;
        }
        else if(item == tmp->item)
            break;
        else{
            if(tmp->right == NULL)
                break;
            else
                tmp = tmp->right;
        }
    }
    return tmp;
}

/**
 * Libération de l'arbre
 * @param tree
 */
void liberer(ARN tree){
    if(tree){
        if(tree->right){
            liberer(tree->right);
        }
        if(tree->left){
            liberer(tree->left);
        }

        tree->item = 0;
        tree->parent = NULL;
        tree->left = NULL;
        tree->right = NULL;
        tree->color = BLACK;

        tree = NULL;
        free(tree);
    }
}
