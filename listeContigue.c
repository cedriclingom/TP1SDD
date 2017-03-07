/*----------------------------------------------------------------------------------------------------------------*/
/*                                                  listeContigue.c                                               */
/*                                                                                                                */
/* Role : Définition des fonctions permettant de créer la liste contigue des jours à partir d'un motif contenu    */
/*        dans une action et la manipulation cette liste contigue.                                                */
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

	  TailleResteAction -= NbCompare+1;

	  decalage += NbCompare+1;

	}
      else
	{
	   TailleResteAction -= NbCompare;

	   decalage += NbCompare;

	}

    }

  return NbCompare;

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
/*                      supprimer et insère ces données année, semaine, jour, heure dans un bloc jour.           */
/*                                                                                                               */
/* En entrée:    pjour - Pointeur sur le bloc alloué.                                                            */
/*               PcodeLecture - Pointeur sur la case qui contient 1 si la lecture c'est bien passé et 0 sinon.   */
/*                                                                                                               */
/* En sortie:    PcodeLecture - Pointeur sur la case contient 1 si la lecture c'est bien passé et 0 sinon.       */
/*---------------------------------------------------------------------------------------------------------------*/


void LectureSemaineJour(jour_t * pjour, int * PcodeLecture)
{

      printf("Le contenu de la sauvegarde avant supression\n");

      AfficheSauvegarde();                                            /*Affiche ce qui était sauvegarder avant la suppression d'une action*/

      do
	{

	  printf("Veuillez entrer l'année et la semaine\n");

	  *PcodeLecture = scanf("%s", pjour->ann_sem);
	  
	  if (*PcodeLecture)                                          /*si la lecture est à marcher*/
	    {
	      
	      printf("Veuillez entrer le jour et l'heure\n");
	      
	      *PcodeLecture = scanf("%s", pjour->jour_heure);         /*j'effectue la deuxième lecture*/
	    }
	}while ((!*PcodeLecture) || ((strlen(pjour->ann_sem) != TAILLE_SEMAINE-1) || (strlen(pjour->jour_heure) != TAILLE_JOUR_HR-1))); /*tantque les chaines lu ne sont pas bonne*/

      if(*PcodeLecture)
	{

	  *PcodeLecture = 1;

	}
      else
	{

	  *PcodeLecture = 0;

	}

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
  
  getchar();

  if (*PcodeLecture)                                               /*si la lecture bien passé*/
    {

      *ppmotif = malloc((TailleMotif+1) * sizeof(char));

      if(*ppmotif != NULL)
	{

	  printf("Veuillez entrer votre motif!\n");

	  if(fgets(*ppmotif,TailleMotif+1,stdin)!= NULL)
	    {

	      *PcodeLecture = 1;

	    }
	  else
	    {
	      
	      *PcodeLecture = 0;

	    }
	  
	}
    }

}








/*------------------------------------------------------------------------------------------------------------*/
/* CreerListeJour          Créer la liste contigue de pointeur vers chaque jour dont l'action contenez un     */
/*                         motif.                                                                             */
/*                                                                                                            */
/* En entrée:    PteteListe - Pointeur de tete de liste chainée des semaines.                                 */
/*                    motif - Chaine caractères qui représente le motif.                                      */
/*                   pdebut - Pointeur de début de liste de contigue de pointeurs de jour.                    */
/*                    ppfin - L'adresse du pointeur de fin de liste contigue dont les éléments sont           */
/*                            des pointeurs de jours.                                                         */
/*                                                                                                            */
/* En sortie:         ppfin - L'adresse du pointeur de fin de liste contigue dont les éléments sont           */
/*                            des pointeurs de jours.                                                         */
/*                                                                                                            */
/* Variable(s) locale(s):       NbElement - Le nombre d'éléments déjà insérer dans la liste contigue.         */
/*                           MotifTrouver - Contient la taille du motif si le motif à été trouvé et 0 si le   */
/*                                          motif n'a pas été trouvé.                                         */
/*                            TailleMotif - La taille du motif.                                               */
/*------------------------------------------------------------------------------------------------------------*/


void CreerListeJour(semaine_t * PteteListe, char * motif, jour_t ** pdebut, jour_t *** ppfin)
{
  int NbElement = 0, MotifTrouver = 0, TailleMotif = strlen(motif);

  semaine_t * pcour1 = PteteListe;                   /*initialise à la tete de liste des semaines*/

  action_t * pcour2 = NULL;

  jour_t * pjour = NULL;

  *ppfin = NULL;

  while ((NbElement < TAILLE_MAX) && (pcour1 != NULL))   /*tanque je peux insérer dans ma liste contigue et je suis dans la liste des semaines*/
    {
      pcour2 = pcour1->PlisteAction;                 /*initialise à la tete de liste des actions associé à cette semaine*/

      while((NbElement < TAILLE_MAX) && (pcour2 != NULL))/*tanque je peux insérer dans ma liste contigue et je suis dans la liste des actions*/
	{

	  MotifTrouver = RechercherMotif(pcour2->nom_action,motif); /*recherche le motif dans l'action courante*/

	  if(MotifTrouver == TailleMotif)
	    {

	      pjour = AllocationJour();

	      if (pjour != NULL)
		{

		  CreerJour(pjour, pcour1, pcour2);

		  if(*ppfin != NULL)                                 /*si j'ai insérer dans la liste contigue au moins un élément*/
		    {

		      *ppfin = *ppfin + 1;

		    }
		  else                                               /* si j'insère le premier élément de la liste contigue*/
		    {

		      *ppfin = pdebut;
           
		    }

		  InsererJour(pdebut, pjour, NbElement);              /* insère le jour dans la liste contigue*/

		  ++NbElement;

		}

	    }

	  pcour2 = pcour2->paction_suiv;                             /*passe à l'action suivante*/

	}

      pcour1 = pcour1->psem_suiv;                                    /*passe à la seamines suivante*/

    }

}








/*----------------------------------------------------------------------------------------------------------------*/
/* AfficherListeContigue          Affiche la liste contigue de jours.                                             */
/*                                                                                                                */
/* En entrée:   pdebut - Pointeur de début de liste de contigue de pointeurs de jour.                             */
/*                pfin - Pointeur de fin de liste contigue dont les éléments sont des pointeurs de jours.         */
/*                                                                                                                */
/* En sortie:   Rien en sortie.                                                                                   */
/*                                                                                                                */
/* Variable(s) locale(s):    i, j - Varieble servant d'indice dans le tableau.                                    */
/*                           prec - Pointeur de pointeur de l'élément précédent.                                  */
/*----------------------------------------------------------------------------------------------------------------*/

            
void AfficherListeContigue(jour_t ** pdebut, jour_t ** pfin)
{

  int i=0, j=0;

  jour_t ** prec=NULL;

  if (pfin != NULL)                                                                     /*si la liste est non vide*/
    {

      prec = pdebut;                                                                    /*initialise le précédent au premier élément*/
      
      printf("\nLes jours et heures associés à chaque semaine des actions ayant se motifs sont:\n");
 
      printf("%s\n", pdebut[i]->ann_sem);                                               /*affiche l'année et semaine courante*/

      while ((pdebut + i) <= pfin)                                                      /*tanque qu'on dans la liste contigue*/
	{

	  while(((pdebut + i) <= pfin) && !strcmp(pdebut[i]->ann_sem, prec[j]->ann_sem))/*tantque qu'on est dans la liste contigue et que l'année et la semaine du précédent et courant sont égaux*/
	  {

	    printf("\t%s\n", pdebut[i]->jour_heure);                                    /*afficher juste le jour et l'heure*/

	    ++i;

	  }
	if (((pdebut + i) <= pfin) && strcmp(pdebut[i]->ann_sem, prec[j]->ann_sem))     /*si on est dans la liste contigue et que l'année et la semaine du précédent et courant sont différents*/
	  {

	    printf("\n%s\n", pdebut[i]->ann_sem);                                       /*affiche l'année et la semaine courante*/

	    printf("\t%s\n", pdebut[i]->jour_heure);                                    /*affiche le jour et l'heure*/

	    j=i;                                                                       

	    ++i;

	  }
      
	}

    }

}








/*------------------------------------------------------------------------------------------------------------*/
/* LibererListeContigue          Libère la liste contigue.                                                    */
/*                                                                                                            */
/* En entrée:    ppdebut - L'adresse du pointeur de tete de liste contigue.                                   */
/*                 ppfin - L'adresse du pointeur de fin de liste contigue.                                    */
/*                                                                                                            */
/* En sortie:    ppdebut - L'adresse du pointeur de tete de liste contigue.                                   */
/*                 ppfin - L'adresse du pointeur de fin de liste contigue.                                    */
/*                                                                                                            */
/* Variable(s) locale(s):    i - Variable servant d'indicage.                                                 */
/*------------------------------------------------------------------------------------------------------------*/

 
void LibererListeContigue(jour_t *** ppdebut, jour_t *** ppfin)
{

  int i=0;

  if(*ppfin != NULL)                                       /*si liste non vide*/
    {

      while ((*ppdebut+i) < *ppfin)                        /*tantque je ne suis pas à la fin de la liste*/
	{

	  free((*ppdebut)[i]);

	  ++i;

	}
      free((*ppdebut)[i]);

    }

  free(*ppdebut);

  *ppdebut = NULL;

  *ppfin = NULL;

}
