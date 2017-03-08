/*-----------------------------------------------------------------------------------------------------------------*/
/*                                             listeChainee_semaine.h                                              */
/*                                                                                                                 */
/* Role:    Déclaration des directives de compilation, constantes symboliques, types et prototypes.                */                       /*                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------*/


#ifndef AGENDA_LISTECHAINEE_SEMAINE_H
#define AGENDA_LISTECHAINEE_SEMAINE_H





#include "./listeChainee_action.h"




#define TAILLE_SEMAINE 7






typedef struct semaine
{

  char ann_sem[TAILLE_SEMAINE];

  action_t * PlisteAction;

  struct semaine * psem_suiv;

}semaine_t;




semaine_t * AllocationSemaine();

void CreerSemaine (semaine_t *, char *);

void InsertionSemaine (semaine_t **, semaine_t *);

semaine_t **  RechercherSemaine (semaine_t **, char *, int *);

void SuppressionSemaine(semaine_t **);

void LibererListe(semaine_t **);

void CreerListe (semaine_t **, FILE *);

void LectureFichier(char *, semaine_t **, int *);

void SauvegardeDansFichier(semaine_t *, int *);

void AfficheSauvegarde();

void supression(semaine_t **, char *, char *);




#endif
