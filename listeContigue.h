/*------------------------------------------------------------------------------------------------------*/
/*                                        listeContigue.h                                               */
/*                                                                                                      */
/* Le role	:   les prototypes des tous les sous-foctions qui participent dans la creation              */
/*              d'une liste contiguë des jours où une action contenant un motif (chaine de caractères)  */
/*              donné est présente. Cette liste sera gérée avec un pointeur de tête et un pointeur      */ 
/*              de fin et définie avec une taille fixe maximum.                                         */
/*------------------------------------------------------------------------------------------------------*/

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
jour_t ** allocationListeContigue ();
jour_t * allocationJour();
void creerJour(jour_t *, semaine_t *, action_t *);
void insererJour(jour_t **, jour_t *,int);
jour_t * lectureSemaineJour();
int lectureMotif(char **);
void creerListeJour(semaine_t *, char *, jour_t **,jour_t ***);
void afficherListeContigue(jour_t **, jour_t **);
void libererListeContigue(jour_t **, jour_t **);

#endif
