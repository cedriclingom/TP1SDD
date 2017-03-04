/*------------------------------------------------------------------------------------------------------*/
/*                                        listeContigue.h                                               */
/*                                                                                                      */
/* Le role : les prototypes des tous les sous-foctions qui participent dans la creation                 */
/*           d'une liste contiguë des jours où une action contenant un motif (chaine de caractères)     */
/*           donné est présente. Cette liste sera gérée avec un pointeur de tête et un pointeur         */ 
/*           de fin et définie avec une taille fixe maximum.                                            */
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


int CompareChaine(char *, char *, int);

int RechercherMotif(char *, char *);

jour_t ** AllocationListeContigue ();

jour_t * AllocationJour();

void CreerJour(jour_t *, semaine_t *, action_t *);

void InsererJour(jour_t **, jour_t *,int);

jour_t * LectureSemaineJour();

void LectureMotif(char **, int *);

void CreerListeJour(semaine_t *, char *, jour_t **,jour_t ***);

void AfficherListeContigue(jour_t **, jour_t **);

void LibererListeContigue(jour_t **, jour_t **);




#endif
