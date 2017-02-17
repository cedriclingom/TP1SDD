#include "./listeContigue.h"


int main (int argc, char ** argv)
{
  semaine_t * pTeteAgenda = NULL;
  /*char JOUR[TAILLE_MAX];*/
  if ((argc == 2) && (lectureFichier(argv[1], &pTeteAgenda)))
    {
      sauvegardeDansFichier(pTeteAgenda);
      libererListe(&pTeteAgenda);
    }
  return 0;
}
