#ifndef AGENDA_LISTECHAINEE_SEMAINE_H
#define AGENDA_LISTECHAINEE_SEMAINE_H





#include "./listeChainee_action.h"




#define TAILLE_SEMAINE 7






typedef struct semaine
{
  char ann_sem[TAILLE_SEMAINE];
  action_t * pListeAction;
  struct semaine * pSem_suiv;
}semaine_t;




semaine_t * allocationSemaine();
void creerSemaine (semaine_t *, char *);
semaine_t **  rechercherSemaine (semaine_t **, char *, int *);
void insertionSemaine (semaine_t **, semaine_t *);
void creerListe (semaine_t **, FILE *);
int lectureFichier(char *, semaine_t **);
int sauvegardeDansFichier(semaine_t *);
void suppressionSemaine(semaine_t **);
void afficheSauvegarde();
void supression(semaine_t **, char *, char *);
void libererListe(semaine_t **);



#endif
