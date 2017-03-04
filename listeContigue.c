/*----------------------------------------------------------------------------------------------------------------*/
/* listeContigue.c:    Définition des fonctions permettant de créer la liste contigue des jours à partir d'un     */
/*                     motif contenu dans une action et la manipulation cette liste contigue.                     */
/*----------------------------------------------------------------------------------------------------------------*/







#include "./listeContigue.h"








/*-----------------------------------------------------------------------------------------------------------------*/
/* CompareChaineN    Compare deux chaine de caractères.                                                            */
/*                                                                                                                 */
/* En entrée:    s1, s2 - Deux chaines de caractères.                                                              */
/*               taille - la taille des deux chaine de caractères.                                                 */
/*                                                                                                                 */
/* En sortie:    Retourne une valeur entière taille si les deux chaines de caractères sont égaux et une valeur     */
/*               strictement inférieur à taille s'ils sont différent.                                              */
/*                                                                                                                 */
/* Variable(s) locale(s):    i - variable de boucle.                                                               */
/*-----------------------------------------------------------------------------------------------------------------*/


int CompareChaine(char * s1, char * s2, int taille)
{

  int i=0;

  while ((i<taille) && (s1[i] == s2[i]))
    {

      ++i;

    }

  return i;

}








/*---------------------------------------------------------------------------------------------------------------*/
/* RechercherMotif    Recherche un motif dans une action.                                                        */
/*                                                                                                               */
/* En entrée:   NomAction - Chaine de caractères contenant le nom de l'action.                                   */
/*                  motif - Chaine de caractères contenant le motif.                                             */
/*                                                                                                               */
/* En sortie:   Retourne la taille du motif si sa trouve le motif et un une valeur strictement inférieur à la    */
/*              taille du motif si on trouve pas le motif.                                                       */
/*                                                                                                               */
/* Variable(s) locale(s):           TailleMotif - La taille du motif.                                            */
/*                                    NbCompare - Le nombre de caractères du motif comparé.                      */
/*                                     decalage - Décalage paraport au premier caractère de l'action.            */
/*                            TailleResteAction - Le reste de la chaine action dans le quel on doit rechercher   */
/*                                                le motif.                                                      */
/*---------------------------------------------------------------------------------------------------------------*/


int RechercherMotif(char * NomAction, char * motif)
{
  int TailleMotif = strlen(motif),NbCompare = 0, decalage=0, TailleResteAction = (TAILLE_ACTION-2);
  
  while ((TailleMotif <= TailleResteAction) && (NbCompare < TailleMotif))             /* tantque je peux encore rechercher le motif*/
    {
      
      NbCompare = CompareChaine(NomAction+decalage, motif, TailleMotif);

      if (!NbCompare)                                                                 /*si le premier caractère du motif n'est pas trouver*/
	{

	  tailleResteAction -= nbCompare+1;

	  decalage += nbCompare+1;

	}
      else
	{
	   tailleResteAction -= nbCompare;

	   decalage += nbCompare;

	}

    }

  return nbCompare;

}








/*---------------------------------------------------------------------------------------------------------------*/
/* AllocationListeContigue  Allocation d'un tableau de pointeur de jour.                                         */
/*                                                                                                               */
/* En entrée:    Rien en entrée.                                                                                 */
/*                                                                                                               */
/* En sortie:    Retourne l'adresse du tableau alloué.                                                           */
/*                                                                                                               */
/* Variable(s) locale(s):    tab - Pointeur de tableau de pointeurs de jours.                                    */
/*---------------------------------------------------------------------------------------------------------------*/


jour_t ** AllocationListeContigue()
{
  jour_t ** tab = (jour_t **)malloc(TAILLE_MAX *sizeof(jour_t *));

  return tab;

}









/*---------------------------------------------------------------------------------------------------------------*/
/* AllocationJour   Allocation d'un bloc jour.                                                                   */
/*                                                                                                               */
/* En entrée:    Rien en entrée.                                                                                 */
/*                                                                                                               */
/* En sortie:    Retourne l'adresse du bloc alloué.                                                              */
/*                                                                                                               */
/* Variable(s) locale(s):    pjour - Pointeur sur le bloc alloué.                                                */
/*---------------------------------------------------------------------------------------------------------------*/


jour_t * AllocationJour()
{
  jour_t * pjour = (jour_t *)malloc(sizeof(jour_t));

  return pjour;

}








/*---------------------------------------------------------------------------------------------------------------*/
/* LectureSemaineJour   Permet de lire au clavier l'année, la semaine, le jour, l'heure de l'action qui sera     */
/*                      supprimer.                                                                               */
/*                                                                                                               */
/* En entrée:    Rien en entrée.                                                                                 */
/*                                                                                                               */
/* En sortie:    Retourne l'adresse du bloc jour contenant comme données année, semaine, jour et heure alloué.   */
/*                                                                                                               */
/* Variable(s) locale(s):    pjour - Pointeur sur le bloc alloué.                                                */
/*---------------------------------------------------------------------------------------------------------------*/


jour_t * LectureSemaineJour()
{
  jour_t * pjour= allocationJour();

  if(pjour != NULL)
    {

      printf("Le contenu de la sauvegarde avant supression\n");

      AfficheSauvegarde();                                            /*Affiche ce qui était sauvegarder avant la suppression d'une action*/

      do
	{

	  printf("Veuillez entrer l'année et la semaine\n");

	  scanf("%s", pjour->ann_sem);

	  printf("Veuillez entrer le jour et l'heure\n");

	  scanf("%s", pjour->jour_heure);

	}while ((strlen(pjour->ann_sem) != TAILLE_SEMAINE-1) || (strlen(pjour->jour_heure) != TAILLE_JOUR_HR-1)); /*tantque les chaines lu ne sont pas bonne*/

    }

  return pjour;

}

/*-------------------------------------------------------------------------------------------------------------------*/
/* CreerJour         Creer un bloc jour connaissant l'année, la semaine, le jour et l'heure.                         */
/*                                                                                                                   */
/* En entrée:       pjour - Pointeur sur le bloc jour.                                                               */
/*               psemaine - Pointeur sur la seamine.                                                                 */
/*                paction - Pointeur sur l'action.                                                                   */
/*                                                                                                                   */
/* En sortie:       pjour - Pointeur sur le bloc jour.                                                               */
/*-------------------------------------------------------------------------------------------------------------------*/


void CreerJour(jour_t * pjour, semaine_t * psemaine, action_t * paction)
{

  strcpy(pjour->ann_sem, psemaine->ann_sem);

  strcpy(pjour->jour_heure, paction->jour_heure);

}








/*-------------------------------------------------------------------------------------------------------------------*/
/* InsererJour         Insère un bloc jour dans la liste contigue des pointeur de bloc jour à indice donné.          */
/*                                                                                                                   */
/* En entrée:   pdebut - Pointeur de début de liste de contigue de pointeurs de jour.                                */
/*               pjour - Pointeur sur le bloc jour.                                                                  */
/*              indice - Indice à la qu'elle je dois insérer dans la liste contigue.                                 */
/*                                                                                                                   */
/* En sortie:    Rien en sortie.                                                                                     */
/*-------------------------------------------------------------------------------------------------------------------*/


void InsererJour(jour_t ** pdebut,jour_t * pjour,int indice)
{

  pdebut[indice] = pjour;

}








/*---------------------------------------------------------------------------------------------------------------*/
/* LectureMotif          Permet de lire au clavier d'un motif.                                                   */
/*                                                                                                               */
/* En entrée:    ppmotif - Pointeur de pointeur sur le motif.                                                    */
/*               PcodeLecture - Pointeur sur la case contenant le code de lecture c'est-à-dire 1 si la lecture   */
/*                              c'est bien passé et 0 sinon.                                                     */
/*                                                                                                               */
/* En sortie:    ppmotif - Pointeur de pointeur sur le motif.                                                    */
/*               PcodeLecture - Pointeur sur la case contenant le code de lecture c'est-à-dire 1 si la lecture   */
/*                              c'est bien passé et 0 sinon.                                                     */
/*                                                                                                               */
/* Variable(s) locale(s):    TailleMotif - La taille du motif.                                                   */
/*---------------------------------------------------------------------------------------------------------------*/


void LectureMotif(char ** ppmotif, int * PcodeLecture)
{
  int TailleMotif;

  printf("Veuillez entrer la taille du motif!\n");

  *PcodeLecture = scanf("%d",&TailleMotif);
  
  if (*PcodeLecture)
    {

      *ppmotif = malloc((TailleMotif+1) * sizeof(char));

      if(*ppmotif != NULL)
	{

	  printf("Veuillez entrer votre motif!\n");

	  *PcodeLecture = scanf("%s",*ppmotif);
	  
	}
    }
  if(*PcodeLecture)
    {

      *PcodeLecture = 1;

    }
  else
    {

      *PcodeLecture = 0;

    }

}

void creerListeJour(semaine_t * pTeteListe, char * motif, jour_t ** pDebut, jour_t *** ppFin)
{
  semaine_t * pcour1 = pTeteListe;
  action_t * pcour2 = NULL;
  jour_t * pJour = NULL;
  int nbElm=0, motifTrouver=0,tailleMotif=strlen(motif);
  *ppFin = NULL;
  while ((nbElm < TAILLE_MAX) && (pcour1 != NULL))
    {
      pcour2 = pcour1->PlisteAction;
      while((nbElm < TAILLE_MAX) && (pcour2 != NULL))
	{
	  motifTrouver = rechercherMotif(pcour2->nom_action,motif);
	  if(motifTrouver == tailleMotif)
	    {
	      pJour = allocationJour();
	      if (pJour != NULL)
		{
		  creerJour(pJour, pcour1, pcour2);
		  if(*ppFin != NULL)
		    {
		      *ppFin = *ppFin + 1;
		    }
		  else
		    {
		      *ppFin = pDebut;
		    }
		  insererJour(pDebut,pJour, nbElm);
		  ++nbElm;
		}
	    }
	  pcour2 = pcour2->paction_suiv;
	}
      pcour1 = pcour1->psem_suiv;
    }
}


void afficherListeContigue(jour_t ** pDebut, jour_t **pFin)
{
  int i=0, j=0;
  jour_t ** pcour=pDebut, ** pprec=NULL;
  if (pFin != NULL)
    {
      pprec = pcour;
      printf("%s\n", pcour[i]->ann_sem);
      while ((pcour + i) <= pFin){
	while(((pcour + i) <= pFin) && !strcmp(pcour[i]->ann_sem, pprec[j]->ann_sem))
	  {
	    printf("\t%s\n",pcour[i]->jour_heure);
	    ++i;
	  }
	if (((pcour + i) <= pFin) && strcmp(pcour[i]->ann_sem, pprec[j]->ann_sem))
	  {
	    printf("\n%s\n", pcour[i]->ann_sem);
	    printf("\t%s\n", pcour[i]->jour_heure);
	    j=i;
	    ++i;
	  }
      }
    }
}



void libererListeContigue(jour_t ** pDebut, jour_t ** pFin)
{
  int i=0;
  if(pFin != NULL)
    {
      while ((pDebut+i) < pFin)
	{
	  free(pDebut[i]);
	  ++i;
	}
      free(pDebut[i]);
    }
  free(pDebut);
}
