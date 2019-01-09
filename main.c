#include <stdio.h>
#include "redBlackTree.h"
#include <time.h>

void affiche(ARN tree){
    if(tree){
        printf("%d - %d | ", tree->item, tree->color);
        affiche(tree->left);
        affiche(tree->right);
    }
}

int menu(){
    int choixMenu;

    printf("\n\n--------------\n");
    printf("---- Menu ----\n");
    printf("--------------\n");

    printf("1. Créer arbre\n");
    printf("2. Insérer valeur dans arbre\n");
    printf("3. Suppression\n");
    printf("4. Recherche\n");
    printf("5. Afficher arbre\n");
    printf("6. Quitter\n");

    scanf("%d", &choixMenu);

    return choixMenu;
}

int main() {
    ARN racine;
    ARN ajout;

    bool inMenu = true;
    int item = 0;

    srand(time(NULL));

    while(inMenu){
        item = rand() % 5000;

        switch (menu()) {
            case 1:
                racine = create(item);
                break;
            case 2:
                ajout = create(item);

                insert(racine, ajout);
                break;
            case 3:
                printf("Suppression\n");
                break;
            case 4:
                printf("Recherche\n");
                break;
            case 5:
                affiche(racine);
                break;
            case 6:
                inMenu = false;
                break;
            default:
                printf("Retour\n");
        }
    }

    return 0;
}