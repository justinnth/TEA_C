#include <stdio.h>
#include "redBlackTree.h"

void affiche(ARN tree){
    if(tree){
        printf("%d - %d | ", (int) tree->item, tree->color);
        affiche(tree->left);
        affiche(tree->right);
    }
}

int menu(){
    int choixMenu;

    printf("--------------\n");
    printf("---- Menu ----\n");
    printf("--------------\n");

    printf("1. Insertion\n");
    printf("2. Suppression\n");
    printf("3. Recherche\n");

    scanf("%d", &choixMenu);

    return choixMenu;
}

int main() {
    ARN racine = create(25);
    ARN ajout = create(15);

    insert(racine, ajout);

    switch (menu()) {
        case 1:
            affiche(racine);
            break;
        case 2:
            printf("Suppression\n");
            break;
        case 3:
            printf("Recherche\n");
            break;
        default:
            printf("Retour\n");
    }

    return 0;
}