#include <stdio.h>
#include <stdlib.h>
#include "score.h"
#include "pendu.h"
#include "mastermind.h"
#include "juste_prix.h"
#include "papier_ciseaux.h"

hightScore highScoresList[TAILLE_LISTE];

void printMenu() {
    printf("\tBienvenue sur la borne d'arcade !\n\n");
    printf("Voici la liste des jeux : \n");
    printf("1) Pierre-Feuille-Ciseaux\n");
    printf("2) Juste Prix\n");
    printf("3) Mastermind\n");
    printf("4) Pendu\n");
    printf("5) Quitter\n");
    printf("6) Score\n\n");
    printf("Choississez a quel jeu vous allez jouer (Entrez un nombre entre 1 et 5) : ");
}


int main()
{
    //printf("Hello world!\n");
    //playPendu();
    //playMastermind();
    //playJustePrix();
    //playPapierCiseaux();

    char* path = "datas/HighScore.sav";

    // ouverture du fichier
    FILE* pt_fichier = fopen(path, "r+");
    if(pt_fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier %s\n", path);
        return RETURN_KO;
    }

    //chargement du fichier
    int resultat = loadHightScore(pt_fichier, highScoresList);
    if(resultat == RETURN_KO)
    {
        printf("Impossible de lire le fichier %s\n", path);
        return RETURN_KO;
    }


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
            quit = 1;
            break;
        case 6:
            afficherHightScore(highScoresList);
            break;
        default:
            printf("Vous devez entrer un nombre entre 1 et 5 !\n\n\n");
            break;
        }
        saveHightScore(pt_fichier,highScoresList);
    }

    printf("Au revoir !");

    return 0;
}
