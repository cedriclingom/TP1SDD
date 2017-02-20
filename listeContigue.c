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


jour_t ** allocationListeContigue()
{
  jour_t ** tab = (jour_t **)malloc(TAILLE_MAX *sizeof(jour_t *));
  return tab;
}



jour_t * allocationJour()
{
  jour_t * pJour = (jour_t *)malloc(sizeof(jour_t));
  return pJour;
}

void creerJour(jour_t * pJour, semaine_t * pSemaine, action_t * pAction)
{
  strcpy(pJour->ann_sem, pSemaine->ann_sem);
  strcpy(pJour->jour_heure, pAction->jour_heure);
}



void insererJour(jour_t ** pDebut, jour_t*** ppFin, jour_t * pJour,int indice)
{
  pDebut[indice] = pJour;
  *ppFin = *ppFin + 1;
}



int lectureMotif(char ** ppMotif)
{
  int codeErr = 0, tailleMotif = 0;
  printf("Veuillez entrer la taille du motif!\n");
  codeErr = scanf("%d",&tailleMotif);
  codeErr = 0;
  *ppMotif = malloc((tailleMotif+1) * sizeof(char));
  if(*ppMotif != NULL)
    {
      printf("Veuillez entrer votre motif!\n");
      codeErr = scanf("%s",*ppMotif);
      codeErr = 1;
    }
  return codeErr;
}

void creerListeJour(semaine_t * pTeteListe, char * motif, jour_t ** pDebut, jour_t *** ppFin)
{
  semaine_t * pcour1 = pTeteListe;
  action_t * pcour2 = NULL;
  jour_t * pJour = NULL;
  int nbElm=0, motifTrouver=0,tailleMotif=strlen(motif);
  while ((nbElm < TAILLE_MAX) && (pcour1 != NULL))
    {
      pcour2 = pcour1->pListeAction;
      while((nbElm < TAILLE_MAX) && (pcour2 != NULL))
	{
	  motifTrouver = rechercherMotif(pcour2->nom_action,motif);
	  if(motifTrouver == tailleMotif)
	    {
	      pJour = allocationJour();
	      if (pJour != NULL)
		{
		  creerJour(pJour, pcour1, pcour2);
		  insererJour(pDebut, ppFin, pJour, nbElm);
		  ++nbElm;
		}
	    }
	  pcour2 = pcour2->pAction_suiv;
	}
      pcour1 = pcour1->pSem_suiv;
    }
}


void libererListeContigue(jour_t ** pDebut, jour_t ** pFin)
{
  int i=0;
  while ((pDebut+i) < pFin)
    {
      free(pDebut[i]);
      ++i;
    }
  free(pDebut[i]);
  free(pDebut);
}
