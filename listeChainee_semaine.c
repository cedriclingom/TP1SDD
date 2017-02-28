/*--------------------------------------------------------------------------------------------------*/
/*   listeChaine_semaine.c:  Définition des fonctions permettent de manipuler la liste des semaines */
/*                         et les actions associées à une année, semaine, jour et heure particulière*/
/*                                                                                                  */
/*                                                                                                  */
/*                                                                                                  */
/*--------------------------------------------------------------------------------------------------*/






#include "./listeChainee_semaine.h"








/*--------------------------------------------------------------------------------------------------*/
/* CreerSemaine         Crée la semaine en introduisant dans le bloc alloué l'année et le numéro de *//*                      semaine lu à partir d'un fichier.                                           */
/*                                                                                                  */
/* En entrée:   pSemaine - pointeur sur le bloc alloué pour la semaine                              */
/*                     s - la chaine à introduire dans le bloc                                      */
/*                                                                                                  */
/* En sortie:   Rien en sortie                                                                      */
/*--------------------------------------------------------------------------------------------------*/



void CreerSemaine(semaine_t * pSemaine, char * s)
{
  strcpy(pSemaine->ann_sem,s);

  pSemaine->pListeAction=NULL;

  pSemaine->pSem_suiv=NULL;
}








/*--------------------------------------------------------------------------------------------------*/
/* InsertionCompare       Insère une nouvelle semaine dans la liste des semaines                    */
/*                                                                                                  */
/* En entrée:   ppSemaine - pointeur de pointeur de tete de liste ou pointeur sur la case pointeur  *//*                          de l'élément précédent                                                  */
/*               pSemaine - pointeur sur la semaine à insérer                                       */
/*                                                                                                  */
/* En sortie:   ppSemaine - pointeur de pointeur de tete de liste ou pointeur sur la case pointeur  *//*                          de l'élément précédent                                                  *//*--------------------------------------------------------------------------------------------------*/


 
void InsertionSemaine (semaine_t ** ppSemaine,semaine_t * pSemaine)
{
  pSemaine->pSem_suiv = *ppSemaine;

  *ppSemaine = pSemaine;
}







/*--------------------------------------------------------------------------------------------------*/
/* CreerListe        Cree la liste chainée à deux niveaux triée à partir des lignes lu dans fichier */
/*                                                                                                  */
/* En entrée:   ppTeteListe - pointeur de pointeur de la tete de liste à deux niveaux               */
/*                        f - Fichier à partir du quel on va lire                                   */
/*                                                                                                  */
/* En sortie:   ppTeteListe - pointeur de pointeur de la tete de liste à deux niveaux               */
/*                                                                                                  */
/* Variable(s) locale(s):                                                                           */
/*--------------------------------------------------------------------------------------------------*/
void CreerListe (semaine_t ** ppTeteListe, FILE * f)
{
  int trouver;

  char s1[TAILLE_SEMAINE];

  char s2[TAILLE_JOUR_HR];

  char s3[TAILLE_ACTION];

  semaine_t * pSemaine = NULL, ** precSemaine = NULL;
 
  action_t * pAction = NULL, ** precAction = NULL;
  while (fgets(s1,TAILLE_SEMAINE,f) != NULL)
    {      

      trouver=0;

      if (fgets(s2,TAILLE_JOUR_HR,f) != NULL)
	{
	  precSemaine = rechercherSemaine (ppTeteListe,s1, &trouver);
	  	 
	  if (!(trouver))
	    {

	      pSemaine = allocationSemaine();

	      if (pSemaine != NULL)
		{

		  CreerSemaine (pSemaine,s1);

		  InsertionSemaine(precSemaine,pSemaine);

		}
	    }

	  if (fgets(s3,TAILLE_ACTION,f) != NULL)
	    {

	      trouver = 0;

	      precAction = rechercherAction (&((*precSemaine)->pListeAction), s2, &trouver);

	      if (!(trouver))
		{

		  pAction = allocationAction();

		  if (pAction != NULL)
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
}




/*--------------------------------------------------------------------------------------------------*/
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













int lectureFichier(char * ch, semaine_t ** ppTeteListe)
{
  int codeErr = 1;
  FILE * fTexte = NULL;
  fTexte = fopen(ch,"r");
  if (fTexte != NULL)
    {
      CreerListe (ppTeteListe, fTexte);
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


void afficheSauvegarde()
{
  int tailleChaine =TAILLE_SEMAINE+TAILLE_JOUR_HR+TAILLE_ACTION-3; 
  FILE * f = fopen("./sauvegarde.txt","r");
  char s[TAILLE_SEMAINE+TAILLE_JOUR_HR+TAILLE_ACTION-3];
  char * ch = NULL;
  if (f != NULL)
    {
      ch = fgets(s,tailleChaine, f);
      while (ch != NULL)
	{
	  printf("%s", s);
	  ch = fgets(s,tailleChaine, f);
	}
      fclose(f);
    }
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
      sauvegardeDansFichier(*ppTeteListe);
      printf("Le contenu de la sauvegarde après supression\n");
      afficheSauvegarde();
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


