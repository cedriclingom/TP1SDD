/*------------------------------------------------------------------------------------------------------*/
/*                                        listeChainee_action.c                                         */                                                                           
/* Le role	:   tous les sous-fonctions qu'on utilise pour la creation d'une liste chainee d'actions    */
/*              triée à partir d'un fichier de données  où son nom est donné en ligne de commande       */
/*------------------------------------------------------------------------------------------------------*/










#include "./listeChainee_action.h"

/*--------------------------------------------------------------------------------------------------*/
/* AllocationAction         allouée une action                                                      */
/*                                                                                                  */
/* En entrée		 :   Rien en entrée                                                             */
/*                                                                                                  */
/* En sortie		 :   paction - pointeur sur le bloc alloué pour l'action                        */ 
/* variables locales : 	 aucune variable locale                               					    */
/*--------------------------------------------------------------------------------------------------*/

action_t * AllocationAction ()
{
  action_t * paction=(action_t *)malloc(sizeof(action_t));

  return paction;
}






/*--------------------------------------------------------------------------------------------------*/
/* CreerAction         il va remplir le bloc action par le jour,l'heure et le nom de l'action       */ 
/*										     														*/ 
/* En entrée 		 : 															                  	*/
/*	                     paction - pointeur sur le bloc action                                      */                                      
/* 						 s1 -      chaine de caractere contient le jour et l'heure de l'action      */
/*						 s2 -      chaine de caractere contient le nom de l'action                  */    
/*                                                                                                  */
/* En sortie		 :   Rien en sortie                                                             */ 
/* variables locales : 	 aucune variable locale                               					    */
/*--------------------------------------------------------------------------------------------------*/

void CreerAction (action_t * paction, char * s1, char * s2)
{
  strcpy(pAction->jour_heure,s1);		/* on copie le jour,l'heure et le nom d'action */
  strcpy(pAction->nom_action,s2);
  paction->paction_suiv=NULL;
}





/*----------------------------------------------------------------------------------------------------------------------*/
/* RechercherAction     Recherche une action dans la liste des actions                                                  */
/*                                                                                                                      */
/* En entrée:  ppTeteListe - Pointeur de pointeur de tête de la liste des actions.                                      */
/*             pvaleur 	   - Pointeur sur l'action à rechercher (qui est une chaine de caractères).                     */
/*             ptrouver    - pointeur sur une case mémoire contenant 0 si on a pas trouvé ou 1 si on a trouvé la chaine.*/
/*                                                                                                                      */
/* En sortie:  prec     	- Pointeur de pointeur sur la case d'élément précédent dans la liste chainée d'action.      */
/*             ptrouver 	- pointeur sur une case mémoire contenant 0 si on a pas trouvé ou 1 si on a trouvé la chaine*/
/*                                                                                                                      */
/* Variables locales :  pcour 		- un pointeur qui parcourt la liste des actions  									*/
/*----------------------------------------------------------------------------------------------------------------------*/

action_t ** RechercherAction (action_t ** PpteteListe, char * pvaleur, int * ptrouver)	
{
  action_t * pcour = *PpteteListe, ** prec = PpteteListe;

  *ptrouver=0;

  while ((pcour != NULL) && (strcmp(pvaleur,pcour->jour_heure) > 0)) 	/* tant que la liste n'est pas finie et pvaleur 
        {                                                                  inferieure à jour_heure */

          prec = &(pcour->pAction_suiv);                               /* avancer le prec */

          pcour = *prec;                                               /* avancer l'élément courant*/

        }
  if ((pcour != NULL) && (!strncmp(pvaleur, pcour->jour_heure,TAILLE_JOUR_HR)))
        {                                                              /* si la liste n'est finie et l'action existe
                                                                          dans la liste des actions */
          *ptrouver=1;

        }
      return prec;
}







/*---------------------------------------------------------------------------------------------------------------------*/
/* InsertionAction         il va inserer une action dans la liste des actions       								   */ 
/*										     																		   */ 
/* En entrée 		 : 															                  					   */
/*	                     paction  - pointeur sur le bloc action                                      				   */                                      
/* 						 ppaction - Pointeur de pointeur sur la case precedente (ou pointeur de pointeur de tete si    */   
/*                       		    on insere en tete)                                               				   */
/* En sortie		 :   Rien en sortie                                                             				   */ 
/* variables locales : 	 aucune variable locale                               					    				   */
/*---------------------------------------------------------------------------------------------------------------------*/
void InsertionAction (action_t ** ppaction,action_t * paction)
{
  paction->paction_suiv = *ppaction;;
  *ppaction = paction;
}






/*---------------------------------------------------------------------------------------------------------------------*/
/* InsertionAction         il va supprimer une action dans la liste des actions       								   */ 
/*										     																		   */ 
/* En entrée 		 : 															                  					   */                                     
/* 						 ppaction - Pointeur de pointeur sur la case precedente (ou pointeur de pointeur de tete si    */   
/*                       		    on veut supprimer la case qui est en tete)                           			   */
/* En sortie		 :   Rien en sortie                                                             				   */ 
/* variables locales : 	 aucune variable locale                               					    				   */
/*---------------------------------------------------------------------------------------------------------------------*/

void SuppressionAction(action_t ** ppaction)
{
  action_t * paction = *ppaction;
  *ppaction = paction->paction_suiv;
  free(paction);
  paction=NULL;
}


