#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mastermind.h"
#include "score.h"

void generateRandomCode(char code[]) {
    const char couleursPossibles[5] = {'R', 'V', 'B', 'J', 'O'};
    int couleursUtilisees[5] = {0, 0, 0, 0, 0};
    int taille = 0;
    while(taille != 4) {
        int randomID = rand() % 5;
        if(couleursUtilisees[randomID] == 0) { //On prend la couleur que si elle n'a pas été choisie
            code[taille] = couleursPossibles[randomID];
            taille++;
            couleursUtilisees[randomID] = 1;
        }
    }
}

//Vérification de l'entree saisie
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
    hightScore highScoresList[TAILLE_LISTE];
    FILE* pt_fichier = loadGameHighScores("datas/MastermindHighScore.sav", highScoresList);
    if(!pt_fichier) {
        return;
    }
    srand(time(NULL));

    char code[4]; //Code a trouver
    char saisie[4] = {0}; //Saisie de l'utilisateur
    const int MAX_TENTATIVES = 10;
    int tentatives = 0, nbBonnesCouleursBienPlacees = 0, nbBonnesCouleursMalPlacees = 0;

    //Génération du code aléatoire
    generateRandomCode(code);

    printf("Mastermind : Trouvez la bonne combinaison de 4 couleurs differentes parmi (R, V, B, J, O)\n");
    //printf("%c%c%c%c\n", code[0], code[1], code[2], code[3]);

    while(tentatives < MAX_TENTATIVES && nbBonnesCouleursBienPlacees < 4) { //Boucle du jeu
        tentatives++;
        printf("Tentative %d/%d > ", tentatives, MAX_TENTATIVES);

        fflush(stdin); //On vide l'entrée utilisateur
        scanf("%c%c%c%c", saisie, saisie + 1, saisie + 2, saisie + 3);


        if(!isInputValid(saisie)) { //Si l'entrée est invalide
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
        hightScore hScore;
        hScore.score = MAX_TENTATIVES - tentatives + 1;
        printf("C'est la bonne combinaison ! Vous marquez %ld points\nEntrez votre nom pour le high score : ", hScore.score);
        scanf("%s", hScore.nom);
        fflush(stdin);
        addHightScore(highScoresList, hScore);
        saveHightScore(pt_fichier, highScoresList);
    }
    else {
        printf("Nombre de tentatives depassees !\n");
    }
    fclose(pt_fichier);
}
