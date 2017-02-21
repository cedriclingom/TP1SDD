#include "./listeChainee_action.h"







action_t * allocationAction ()
{
  action_t * pAction=(action_t *)malloc(sizeof(action_t));

  return pAction;
}



void creerAction (action_t * pAction, char * s1, char * s2)
{
  strcpy(pAction->jour_heure,s1);
  strcpy(pAction->nom_action,s2);
  pAction->pAction_suiv=NULL;
}




action_t ** rechercherAction (action_t ** ppTeteListe, char * pvaleur, int * ptrouver)
{
  action_t * pcour = *ppTeteListe, ** prec = ppTeteListe;

  *ptrouver=0;

  while ((pcour != NULL) && (strcmp(pvaleur,pcour->jour_heure) > 0))
        {

          prec = &(pcour->pAction_suiv);

          pcour = *prec;

        }
  if ((pcour != NULL) && (!strncmp(pvaleur, pcour->jour_heure,TAILLE_JOUR_HR)))
        {

          *ptrouver=1;

        }
      return prec;
}


void insertionAction (action_t ** ppAction,action_t * pAction)
{
  pAction->pAction_suiv = *ppAction;;
  *ppAction = pAction;
}









void suppressionAction(action_t ** ppAction)
{
  action_t * pAction = *ppAction;
  *ppAction = pAction->pAction_suiv;
  free(pAction);
  pAction=NULL;
}


