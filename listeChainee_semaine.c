/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                         listeChaine_semaine.c:  Définition des fonctions permettent de manipuler la liste des semaines                                            */
/*                                                                                                                                                                   */
/*                                                                                                                                                                   */
/*                                                                                                                                                                   */
/*                                                                                                                                                                   */
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/







#include "./listeChainee_semaine.h"









/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* allocationSemaine         Alloue un bloc de la seamine.                                                                                                           */
/*                                                                                                                                                                   */
/* En entrée:  RAS                                                                                                                                                   */
/*                                                                                                                                                                   */
/* En sortie:  On retourne l'adresse du bloc semaine alloué.                                                                                                         */
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


semaine_t * allocationSemaine()
{
  semaine_t * pSemaine = (semaine_t *)malloc(sizeof(semaine_t));

  return pSemaine;
}




/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* creerSemaine         Crée la semaine en introduisant dans le bloc alloué l'année et le numéro de semaine lu à partir d'un fichier.                                */
/*                                                                                                                                                                   */
/* En entrée:  ppSemaine, f   Respectivement l'adresse du pointeur sur le bloc alloué et le fichier à partir du quel on va lire                                      */
/*                                                                                                                                                                   */
/* En sortie:  ppSemaine   Pointeur de pointeur sur la semaine créer                                                                                                 */
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


void creerSemaine(semaine_t * pSemaine, char * s)
{
  strcpy(pSemaine->ann_sem,s);
  pSemaine->pListeAction=NULL;
  pSemaine->pSem_suiv=NULL;
}



/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* rechercherSemaine        Rcherche une semaine dans la liste des semaines                                                                                          */
/*                                                                                                                                                                   */
/* En entrée:  pListeSemaine - Pointeur sur la tête de la liste des semaines.                                                                                        */
/*             pprec - Pointeur de pointeur sur la case d'élément précédent dans la liste chainée de semaines.                                                       */
/*             pvaleur - Pointeur sur la semaine à rechercher (qui est une chaine de caractères).                                                                    */
/*             ptrouver - pointeur sur une case mémoire contenant 0 si on a pas trouvé ou 1 si on a trouvé la chaine.                                                */
/*                                                                                                                                                                   */
/* En sortie:   pprec - Pointeur de pointeur sur la case d'élément précédent dans la liste chainée de semaines.                                                      */
/*             ptrouver - pointeur sur une case mémoire contenant 0 si on a pas trouvé ou 1 si on a trouvé la chaine.                                                */
/*             Rien n'est retourner par la fonction.                                                                                                                 */
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



semaine_t **  rechercherSemaine (semaine_t ** ppTeteListe,char * pvaleur, int * ptrouver)
{
  semaine_t * pcour = *ppTeteListe, ** prec = ppTeteListe;         /*Pointeur sur la semaine courante*/

  *ptrouver = 0;

  while   ((pcour != NULL) && (strcmp(pvaleur, pcour->ann_sem) > 0)) /*Tantque je suis dans la liste et que ma chaine est plus grande*/
    {
      
      prec = &(pcour->pSem_suiv);                                                   /*On récupère l'adresse de la case pointeur de l'élément précédent*/
      
      pcour = *prec;                                                              /*Passe au suivant*/
      
    }
  if ((pcour != NULL) && (!strcmp(pvaleur, pcour->ann_sem)))         /*Si on trouve la chaine*/
    {
      *ptrouver=1;
    }
  return prec;
}



void insertionSemaine (semaine_t ** ppSemaine,semaine_t * pSemaine)
{
  pSemaine->pSem_suiv = *ppSemaine;
  *ppSemaine = pSemaine;
}


void creerListe (semaine_t ** ppTeteListe, FILE * f)
{
  semaine_t * pSemaine = NULL, ** precSemaine = NULL;
  action_t * pAction = NULL, ** precAction = NULL;
  char * s4, * s5;
  char s1[TAILLE_SEMAINE];
  char s2[TAILLE_JOUR_HR];
  char s3[TAILLE_ACTION];
  int trouver;
  s4 = fgets(s1,TAILLE_SEMAINE,f);
  while (s4 != NULL)
    {      
      trouver=0;
      if (strcmp(s4,"\n"))
	{
	  s5 = fgets(s2,TAILLE_JOUR_HR,f);
	  if((s5 != NULL) && strcmp(s5,"\n"))
	    {
	      precSemaine = rechercherSemaine (ppTeteListe,s1, &trouver);	  	 
	      if (!(trouver))
		{
		  pSemaine = allocationSemaine();
		  if   (pSemaine != NULL)
		    {
		      creerSemaine (pSemaine,s1);
		      insertionSemaine(precSemaine,pSemaine);
		    }
		}
	      if(fgets(s3,TAILLE_ACTION,f) != NULL)
		{
		  trouver = 0;
		  precAction = rechercherAction (&((*precSemaine)->pListeAction), s2, &trouver);
		  if(!(trouver))
		    {
		      pAction = allocationAction();
		      if   (pAction != NULL)
			{
			  creerAction (pAction, s2, s3);
			  insertionAction(precAction, pAction);
			}
		      else
			{
			  libererListe(ppTeteListe);
			}
		    }
		  
		}
	    }
	}
      s4 = fgets(s1,TAILLE_SEMAINE,f);
    }
}








int lectureFichier(char * ch, semaine_t ** ppTeteListe)
{
  int codeErr = 1;
  FILE * fTexte = NULL;
  fTexte = fopen(ch,"r");
  if (fTexte != NULL)
    {
      creerListe (ppTeteListe, fTexte);
      fclose(fTexte);
    }
  else
    {
      codeErr = 0;
    }
  return codeErr;
}





int sauvegardeDansFichier(semaine_t * pTeteListe)
{
  int codeErr = 1;
  semaine_t * pcour1=pTeteListe;
  action_t *pcour2;
  FILE * f = fopen("sauvegarde.txt","w");
  if(f != NULL)
    {
      while   (pcour1 != NULL)
	{
	  
	  pcour2 = pcour1->pListeAction;
	  
	  while   (pcour2 != NULL)
	    {
	      fprintf(f,"%s%s%s", pcour1->ann_sem, pcour2->jour_heure, pcour2->nom_action);
	      pcour2 = pcour2->pAction_suiv;
	      
	    }
	  pcour1 = pcour1->pSem_suiv;
	  
	}
      fclose(f);
    }
  else
    {
      codeErr = 0;
    }
  return codeErr;
}






void suppressionSemaine(semaine_t ** ppSemaine)
{
  semaine_t * pSemaine = *ppSemaine;
  *ppSemaine = pSemaine->pSem_suiv;
  free(pSemaine);
  pSemaine=NULL;
}




void supression(semaine_t **ppTeteListe, char * ann_sem, char * jour_heure)
{
  semaine_t ** precSemaine = NULL;
  action_t ** precAction =NULL;
  int trouver=0;
  if (*ppTeteListe !=NULL)
    {
      precSemaine = rechercherSemaine(ppTeteListe, ann_sem, &trouver);
      if (trouver)
	{
	  trouver = 0;
	  precAction = rechercherAction(&((*precSemaine)->pListeAction), jour_heure, &trouver);

	  if(trouver)
	    {
	      suppressionAction(precAction);
	      if((*precSemaine)->pListeAction == NULL)
		{
		  suppressionSemaine(precSemaine);
		}
	    }
	}
    }
}




void libererListe(semaine_t ** ppSemaine)
{
  while ((*ppSemaine) != NULL)
    {
      while((*ppSemaine)->pListeAction != NULL)
	{
	  suppressionAction(&((*ppSemaine)->pListeAction));
	}
      suppressionSemaine(ppSemaine);
    }
}


