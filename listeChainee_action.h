#ifndef AGENDA_LISTECHAINEE_ACTION_H
#define AGENDA_LISTECHAINEE_ACTION_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define TAILLE_JOUR_HR 4
#define TAILLE_ACTION 12





typedef struct action
{
  char jour_heure[TAILLE_JOUR_HR];
  char nom_action[TAILLE_ACTION];
  struct action * pAction_suiv;
}action_t;




action_t * allocationAction ();
void creerAction (action_t *, char*, char *);
action_t ** rechercherAction (action_t **, char *, int *);
void insertionAction (action_t **, action_t *);
void suppressionAction(action_t **);

#endif
