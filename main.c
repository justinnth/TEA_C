#include <stdio.h>
#include "redBlackTree.h"

void affiche(ARN tree){
    if(tree){
        printf("%d - %d | ", tree->item, tree->color);
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
    ARN ajout2 = create(35);
    ARN ajout3 = create(20);
    ARN ajout4 = create(22);
    /*ARN ajout5 = create(10);
    ARN ajout6 = create(22);
    ARN ajout7 = create(30);*/

    insert(racine, ajout);
    insert(racine, ajout2);
    insert(racine, ajout3);
    insert(racine, ajout4);
    /*insert(racine, ajout5);
    insert(racine, ajout6);
    insert(racine, ajout7);*/

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