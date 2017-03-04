#compilateur

CC = gcc

#Profileur

VG = valgrind

#Option

CFLAGS = -ansi -pedantic -Wall -Wextra -g -O2
LDFLAGS = -lm

#liste des fichiers objets

OBJ = main.o listeChainee_semaine.o listeChainee_action.o listeContigue.o


#Règle d'éxécution
exe : main
	./main fichier.txt

#Regle de production de l'exécutable

main : $(OBJ)
	$(CC) -o main $(OBJ) $(CFLAGS) $(LDFLAGS)


#Règle de production des fichiers objets

listeChainee_semaine.o : listeChainee_semaine.c listeChainee_semaine.h 
	$(CC) -c listeChainee_semaine.c $(CFLAGS) $(LDFLAGS)

listeChainee_action.o : listeChainee_action.c listeChainee_action.h
	$(CC) -c listeChainee_action.c $(CFLAGS) $(LDFLAGS)

listeContigue.o: listeContigue.c listeContigue.h
	$(CC) -c listeContigue.c $(CFLAGS) $(LDFLAGS)

main.o : main.c listeContigue.h
	$(CC) -c main.c $(CFLAGS) $(LDFLAGS)

#Regle pour nettoyer

clean :
	rm $(OBJ)


#Regle d'utilisation de valgrind

valgrind:  main
	$(VG) ./main fichier.txt

