/*---------------------------------------------------------------------------------------------------------------------------*/
/*   listeChaine_semaine.c:  Définition des fonctions permettent de manipuler la listeChainée des semaines                   */
/*                           et les actions associées à une année, semaine, jour et heure particulière.                      */
/*                                                                                                                           */
/*                                                                                                                           */
/*                                                                                                                           */
/*---------------------------------------------------------------------------------------------------------------------------*/






#include "./listeChainee_semaine.h"









/*------------------------------------------------------------------------------------------------------------------*/
/* AllocationSemaine         Alloue un bloc semaine où sera stocker la semaine.                                     */
/*                                                                                                                  */
/* En entrée:   Rien en Entrée                                                                                      */
/*                                                                                                                  */
/* En sortie:   On retourne l'adresse du bloc semaine alloué.                                                       */
/*                                                                                                                  */
/* Variable(s) locale(s):   psemaine - Pointeur sur le bloc alloué.                                                 */
/*------------------------------------------------------------------------------------------------------------------*/


semaine_t * AllocationSemaine()
{
  semaine_t * psemaine = (semaine_t *)malloc(sizeof(semaine_t));

  return psemaine;
}









/*---------------------------------------------------------------------------------------------------------------------------*/
/* CreerSemaine         Crée la semaine en introduisant dans le bloc alloué l'année et le numéro de                          */
/*                      semaine lu à partir d'un fichier.                                                                    */
/*                                                                                                                           */
/* En entrée:   psemaine - Pointeur sur le bloc alloué pour la semaine.                                                      */
/*                     s - La chaine à introduire dans le bloc.                                                              */
/*                                                                                                                           */
/* En sortie:   Rien en sortie                                                                                               */
/*---------------------------------------------------------------------------------------------------------------------------*/


void CreerSemaine(semaine_t * psemaine, char * s)
{
  strcpy(psemaine->ann_sem,s);

  psemaine->PlisteAction=NULL;

  psemaine->psem_suiv=NULL;
}








/*------------------------------------------------------------------------------------------------------------------------*/
/* InsertionCompare       Insère une nouvelle semaine dans la liste chainée des semaines.                                 */
/*                                                                                                                        */
/* En entrée:   ppsemaine - Pointeur de pointeur de tete de liste chainée des semaines ou pointeur sur la case pointeur   */
/*                          de l'élément précédent.                                                                       */
/*               psemaine - Pointeur sur la semaine à insérer.                                                            */
/*                                                                                                                        */
/* En sortie:   ppsemaine - Pointeur de pointeur de tete de liste chainée des semaines ou pointeur sur la case pointeur   */
/*                          de l'élément précédent.                                                                       */
/*------------------------------------------------------------------------------------------------------------------------*/

 
void InsertionSemaine (semaine_t ** ppsemaine,semaine_t * psemaine)
{
  psemaine->psem_suiv = *ppsemaine;

  *ppsemaine = psemaine;
}







/*---------------------------------------------------------------------------------------------------------------*/
/* SupressionSemaine          Supprime une semaine de liste chainée des semaines.                                */
/*                                                                                                               */
/* En entrée:    ppsemaine -  Pointeur de pointeur de tete de liste chainée des semaines ou pointeur sur la case */
/*                            pointeur de l'élément précédent de la liste chainée des semaines.                  */
/*                                                                                                               */
/* En sortie:    ppsemaine -  Pointeur de pointeur de tete de liste chainée des semaines ou pointeur sur la case */
/*                            pointeur de l'élément précédent de la liste chainée des semaines.                  */
/*                                                                                                               */
/* Variable(s) locale(s):    psemaine - Pointeur sur la semaine à supprimer.                                     */
/*---------------------------------------------------------------------------------------------------------------*/


void SuppressionSemaine(semaine_t ** ppsemaine)
{
  semaine_t * psemaine = *ppsemaine;                          /*recupère l'adresse de la semaine à supprimer*/

  *ppsemaine = psemaine->psem_suiv;                           /*la semaine précédente pointe sur la semaine après la semaine à supprimer*/

  free(psemaine);                                             /*supprime la semaine*/

  psemaine=NULL;

}








/*------------------------------------------------------------------------------------------------------------------------*/
/* LibererListe               Libère toute la liste à deux niveau.                                                        */
/*                                                                                                                        */
/* En entrée:  ppsemaine - Pointeur de pointeur de tete de liste chainée.                                                 */
/*                                                                                                                        */
/* En sortie:  ppsemaine - Pointeur de pointeur de tete de liste chainée.                                                 */
/*------------------------------------------------------------------------------------------------------------------------*/


void LibererListe(semaine_t ** ppsemaine)
{

  while ((*ppsemaine) != NULL)                                /*libère la liste chainée des semaines*/
    {

      while((*ppsemaine)->PlisteAction != NULL)
	{

	  suppressionAction(&((*ppsemaine)->PlisteAction));   /*libère la liste chainée des actions associés à chaque semaine*/

	}
      SuppressionSemaine(ppsemaine);

    }
}







/*-------------------------------------------------------------------------------------------------------------------------*/
/* RechercherSemaine        Recherche une semaine dans la liste chainée des semaines.                                      */
/*                                                                                                                         */
/* En entrée:   PpteteListe - Pointeur sur la tête de la liste chainée des semaines.                                       */
/*                      pprec - Pointeur de pointeur de tete de la liste chainée des semaines ou pointeur sur la case      */
/*                              d'élément précédent dans la liste chainée de semaines.                                     */
/*                    pvaleur - Pointeur sur la semaine à rechercher (qui est une chaine de caractères).                   */
/*                   ptrouver - Pointeur sur une case mémoire contenant 0 si on a pas trouvé ou 1 si on a trouvé la chaine */
/*                                                                                                                         */
/* En sortie:           pprec - Retourne l'adresse du pointeur de tete de liste chainée des semaines ou l'adresse de la    */
/*                              case pointeur de l'élément précédent dans la liste chainée de semaines.                    */
/*                   ptrouver - Pointeur sur une case mémoire contenant 0 si on a pas trouvé l'élément ou 1 si on a trouvé */
/*                              dans la liste chainée des semaines.                                                        */
/*                                                                                                                         */
/* Variable(s) locale(s):   pcour - Pointeur sur la semaine courante.                                                      */
/*                          prec  - Pointeur de pointeur de tete de liste chainée des semaines ou pointeur sur la case     */
/*                                  pointeur de l'élément précédent de la liste chainée des semaines.                      */
/*-------------------------------------------------------------------------------------------------------------------------*/


semaine_t **  RechercherSemaine (semaine_t ** PpteteListe,char * pvaleur, int * ptrouver)
{
  semaine_t * pcour = *PpteteListe, ** prec = PpteteListe;           /*Initialisation à la première semaine et au pointeur de tete*/

  *ptrouver = 0;

  while   ((pcour != NULL) && (strcmp(pvaleur, pcour->ann_sem) > 0)) /*Tantque je suis dans la liste et que ma chaine est plus grande*/
    {
      
      prec = &(pcour->psem_suiv);                                    /*On récupère l'adresse de la case pointeur de l'élément précédent*/
      
      pcour = *prec;                                                 /*Passe au suivant*/
      
    }

  if ((pcour != NULL) && (!strcmp(pvaleur, pcour->ann_sem)))         /*Si on trouve la chaine*/
    {

      *ptrouver=1;

    }

  return prec;
}









/*-------------------------------------------------------------------------------------------------------------------------*/
/* CreerListe        Cree la liste chainée à deux niveaux triée à partir des lignes lu dans fichier.                       */
/*                                                                                                                         */
/* En entrée:   PpteteListe - Pointeur de pointeur de la tete de liste à deux niveaux.                                     */
/*                        f - Fichier à partir du quel on va lire.                                                         */
/*                                                                                                                         */
/* En sortie:   PpteteListe - Pointeur de pointeur de la tete de liste à deux niveaux.                                     */
/*                                                                                                                         */
/* Variable(s) locale(s):         trouver - Permet de dire si on a trouver l'élément qu'on recherche ou pas.               */
/*                                     s1 - Tableau de caractère qui va contenir l'année et semaine                        */
/*                                          lu à partir du fichier.                                                        */
/*                                     s2 - Tableau de caractère qui va contenir le jour et l'heure                        */
/*                                          lu à partir du fichier.                                                        */
/*                                     s3 - Tableau de caractères qui va contenir l'action lu à                            */
/*                                          partir du fichier.                                                             */
/*                               psemaine - Pointeur sur la semaine à insérer.                                             */
/*                            PrecSemaine - Pointeur de pointeur de tete de liste des semaines ou pointeur sur la          */
/*                                          case pointeur de l'élément précédent de la liste des semaines.                 */
/*                                paction - Pointeur sur l'action à insérer.                                               */
/*                             PrecAction - Pointeur de pointeur de tete de liste des actions ou pointeur sur la           */
/*                                          case pointeur de l'élément précédent de la liste des actions.                  */
/*                                                                                                                         */
/*-------------------------------------------------------------------------------------------------------------------------*/


void CreerListe (semaine_t ** PpteteListe, FILE * f)
{
  int trouver;

  char s1[TAILLE_SEMAINE];

  char s2[TAILLE_JOUR_HR];

  char s3[TAILLE_ACTION];

  semaine_t * psemaine = NULL, ** PrecSemaine = NULL;
 
  action_t * paction = NULL, ** PrecAction = NULL;

  while (fgets(s1,TAILLE_SEMAINE,f) != NULL)                           /*Test si je ne suis pas à la fin du fichier*/
    {      

      trouver=0;

      if (fgets(s2,TAILLE_JOUR_HR,f) != NULL)
	{
	  PrecSemaine = RechercherSemaine (PpteteListe,s1, &trouver);
	  	 
	  if (!(trouver))                                             /*Si j'ai pas trouver la semaine rechercher*/
	    {

	      psemaine = AllocationSemaine();

	      if (psemaine != NULL)                                   /* Vérifie si l'allocation semaine c'est bien passé*/
		{

		  CreerSemaine (psemaine,s1);

		  InsertionSemaine(PrecSemaine,psemaine);

		}
	    }

	  if (fgets(s3,TAILLE_ACTION,f) != NULL)
	    {

	      trouver = 0;

	      PrecAction = rechercherAction (&((*PrecSemaine)->PlisteAction), s2, &trouver);

	      if (!(trouver))                                             /*Si j'ai trouver l'action rechercher*/
		{

		  paction = allocationAction();

		  if (paction != NULL)                                    /*Vérifier si l'allocation de l'action c'est bien passé*/
		    {

		      creerAction (paction, s2, s3);

		      insertionAction(PrecAction, paction);

		    }
		  else
		    {

			  LibererListe(PpteteListe);

		    }
		}
	    }
	}
    }
}










/********************************************************************************************************************/
/* LectureFichier           Lire chaque ligne de notre fichier qui contient comme données année, semaine, jour,     */
/*                          heure et créer une liste chainée à deux niveaux à partir de cette lecture.              */
/*                                                                                                                  */
/* En entrée:     NomFichier - Nom du fichier dans le quel on va lire.                                              */
/*               PpteteListe - Pointeur de pointeur de tete de liste chainée des semaines.                          */
/*              PcodeLecture - Pointeur sur la case contenant le code de lecture c'est-à-dire 1 si la lecture c'est */
/*                             bien passé et 0 sinon.                                                               */
/*                                                                                                                  */
/* En sortie:    PpteteListe - Pointeur de pointeur de tete de liste chainée des semaines.                          */
/*              PcodeLecture - Pointeur sur la case contenant le code de lecture c'est-à-dire 1 si la lecture c'est */
/*                             bien passé et 0 sinon.                                                               */
/*                                                                                                                  */
/* Variable(s) locale(s):  f - Pointeur sur le fichier.                                                             */
/*------------------------------------------------------------------------------------------------------------------*/  

   
void LectureFichier(char * NomFichier, semaine_t ** PpteteListe, int * PcodeLecture)
{

  FILE * f = NULL;

  f = fopen(NomFichier,"r");

  if (f != NULL)
    {

      CreerListe(PpteteListe, f);                            /*Créer la liste à deux niveaux.*/

      fclose(f);

    }
  else                                                       /*Si la lecture ne s'est pas bien passé*/
    {

      *PcodeLecture = 0; 
                                  
    }
}








/*-------------------------------------------------------------------------------------------------------------------*/
/* SauvergardeDansFichier         Sauvegarde de la liste chainée à deux niveaux triée dans un fichier.               */
/*                                                                                                                   */
/* En entree:         PteteListe - Pointeur de tete de liste chainées des semaines.                                  */
/*               PcodeSauvegarde - Pointeur sur la case contenant le code de sauvegarde qui vaut 1 c'est-à-dire la   */
/*                                 sauvgarde est supposer vrai en entrée                                             */
/*                                                                                                                   */
/* En sortie:    PcodeSauvegarde - Pointeur sur la case contenant le code de sauvegarde c'est-à-dire 1 si la         */
/*                                 sauvgarde c'est bien passer et 0 sinon.                                           */
/*                                                                                                                   */
/* Variable(s) locale(s):   pcour1 - Pointeur sur la semaine courante.                                               */
/*                          pcour2 - Pointeur sur l'action courante.                                                 */
/*                               f - Pointeur sur le fichier de sauvegarde.                                          */
/*-------------------------------------------------------------------------------------------------------------------*/


void SauvegardeDansFichier(semaine_t * PteteListe, int * PcodeSauvegarde)
{

  semaine_t * pcour1 = PteteListe;

  action_t *pcour2;

  FILE * f = fopen("sauvegarde.txt","w");

  if(f != NULL)
    {

      while(pcour1 != NULL)                                                                /*tantque je suis dans la liste des semaines*/
	{
	  
	  pcour2 = pcour1->PlisteAction;
	  
	  while   (pcour2 != NULL)                                                         /*tantque je suis dans la liste d'actions*/
	    {

	      fprintf(f,"%s%s%s", pcour1->ann_sem, pcour2->jour_heure, pcour2->nom_action);

	      pcour2 = pcour2->pAction_suiv;                                               /*passe à l'action suivante*/
	      
	    }

	  pcour1 = pcour1->psem_suiv;                                                      /*passe à la semaine suivante*/
	  
	}

      fclose(f);
    }
  else
    {

      *PcodeSauvegarde = 0;

    }
}









/*------------------------------------------------------------------------------------------------------------------*/
/* AfficheSauvegarde   Affiche les année, semaine, jour, heure et action qui ont été sauvegarder.                   */
/*                                                                                                                  */
/* En entrée:    Rien en entrée.                                                                                    */
/*                                                                                                                  */
/* En sortie:    Rien en sortie.                                                                                    */
/*                                                                                                                  */
/* Variable(s) locale(s):    TailleChaine - Taille de chaine de carctères qui représente celle de la ligne lu dans  */
/*                                          le fichier.                                                             */
/*                                 chaine - Tableau de caractères.                                                  */
/*                                      f - Pointeur sur le fichier de sauvegarde.                                  */
/*------------------------------------------------------------------------------------------------------------------*/


void AfficheSauvegarde()
{
  int TailleChaine = TAILLE_SEMAINE+TAILLE_JOUR_HR+TAILLE_ACTION-3;
 
  char chaine[TAILLE_SEMAINE+TAILLE_JOUR_HR+TAILLE_ACTION-3];   /*permet de récupérer chaque ligne du fichier*/

  FILE * f = fopen("./sauvegarde.txt","r");
  
  if(f != NULL)
    {

      while (fgets(chaine,TailleChaine, f) != NULL)             /*tantque je ne suis pas à la fin du fichier*/
	{

	  printf("%s", chaine);

	}

      fclose(f);

    }
}

  







/*---------------------------------------------------------------------------------------------------------------*/
/* supression         Supprime une action connaissant l'année, la semaine, le jour et l'heure.                   */
/*                                                                                                               */
/* En entrée:    PpteteListe - Pointeur de pointeur de tete de la liste chainée à deux niveaux.                  */
/*                   ann_sem - Pointeur sur la chaine de caractères qui contiendra l'année et la semaine.        */
/*                jour_heure - Pointeur sur la chaine de caractères qui contiendra le jour et l'heure.           */
/*                                                                                                               */
/* En sortie:    PpteteListe - Pointeur de pointeur de tete de la liste chainée à deux niveaux.                  */
/*                                                                                                               */
/* Variable(s) locale(s):   PrecSemaine - Pointeur de pointeur de tete de liste des semaines ou pointeur sur la  */
/*                                        case pointeur de l'élément précédent de la liste des semaines.         */
/*                           PrecAction - Pointeur de pointeur de tete de liste des semaines ou pointeur sur la  */
/*                                        case pointeur de l'élément précédent de la liste des semaines.         */
/*---------------------------------------------------------------------------------------------------------------*/


void supression(semaine_t ** PpteteListe, char * ann_sem, char * jour_heure)
{
  int trouver, CodeSauvegarde = 0;

  semaine_t ** PrecSemaine = NULL;

  action_t ** PrecAction =NULL;

  if(*PpteteListe != NULL)                                                                       /*si liste chainée des semaines non vide*/
    {

      PrecSemaine = RechercherSemaine(PpteteListe, ann_sem, &trouver);

      if (trouver)                                                                               /* si j'ai trouver la semaine rechercher*/
	{

	  trouver = 0;

	  PrecAction = rechercherAction(&((*PrecSemaine)->PlisteAction), jour_heure, &trouver);

	  if(trouver)                                                                            /* si j'ai trouver l'action rechercher*/
	    {

	      suppressionAction(PrecAction);

	      if((*PrecSemaine)->PlisteAction == NULL)
		{

		  SuppressionSemaine(PrecSemaine);

		}
	    }
	}

      SauvegardeDansFichier(*PpteteListe, &CodeSauvegarde);                                     /*sauvegarde après suppression*/

      printf("Le contenu de la sauvegarde après supression\n");

      AfficheSauvegarde();                                                                      /*Affiche la nouvelle sauvegarde*/

    }
}







