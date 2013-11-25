#ifndef FONCTIONS
	#define FONCTIONS

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>
	#include <stdbool.h>
	#include <unistd.h>
	#include <math.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>

	//taille de la chaine d'information
	#define TAILLE_MAX_TABLEAU_AFFICHE 1000
	#define TAILLE_MAX_TABLEAU_TUTORIEL 30

	//taille du terrain
	#define TAILLE_TERRAIN_HAUTEUR 20
	#define TAILLE_TERRAIN_LARGEUR 20

	#define FIN 2

	#define NB_OBJET 10

	#define HAUTEUR_TUTORIEL 5

	//enum des directions
	enum{QUIT = 0, HAUT = 8, BAS = 2, DROITE = 6, GAUCHE = 4};

	//enum des objets
	enum{HERBE, FLEUR, ARBRE, ROCHER, CLEF, PO, CADENAS, PIEGE, MONSTRE};

	//enum des couleurs des objets
	enum{HERBECL = 32 , FLEURCL = 33, ARBRECL = 130, ROCHERCL = 37, CLEFCL = 34, POCL = 133, CADENASCL = 137, PIEGECL = 35, MONSTRECL = 31, PERSOCL = 34};

	//Fonction de déplacement (deplacement.c)
	int deplace_personnage(int terrain[TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR], int positionPerso[2], int *compteurPO, int *vies, int *clefs, char message[TAILLE_MAX_TABLEAU_AFFICHE]);
	int deplacement(int terrain[TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR], int position[2] , int x, int y, int importEnnemi);
	int deplace_ennemi(int terrain[TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR], int sousTerrain[TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR], int positionPerso[2], int *vies, char message[TAILLE_MAX_TABLEAU_AFFICHE]);

	//Fonction d'affichage (affichage.c)
	int init_carte(int terrain [TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR], int sousTerrain [TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR], char tutoriel[NB_OBJET][TAILLE_MAX_TABLEAU_TUTORIEL]);
	void affiche_carte(int terrain[TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR], int positionPerso[2], int positionEnnemi[2], int compteurPO, int vies, int clefs, char tutoriel[NB_OBJET][TAILLE_MAX_TABLEAU_TUTORIEL]);
	void remplirCouleur(int couleurs[10]);
	void fin(int compteurPO, int testFin);

#endif