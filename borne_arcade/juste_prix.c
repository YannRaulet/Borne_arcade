#include <stdio.h>
#include <stdlib.h>

#include "juste_prix.h"

void playJustePrix()
{
    // Déclaration des variables
    char code_a_trouver[] = {'R', 'V', 'B', 'J'};
    char saisie_utilisateur[4];
    const int NOMBRE_CARACTERES = 4;
    int nombre_bien_place=0;

    for (int nombre_de_tentatives=1; nombre_de_tentatives < 10; nombre_de_tentatives++)
    {
        // Lecture de la saisie utilisateur
        printf("Entrez la combinaison de 4 caractères sans espace \n");
        printf("Vous avez le choix entre R, V, B, J et O \n");
        fflush(stdin);

        // comparaison du code à trouver et de la saisie utilisateur
        for (int ligne=0; ligne < 3; ligne++)
        {
            scanf("%c", &saisie_utilisateur[ligne]);

            if (saisie_utilisateur[ligne] == code_a_trouver[ligne])
            {
                nombre_bien_place++;
            }
        }
        printf("Le nombre de piece bien placee est de %d \n", nombre_bien_place);
        printf("Le nombre de tentatives est de %d \n", nombre_de_tentatives);
    }
}
