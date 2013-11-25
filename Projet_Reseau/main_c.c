#include "fonction.h"

int main(int argc, char const *argv[])
{
	int s_cli ;
  	struct sockaddr_in serv_addr ;
	//initialisation des variables
	int testFin = 1;
	char testFinChar[100] = "true";
	int terrain[TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR];
	int sousTerrain[TAILLE_TERRAIN_HAUTEUR][TAILLE_TERRAIN_LARGEUR];
	int positionPerso[2] = {0, 0};
	int positionEnnemi[2] = {19, 19};
	int compteurPO = 0, vies = 10, clefs = 0;
	char positionChar[100] = "";

	char tutoriel[NB_OBJET][TAILLE_MAX_TABLEAU_TUTORIEL] = {"\0"};
	char message[TAILLE_MAX_TABLEAU_AFFICHE] = "Dans quel direction voulez vous aller ? : ";
	
	s_cli = socket (PF_INET, SOCK_STREAM, 0) ;
	  serv_addr.sin_family = AF_INET ;
	  if ((argc == 2) || (argc == 3))
	  {
	    serv_addr.sin_addr.s_addr = inet_addr (argv[1]);
	  }
	  else
	  {
	    serv_addr.sin_addr.s_addr = inet_addr ("127.0.0.1");
	  }
	  if ((argc == 3))
	  {
	      serv_addr.sin_port = htons (atoi(argv[2])) ;
	  }
	  else
	  {
	      serv_addr.sin_port = htons (5000) ;
	  }
	  memset (&serv_addr.sin_zero, 0, sizeof(serv_addr.sin_zero));
	  connect (s_cli, (struct sockaddr *)&serv_addr, sizeof serv_addr) ;

	//initialisation de la carte (renvoie faux si le fichier n'existe pas)
	testFin = init_carte(terrain, sousTerrain, tutoriel);

	//boucle du jeu
	while(testFin == true)
	{
		//on affiche la carte
		affiche_carte(terrain, positionPerso, positionEnnemi, compteurPO, vies, clefs, tutoriel);

		//deplacement du personnage (renvoie faux si le personnage a gagné / perdu / arrété)
		testFin = deplace_personnage(terrain, positionPerso, &compteurPO, &vies, &clefs, message);
		
		if (testFin == false)
		{
			write(s_cli, "false", 100);
		}
		else
		{
			write(s_cli, "true", 100);

			bzero (positionChar, 100) ;
			sprintf(positionChar, "%d", positionPerso[0]);
			write(s_cli, positionChar, 100);
			bzero (positionChar, 100) ;
			sprintf(positionChar, "%d", positionPerso[1]);
			write(s_cli, positionChar, 100);

			read(s_cli, testFinChar, 100);
			if (!(strcmp(testFinChar, "true")))
			{
				bzero (positionChar, 100) ;
				read(s_cli, positionChar, 100);
				positionEnnemi[0] = atoi(positionChar);
				bzero (positionChar, 100) ;
				read(s_cli, positionChar, 100);
				positionEnnemi[1] = atoi(positionChar);
			}
			else
			{
				testFin = false;
			}
		}

	}
	//On affiche la carte finale
	affiche_carte(terrain, positionPerso, positionEnnemi, compteurPO, vies, clefs, tutoriel);
	//on affiche le résultat
	fin(compteurPO, testFin);

	return 0;
}