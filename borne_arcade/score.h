#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

// ----- DEFINES
#define TAILLE_LISTE 5
#define TAILLE_MAX_NOM 10

#define RETURN_OK 0
#define RETURN_KO -1

// ----- STRUCTURES
typedef struct HIGHT_SCORE
{
    char nom[TAILLE_MAX_NOM];
    long score;
}hightScore;

// ----- PROTOS
int loadHightScore(FILE* , hightScore*);
FILE* loadGameHighScores(const char * path, hightScore *hsList);
void afficherHightScore(hightScore*);

int addHightScore(hightScore*, hightScore);
int saveHightScore(FILE* , hightScore*);



#endif // SCORE_H_INCLUDED
