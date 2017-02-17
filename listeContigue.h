#ifndef AGENDA_LISTECONTIGUE_H
#define AGENDA_LISTECONTIGUE_H



#include "./listeChainee_semaine.h"



#define TAILLE_MAX 20




typedef struct jour
{
  char ann_sem[TAILLE_SEMAINE];
  char jour_heure[TAILLE_JOUR_HR];
}jour_t;


int compareChaineN (char *, char *, int);
int rechercherMotif(char *, char *);
void creerListeJour(semaine_t *, char *, jour_t **);

#endif
