/*------------------------------------------------------------------------------------------------------*/
/*                                        listeChainee_action.c                                         */
/*                                                                                                      */                       
/* Role:   Définition des fonctions qu'on utilise pour la creation d'une liste chainee d'actions        */
/*         triée à partir d'un fichier de données  où son nom est donné en ligne de commande            */
/*------------------------------------------------------------------------------------------------------*/







#include "./listeChainee_action.h"








/*--------------------------------------------------------------------------------------------------*/
/* AllocationAction         Allouée le bloc action.                                                 */
/*                                                                                                  */
/* En entrée:   Rien en entrée                                                                      */
/*                                                                                                  */
/* En sortie:   On retourne l'adresse du bloc action alloué.                                        */ 
/*                                                                                                  */
/* variables locales: 	 paction - Pointeur sur le bloc alloué.                                     */
/*--------------------------------------------------------------------------------------------------*/


action_t * AllocationAction ()
{

  action_t * paction=(action_t *)malloc(sizeof(action_t));

  return paction;

}








/*--------------------------------------------------------------------------------------------------*/
/* CreerAction         Crée l'action en introduisant dans le bloc alloué le jour et l'heure         */ 
/*		       lu à partir d'un fichier.                                                    */
/*                                                                                                  */ 
/* En entrée:   paction - Pointeur sur le bloc alloué pour l'action.                                */                                      
/* 		     s1 - Chaine de caractères contenantt le jour et l'heure de l'action.           */
/*		     s2 - Chaine de caractere contenant le nom de l'action.                         */    
/*                                                                                                  */
/* En sortie:   Rien en sortie                                                                      */ 
/*--------------------------------------------------------------------------------------------------*/


void CreerAction (action_t * paction, char * s1, char * s2)
{

  strcpy(paction->jour_heure,s1);		/*copie le jour et l'heure*/

  strcpy(paction->nom_action,s2);               /*copie le nom de l'action*/

  paction->paction_suiv=NULL;
}








/*----------------------------------------------------------------------------------------------------------------------*/
/* RechercherAction          Recherche une action dans la liste chainée des actions.                                    */
/*                                                                                                                      */
/* En entrée:  PpteteListe - Pointeur de pointeur de tête de la liste chainée des actions.                              */
/*             pvaleur 	   - Pointeur sur l'action à rechercher (qui est une chaine de caractères).                     */
/*             ptrouver    - Pointeur sur une case mémoire contenant 0 si on a pas trouvé ou 1 si on a trouvé la chaine.*/
/*                                                                                                                      */
/* En sortie:         prec - Pointeur de pointeur de tete de liste chainée des actions ou pointeur sur la case pointeur */
/*                           d'élément précédent dans la liste chainée d'actions.                                       */
/*                ptrouver - Pointeur sur une case mémoire contenant 0 si on a pas trouvé ou 1 si on a trouvé l'action  */
/*                           dans la liste chainée des actions.                                                         */
/*                                                                                                                      */
/* Variable(s) locale(s) :   pcour - Pointeur sur l'action courante.                         				*/
/*                           prec  - Pointeur de pointeur de tete de liste chainée des actions ou pointeur sur la case  */
/*                                   pointeur de l'élément précédent de la liste chainée des actions.                   */
/*----------------------------------------------------------------------------------------------------------------------*/


action_t ** RechercherAction (action_t ** PpteteListe, char * pvaleur, int * ptrouver)	
{

  action_t * pcour = *PpteteListe, ** prec = PpteteListe;                 /*Initialisation à la première action et au pointeur de tete*/

  *ptrouver=0;

  while ((pcour != NULL) && (strcmp(pvaleur,pcour->jour_heure) > 0)) 	  /*Tantque je suis dans la liste et que ma chaine est plus grande*/
        {                                                                 

          prec = &(pcour->paction_suiv);                                  /*on récupère l'adresse de la case pointeur de l'élément courant*/

          pcour = *prec;                                                  /*passe au suivant*/

        }

  if ((pcour != NULL) && (!strncmp(pvaleur, pcour->jour_heure,TAILLE_JOUR_HR)))  /*si on trouve la chaine*/
        {
                                                                                                                                     
          *ptrouver=1;

        }

      return prec;

}







/*---------------------------------------------------------------------------------------------------------------------*/
/* InsertionAction         Insère une nouvelle action dans la liste chainée des actions.                               */ 
/*										     				       */ 
/* En entrée:    ppaction - Pointeur de pointeur de tete de liste chainée des actions ou pointeur sur la case pointeur */
/*                          de l'élément précédent.                                                                    */ 
/*	          paction - Pointeur sur l'action à insérer.                            			       */                   /*                                                              				                           */
/* En sortie:    ppaction - Pointeur de pointeur de tete de liste chainée des actions ou pointeur sur la case pointeur */
/*                          de l'élément précédent.                                                                    */                   /*---------------------------------------------------------------------------------------------------------------------*/


void InsertionAction (action_t ** ppaction,action_t * paction)
{

  paction->paction_suiv = *ppaction;

  *ppaction = paction;

}






/*---------------------------------------------------------------------------------------------------------------------*/
/* SuppressionAction          Supprime une action de liste chainée des actions.                                        */ 
/*										     				       */ 
/* En entrée:   ppaction - Pointeur de pointeur de tete de liste chainée des actions ou pointeur sur la case           */
/*                         pointeur de l'élément précédent de la liste chainée des actions.                            */                  
/*                                                                                                                     */
/* En sortie:	ppaction - Pointeur de pointeur de tete de liste chainée des actions ou pointeur sur la case           */
/*                         pointeur de l'élément précédent de la liste chainée des actions.                            */
/*                                                                                                                     */ 
/* Variable(s) locale(s):  paction - Pointeur sur l'action à supprimer.                            		       */
/*---------------------------------------------------------------------------------------------------------------------*/


void SuppressionAction(action_t ** ppaction)
{

  action_t * paction = *ppaction;           /*recupère l'adresse de l'action à supprimer*/

  *ppaction = paction->paction_suiv;        /*l'action précédente pointe sur l'action après l'action à supprimer*/

  free(paction);                            /*supprime l'action*/

  paction = NULL;
}


