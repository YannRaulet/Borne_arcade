#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pendu.h"
#include "score.h"

//Met a jour motCache afin d'afficher les nouvelles lettres trouvees
void updateMot(const char mot[], const int lettresTrouvees[], char motCache[]) {
    for(int i = 0; i < TAILLE_MOT - 1; i++) {
        motCache[i] = lettresTrouvees[i] ? mot[i] : '-';
    }
}

//Verifie si la lettre est presente dans le mot et met a jour lettreTrouvees
int checkLetter(const char mot[], int lettresTrouvees[], char lettre) {
    int present = 0;
    for(int i = 0; i < TAILLE_MOT - 1; i++) {
        if(mot[i] == lettre) {
            lettresTrouvees[i] = 1;
            present = 1;
        }
    }
    return present;
}

//Indique si le mot entier a ete trouve
int isWordFound(const int lettresTrouvees[]) {
    for(int i = 0; i < TAILLE_MOT - 1; i++) { //On vérifie si tout le mot a été trouvé
        if(!lettresTrouvees[i]) {
            return 0;
        }
    }
    return 1;
}

//Récupère l'entrée de l'utilisateur et enlève le retour à la ligne généré par fgets
void getInput(char entreeUser[]) {
    fgets(entreeUser, 99, stdin);
    fflush(stdin);
    strchr(entreeUser, '\n')[0] = '\0'; //Enlève le saut à la ligne
}

//Gère le cas ou on a entré un mot
int processWord(const char entreeUser[], const char motATrouver[], int *nbVies) {
    if(strcmp(entreeUser, motATrouver) == 0) { //Si c'est le bon mot
        return 1;
    }
    (*nbVies)--;
    printf("Ce n'est pas le bon mot. Il vous reste %d vies\n", *nbVies);
    return 0;
}

//Gère le cas ou on a entré une lettre
void processLetter(const char motATrouver[], char motCache[], int lettresTrouvees[], int *nbVies, char lettre) {
    if(lettre < 'A' || lettre > 'Z') {
        printf("Ce n'est pas une lettre majuscule\nIl vous reste %d vies\n", *nbVies);
        return;
    }
    if(checkLetter(motATrouver, lettresTrouvees, lettre) != 0) { //Si la lettre est bonne
        updateMot(motATrouver, lettresTrouvees, motCache); //On met à jour la visibilité du mot
        printf("Oui, la lettre %c est presente dans le mot \"%s\". Il vous reste %d vies\n", lettre, motCache, *nbVies);
    }
    else { //Si ce n'est pas la bonne lettre
        (*nbVies)--;
        printf("Non, la lettre %c n'est pas presente dans le mot \"%s\". Il vous reste %d vies\n", lettre, motCache, *nbVies);
    }
}

void playPendu()
{
    hightScore highScoresList[TAILLE_LISTE];
    FILE* pt_fichier = loadGameHighScores("datas/PenduHighScore.sav", highScoresList);
    if(!pt_fichier) {
        return;
    }

    char motATrouver[] = "CODEBLOCKS";
    char motCache[TAILLE_MOT] = {'\0'}; //La version du mot revelee a l'utilisateur en fonction des lettres trouvees
    char entreeUser[100];
    int lettresTrouvees[TAILLE_MOT - 1] = {0}; //Permet de savoir les lettres qui ont ete trouvees (0 pour non trouvé, 1 pour trouvé)
    int nbVies = 10, gagne = 0;

    printf("Jeu du Pendu!\n");

    updateMot(motATrouver, lettresTrouvees, motCache); //Initialisation de la visibilité du mot (que des tirets)

    while(gagne != 1 && nbVies  > 0) {
        printf("Mot a trouver : %s\n", motCache);
        printf("Donnez une lettre ou un mot (en majuscule) > ");
        getInput(entreeUser);

        if(strlen(entreeUser) > 1) { //Si c'est un mot
            gagne = processWord(entreeUser, motATrouver, &nbVies);
        }
        else if(strlen(entreeUser) == 1) { //Si c'est une lettre
            processLetter(motATrouver, motCache, lettresTrouvees, &nbVies, entreeUser[0]);
            gagne = isWordFound(lettresTrouvees);
        }
        else { //Entrée vide
            continue;
        }
    }
    if(gagne) {
        printf("Bravo, vous avez trouve le mot\n");
        hightScore hScore;
        hScore.score = nbVies;
        printf("Vous marquez %ld points !\nEntrez votre nom pour le high score : ", hScore.score);
        scanf("%s", hScore.nom);
        fflush(stdin);
        addHightScore(highScoresList, hScore);
        saveHightScore(pt_fichier, highScoresList);
    }
    else {
        printf("Perdu ! Il ne vous reste plus de vies\n");
    }
    fclose(pt_fichier);
}
