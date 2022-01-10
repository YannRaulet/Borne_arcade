#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mastermind.h"

void generateRandomCode(char code[]) {
    const char couleursPossibles[5] = {'R', 'V', 'B', 'J', 'O'};
    int couleursUtilisees[5] = {0, 0, 0, 0, 0};
    int taille = 0;
    while(taille != 4) {
        int randomID = rand() % 5;
        if(couleursUtilisees[randomID] == 0) { //On prend la couleur que si elle n'a pas �t� choisie
            code[taille] = couleursPossibles[randomID];
            taille++;
            couleursUtilisees[randomID] = 1;
        }
    }
}

//V�rification de l'entree saisie
int isInputValid(const char saisie[]) {
    for(int i = 0; i < 4; i++) {
        char couleur = saisie[i];
        if (couleur != 'R' && couleur != 'V' && couleur != 'B' && couleur != 'J' && couleur != 'O') {
            return 0;
        }
    }
    return 1;
}

void checkCouleurs(const char code[], const char saisie[], int *nbBonnesCouleursMalPlacees, int *nbBonnesCouleursBienPlacees) {
    *nbBonnesCouleursBienPlacees = 0;
    *nbBonnesCouleursMalPlacees = 0;
    for(int i = 0; i < 4; i++) { //Comparaison du code
        if(saisie[i] == code[i]) { //On cherche les couleurs bien placees
            (*nbBonnesCouleursBienPlacees)++;
        }
        else {
            for(int j = 0; j < 4; j++) { //On cherche les couleurs mal placees
                if(saisie[i] == code[j] && saisie[j] != code[j]) {
                    (*nbBonnesCouleursMalPlacees)++;
                }
            }
        }
    }

}

void playMastermind()
{
    printf("TP8 : Tableaux\n");
    srand(time(NULL));

    char code[4]; //Code a trouver
    char saisie[4] = {0}; //Saisie de l'utilisateur
    const int MAX_TENTATIVES = 3;
    int tentatives = 0, nbBonnesCouleursBienPlacees = 0, nbBonnesCouleursMalPlacees = 0;

    //G�n�ration du code al�atoire
    generateRandomCode(code);

    printf("Mastermind : Trouvez la bonne combinaison de 4 couleurs differentes parmi (R, V, B, J, O)\n");
    //printf("%c%c%c%c\n", code[0], code[1], code[2], code[3]);

    while(tentatives < MAX_TENTATIVES && nbBonnesCouleursBienPlacees < 4) { //Boucle du jeu
        tentatives++;
        printf("Tentative %d/%d > ", tentatives, MAX_TENTATIVES);

        fflush(stdin); //On vide l'entr�e utilisateur
        scanf("%c%c%c%c", saisie, saisie + 1, saisie + 2, saisie + 3);


        if(!isInputValid(saisie)) { //Si l'entr�e est invalide
            printf("L'entree est invalide. Les couleurs sont R, V, B, J, O\n");
            tentatives--; //On ne compte pas cette tentative
            continue;
        }

        checkCouleurs(code, saisie, &nbBonnesCouleursMalPlacees, &nbBonnesCouleursBienPlacees);
        printf("Bonnes couleurs mal placees : %d\n", nbBonnesCouleursMalPlacees);
        printf("Bonnes couleurs bien placees : %d\n", nbBonnesCouleursBienPlacees);
    }

    //Fin du jeu
    if(nbBonnesCouleursBienPlacees == 4) {
        printf("C'est la bonne combinaison !\n");
    }
    else {
        printf("Nombre de tentatives depassees !\n");
    }
}
