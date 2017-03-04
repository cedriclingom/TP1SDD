/*-------------------------------------------------------------------------------------------------------------*/
/*                                                 Main                                                        */
/*                                                                                                             */
/* Role:   Fichier de notre fonction principal faisant appelle à tout les toutes les fonctions nécéssaires     */
/*         au traiment en ce qui concern:                                                                      */
/*                                                                                                             */
/*               -Création d'une liste chaine à deux niveaux triée à partir de la lecture dans un fichier.     */
/*                                                                                                             */
/*               -Sauvegarde dans un fichier la liste chainée et création d'une liste contigue de bloc de jour */
/*                ayant comme anée, semaine, jour, heure de l'action contenant le motif rechercher.            */
/*                                                                                                             */
/*               -Suppression d'une action connaissant le l'anée, la semaine, le jour et l'heure.              */
/*-------------------------------------------------------------------------------------------------------------*/





#include "./listeContigue.h"





int main (int argc, char ** argv)
{

  int choix, CodeLecture = 1, CodeSauvegarde = 1;

  char * pmotif = NULL;

  semaine_t * PteteAgenda = NULL;

  jour_t ** PteteListeContigue = NULL, ** PfinListeContigue=NULL, * pjour = NULL;

  if (argc == 2)
    {

      LectureFichier(argv[1], &PteteAgenda, &CodeLecture);

      printf("Veuillez choisir l'opération à faire!\n");

      printf("1. Creer la liste à deux niveaux et sauvegarder\n");

      printf("2. Creer la liste contigue des jours des actions contenant un motif\n");

      printf("3. Supprimer une action.\n");

      scanf("%d", &choix);

      switch(choix)
	{

	case 1:

	  if (CodeLecture)                                      /*si lecture à partir fichier entrée en ligne de commande c'est bien passé*/
	    {

	      SauvegardeDansFichier(PteteAgenda, &CodeSauvegarde); /*sauvegarde liste à deux niveau dans un fichier de sauvegarde*/

	    }

	  break;

	case 2:

	  if (CodeLecture)                                      /*si lecture à partir fichier entrée en ligne de commande c'est bien passé*/
	    {

	      PteteListeContigue = AllocationListeContigue();
	       
	      CodeLecture = 1;

	      LectureMotif(&pmotif, &CodeLecture);

	      if ((PteteListeContigue != NULL) && CodeLecture)
		{

		  CreerListeJour(PteteAgenda, pmotif, PteteListeContigue, &PfinListeContigue);

		  AfficherListeContigue(PteteListeContigue, PfinListeContigue);

		  LibererListeContigue(&PteteListeContigue, &PfinListeContigue);

		  free(pmotif);

		}
	    }

	  break;

	case 3:

	  if (CodeLecture)                                      /*si lecture à partir fichier entrée en ligne de commande c'est bien passé*/
	    {

	      SauvegardeDansFichier(PteteAgenda, &CodeSauvegarde);

	      pjour = AllocationJour();
	       
	      if(pjour != NULL)
		{

		  LectureSemaineJour(pjour, &CodeLecture);     /*lit année, semaine, jour, heure de l'action à supprimer*/
		   
		  if(CodeLecture)                              /*si la lecture c'est bien passé*/
		    {

		      supression(&PteteAgenda,pjour->ann_sem, pjour->jour_heure);   /*je supprime l'action*/
		       
		      free(pjour);

		    }

		}

	    }

	}

      LibererListe(&PteteAgenda);
      
    }

  return 0;

}
