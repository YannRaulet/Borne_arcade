#include <stdio.h>
#include <stdlib.h>
#include "papier_ciseaux.h"



void score_final( int score_joueur, int score_robot)
{
    // On affiche le score
    printf("\nScore du robot : %d\nVotre score : %d\n\n", score_robot, score_joueur);

        // On compare les resultats
    if (score_joueur > score_robot)
    {
    printf("Vous avez gagne la partie avec un score de %d contre un score de %d pour le robot\n\n",score_joueur,score_robot);
    }
    else if (score_joueur < score_robot)
    {
    printf("Vous avez perdu la partie avec un score de %d contre un score de %d pour le robot\n\n",score_joueur,score_robot);
    }
    else
    {
    printf("Vous terminez la partie sur une egalite\n\n");
    }

        return 0;
}

void choix_robot(int choix_utilisateur,char* choix_robot)
{
        // On interprete le choix du robot
        if (choix_utilisateur == 1)
        {
            *choix_robot = '1';
        }
        else if (choix_utilisateur == 2)
        {
            *choix_robot = '2';
        }
        else if (choix_utilisateur == 3)
        {
            *choix_robot = '3';
        }

        return 0;
}

void choix_utilisateur(int choix_joueur, int* quit)
{
       if(choix_joueur == '1' || choix_joueur == '2'|| choix_joueur == '3')
        {
            printf("Vous avez choisi "); //on affiche le choix du joueur
            if (choix_joueur =='1')
            {
                printf("\nPierre\n");
                choix_joueur = '1';
            }
            else if (choix_joueur == '2')
            {
                printf("\nFeuille\n");
                choix_joueur = '2';
            }
            else if (choix_joueur == '3')
            {
                printf("\nCiseaux\n");
                choix_joueur = '3';
            }
        }else if (choix_joueur == '0')
        {
            printf("Bonjour");
            *quit = 0;
        }else
        {
            printf("Votre saisie n'est pas valable, veuillez reesayer avec 1, 2, 3 ou 0\n");     //message d'erreur si le mauvais caractère est rentré
        }

        return 0;
}

void playPapierCiseaux()
{

    // Les variables du projet
    int jeu_ordinateur = 0, jeu_utilisateur = 0;
    const int VALEUR_MIN = 1, VALEUR_MAX = 3;
    char choixDuJoueur;
    char choixDuRobot;
    int score = 0,quitter = 1, robot = 0; // On initialise le score et le nombre d'essai a 0.

    // Choix du nombre au hasard
    srand(time(NULL)); // Initialisation de la fonction rand


    // Ici debute la boucle du jeu
    do {

        jeu_ordinateur = (rand() % VALEUR_MAX) + VALEUR_MIN; // On choisit un nombre entre 1 et 3

        choix_robot(jeu_ordinateur,&choixDuRobot);

        // Le jeu
        printf("Choissisez 1-Pierre, 2-Papier, 3-Ciseaux (saisissez 0 pour quitter) : ");
        fflush(stdin);
        scanf("%c",&choixDuJoueur);//le joueur rentre son choix
        fflush(stdin);

        choix_utilisateur(choixDuJoueur, &quitter);


        // Egalite
        if (choixDuJoueur == choixDuRobot)
        {
            printf("%c contre %c : Egalite parfaite !\n", choixDuJoueur, choixDuRobot);
        }
        // Si joueur = pierre
        else if (choixDuJoueur == '1' )
        {
            if (choixDuRobot == '2')
            {
                printf("La feuille recouvre la pierre, vous perdez la manche\n");
                robot++;
            }
            else if (choixDuRobot == '3')
            {
                score++;
                printf("La pierre casse le ciseaux, vous gagnez la manche\n");

            }
        }else if (choixDuJoueur == '2' ) // Si joueur = feuille
        {
            if (choixDuRobot == '1')
            {
                score++;
                printf("La feuille recouvre la pierre, vous gagnez la manche\n");

            }else if (choixDuRobot == '3')
            {
                printf("Le ciseaux coupe la feuille, vous perdez la manche\n");
                robot++;
            }
        }else if (choixDuJoueur == '3' ) // Si joueur = ciseaux
        {
            if (choixDuRobot == '1')
            {
                printf("La pierre casse le ciseaux, vous perdez la manche\n");
                robot++;
            }
            else if (choixDuRobot == '2')
            {
                score++;
                printf("Le ciseaux coupe la feuille, vous gagnez la manche\n");
            }
        }

        printf("%d", quitter);

    // Ici s'arrete la boucle du jeu
    }while(quitter == 1);

    score_final(score, robot);

    // Fin du code
    return 0;
}
