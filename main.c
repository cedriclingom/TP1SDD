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

      printf("2. Creer la liste contigue des jours contenant un motif\n");

      printf("3. Supprimer une action\n");

      scanf("%d", &choix);

      switch(choix)
	{

	case 1:

	   if (CodeLecture)
	     {

	       SauvegardeDansFichier(PteteAgenda, &CodeSauvegarde);

	     }

	   break;

	case 2:

	  if (CodeLecture)
	     {

	       PteteListeContigue = AllocationListeContigue();
	       
	       CodeLecture = 1;

	       LectureMotif(&pmotif, &CodeLecture);

	       if ((PteteListeContigue != NULL) && CodeLecture)
		 {

		   CreerListeJour(PteteAgenda, pmotif, PteteListeContigue, &PfinListeContigue);

		   AfficherListeContigue(PteteListeContigue, PfinListeContigue);

		   LibererListeContigue(PteteListeContigue, PfinListeContigue);

		   free(pmotif);

		 }
	     }

	  break;

	case 3:

	   if (CodeLecture)
	     {

	       SauvegardeDansFichier(PteteAgenda, &CodeSauvegarde);

	       pjour = LectureSemaineJour();

	       if(pjour != NULL)
		 {

		   supression(&PteteAgenda,pjour->ann_sem, pjour->jour_heure);

		   free(pjour);

		 }

	     }

	}

      LibererListe(&PteteAgenda);
      
    }

  return 0;

}
