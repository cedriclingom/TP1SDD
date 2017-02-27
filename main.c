#include "./listeContigue.h"


int main (int argc, char ** argv)
{
  int choix;
  char * pMotif = NULL;
  semaine_t * pTeteAgenda = NULL;
  jour_t ** pTeteListeContigue = NULL, ** pFinListeContigue=NULL, * pJour = NULL;
  if (argc == 2)
    {
      printf("Veuillez choisir l'opération à faire!\n");
      printf("1. Creer la liste à deux niveaux et sauvegarder\n");
      printf("2. Creer la liste contigue des jours contenant un motif\n");
      printf("3. Supprimer une action\n");
      scanf("%d", &choix);
      switch(choix)
	{
	case 1:
	   if (lectureFichier(argv[1], &pTeteAgenda))
	     {
	       sauvegardeDansFichier(pTeteAgenda);
	     }
	   break;
	case 2:
	  if (lectureFichier(argv[1], &pTeteAgenda))
	     {
	       pTeteListeContigue = allocationListeContigue();
	       if ((pTeteListeContigue !=NULL) && (lectureMotif(&pMotif)))
		 {
		   creerListeJour(pTeteAgenda, pMotif, pTeteListeContigue, &pFinListeContigue);
		   afficherListeContigue(pTeteListeContigue, pFinListeContigue);
		   libererListeContigue(pTeteListeContigue, pFinListeContigue);
		   free(pMotif);
		 }
	     }
	  break;
	case 3:
	   if (lectureFichier(argv[1], &pTeteAgenda))
	     {
	       sauvegardeDansFichier(pTeteAgenda);
	       pJour = lectureSemaineJour();
	       if(pJour != NULL)
		 {
		   supression(&pTeteAgenda,pJour->ann_sem, pJour->jour_heure);
		   free(pJour);
		 }
	     }
	}
      libererListe(&pTeteAgenda);      
    }
  return 0;
}
