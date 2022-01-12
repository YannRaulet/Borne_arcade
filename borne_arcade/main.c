#include <stdio.h>
#include <stdlib.h>
#include "score.h"
#include "pendu.h"
#include "mastermind.h"
#include "juste_prix.h"
#include "papier_ciseaux.h"

void printMenu() {
    printf("\tBienvenue sur la borne d'arcade !\n\n");
    printf("Voici la liste des jeux : \n");
    printf("1) Pierre-Feuille-Ciseaux\n");
    printf("2) Juste Prix\n");
    printf("3) Mastermind\n");
    printf("4) Pendu\n");
    printf("5) Score\n");
    printf("6) Quitter\n\n");
    printf("Choississez a quel jeu vous allez jouer (Entrez un nombre entre 1 et 5) : ");
}

void getHighScores() {
    int choix = 0;
    hightScore highScoresList[TAILLE_LISTE];
    FILE* pt_fichier = NULL;
    printf("Liste des jeux : \n");
    printf("1) Pierre-Feuille-Ciseaux\n");
    printf("2) Juste Prix\n");
    printf("3) Mastermind\n");
    printf("4) Pendu\n");
    printf("Pour quel jeu voulez-vous voir le high score ? ");
    scanf("%d", &choix);
    switch(choix) {
        case 1:
            pt_fichier = loadGameHighScores("datas/PapierCiseauxHighScore.sav", highScoresList);
            break;
        case 2:
            pt_fichier = loadGameHighScores("datas/JustePrixHighScore.sav", highScoresList);
            break;
        case 3:
            pt_fichier = loadGameHighScores("datas/MastermindHighScore.sav", highScoresList);
            break;
        case 4:
            pt_fichier = loadGameHighScores("datas/PenduHighScore.sav", highScoresList);
            break;
        default:
            printf("Selection invalide\n");
            return;
    }
    if(!pt_fichier) {
        return;
    }
    afficherHightScore(highScoresList);

    fclose(pt_fichier);

}



int main()
{

    int quit = 0, choice = 0;

    while(quit == 0) {
        printMenu();
        scanf("%d", &choice);
        fflush(stdin);
        printf("\n\n\n");
        switch(choice) {
        case 1:
            playPapierCiseaux();
            printf("\n\n\n");
            break;
        case 2:
            playJustePrix();
            printf("\n\n\n");
            break;
        case 3:
            playMastermind();
            printf("\n\n\n");
            break;
        case 4:
            playPendu();
            printf("\n\n\n");
            break;
        case 5:
            getHighScores();
            printf("\n\n\n");
            break;
        case 6:
            quit = 1;
            break;
        default:
            printf("Vous devez entrer un nombre entre 1 et 5 !\n\n\n");
            break;
        }
    }

    printf("Au revoir !");

    return 0;
}
