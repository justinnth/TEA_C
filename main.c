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
    printf("6. Libération\n");
    printf("7. Quitter\n");

    scanf("%d", &choixMenu);

    return choixMenu;
}

int main() {
    float temps;
    clock_t t1, t2;

    ARN racine;
    ARN ajout;

    bool inMenu = true;

    int item = 0;

    int nbNoeuds;
    int idNoeud;

    srand(time(NULL));

    while(inMenu){
        switch (menu()) {
            case 1:
                item = rand() % 5000;
                racine = create(item);
                break;
            case 2:
                printf("Combien de noeuds désirez vous ?");
                scanf("%d", &nbNoeuds);

                t1 = clock();

                for (int i = 1; i < nbNoeuds; i++) {
                    item = rand() % 5000;

                    ajout = create(item);
                    racine = insert(racine, ajout);
                }

                t2 = clock();
                temps = (float)(t2-t1)/CLOCKS_PER_SEC;
                printf("temps = %f\n", temps);

                break;
            case 3:
                printf("Suppression\n");
                break;
            case 4:
                printf("Quel noeud cherchez vous?\n");
                scanf("%d", &idNoeud);

                ARN trouve = recherche(racine, idNoeud);
                affiche(trouve);
                break;
            case 5:
                affiche(racine);
                break;
            case 6:
                printf("Libération de l'espace mémoire de l'arbre\n");
                liberer(racine);
                break;
            case 7:
                inMenu = false;
                printf("Fermeture du programme");
                break;
            default:
                printf("Retour\n");
        }
    }
    return 0;
}