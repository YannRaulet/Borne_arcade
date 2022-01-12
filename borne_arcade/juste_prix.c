#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "juste_prix.h"
#include "score.h"

int randomCode()
{
    // declaration de nos variables
    int nombre_mystere = 0;
    const int VALEUR_MIN = 1, VALEUR_MAX = 100;

    //  generation du code aleatoire
    nombre_mystere = (rand() % (VALEUR_MAX - VALEUR_MIN + 1)) + VALEUR_MIN;
    printf("Devinez quel est mon nombre mystere. Indice: c'est un nombre entre %d et %d \n", VALEUR_MIN, VALEUR_MAX);
    return nombre_mystere;
}

void playJustePrix()
{
   printf("Juste Prix !\n");

    // declaration de nos variables
    int nombre_utilisateur = 0;
    int compteur = 0;
    const int NOMBRE_MAX = 10;
    hightScore highScoresList[TAILLE_LISTE];

    srand(time(NULL));
    int nombre_mystere = randomCode();

    do
    {
        /* Tant que le compteur est inférieur à 10,
           afficher un message à l'utilisateur lui demandant d'entrer un nombre
        */
        if(compteur < NOMBRE_MAX)
        {
            compteur = compteur +1;
            printf("Entrez un nombre aleatoire \n");
            scanf("%d", &nombre_utilisateur);

            // Si nombre déclaré est supérieur au nombre mystere, afficher le nombre de tentative, puis "c'est moins"
            if(nombre_utilisateur > nombre_mystere)
            {
                printf("tentative %d > %d \n", compteur, nombre_utilisateur);
                printf("C'est moins ! \n");
            }
            else if (nombre_utilisateur < nombre_mystere)             // Si nombre déclaré est inférieur au nombre mystere, afficher le nombre de tentative, puis "c'est plus"
            {
                printf("tentative %d > %d \n", compteur, nombre_utilisateur);
                printf("C'est plus ! \n");
            }
            else             // afficher un message si le nombre mystère est trouvé
            {
                printf ("Bravo, vous avez trouve le nombre mystere %d en %d tentatives \n", nombre_mystere, compteur);
                // Utilisation du score.h
                hightScore hScore;
                hScore.score = NOMBRE_MAX - compteur + 1;
                printf ("Votre nombre de points %ld \n", hScore.score);
                printf ("Entrez votre nom %s \n", hScore.nom);
                scanf("%s", hScore.nom);
                fflush(stdin);
                addHightScore(highScoresList, hScore);
            }
        } else //quand l'utilisateur a atteint le maximum de tentatives, arreter le programme
        {
            printf("Vous avez atteint le nombre maximum de tentatives !!");
            break;
        }
    }
    while (nombre_utilisateur != nombre_mystere);
}
