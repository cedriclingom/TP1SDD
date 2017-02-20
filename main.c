#include "./listeContigue.h"


int main (int argc, char ** argv)
{
  char * pMotif = NULL;
  semaine_t * pTeteAgenda = NULL;
  jour_t ** pTeteListeContigue = NULL, ** pFinListeContigue=NULL;
  if ((argc == 2) && (lectureFichier(argv[1], &pTeteAgenda)))
    {
      sauvegardeDansFichier(pTeteAgenda);
      pTeteListeContigue = allocationListeContigue();
      if ((pTeteListeContigue !=NULL) && (lectureMotif(&pMotif)))
	{
	  creerListeJour(pTeteAgenda, pMotif, pTeteListeContigue, &pFinListeContigue);
	  libererListeContigue(pTeteListeContigue, pFinListeContigue);
	  free(pMotif);
	}
      libererListe(&pTeteAgenda);      
    }
  return 0;
}
