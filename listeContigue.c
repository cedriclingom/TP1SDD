#include "./listeContigue.h"


int compareChaineN (char * s1, char * s2, int taille)
{

  int i=0;
  while ((i<taille) && (s1[i] == s2[i]))
    {
      ++i;
    }
  if(!i)
    {
      ++i;
    }
  return i;
}


int rechercherMotif(char * nomAction, char * motif)
{
  int tailleMotif = strlen(motif),decalage=0, tailleResteAction = (TAILLE_ACTION-2)-decalage;
  
  while ((tailleMotif <= tailleResteAction) && (decalage < tailleMotif))
    {
      decalage = compareChaineN(nomAction+decalage, motif, tailleMotif);
      tailleResteAction -=decalage;      
    }
  return decalage;
}





 void creerListeJour(semaine_t * pTeteListe, char * motif, jour_t ** tab)
{
  semaine_t * pcour1 = pTeteListe;
  action_t * pcour2 = NULL;
  int nbElm=0, motifTrouver=0,tailleMotif=strlen(motif);

  while ((nbElm < TAILLE_MAX) && (pcour1 != NULL))
    {
      pcour2 = pcour1->pListeAction;
      while((nbElm < TAILLE_MAX) && (pcour2 != NULL))
	{
	  motifTrouver = rechercherMotif(pcour2->nom_action,motif);
	  if(motifTrouver == tailleMotif)
	    {
	      /*insrerMotif dans la liste contigue*/
	      ++nbElm;
	    }
	  pcour2 = pcour2->pAction_suiv;
	}
    }
}
