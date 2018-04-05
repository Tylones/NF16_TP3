#include "tp3.h"
#include "menu.h"

BlockChain bc;








int main()
{

	int choix = -1;
	while(choix != 0){
		printf("Que voulez vous faire ?\n");
		printf("1 : Afficher la liste des blocs de la BlockChain \n");
		printf("2 : Afficher toutes les transactions d’un bloc \n");
		printf("3 : Afficher toutes les transactions du jour pour un étudiant \n");
		printf("4 : Afficher l’historique pour un étudiant  \n");
		printf("5 : Créditer un compte  \n");
		printf("6 : Payer un repas  \n");
		printf("7 :  Transférer des EATCoins entre deux étudiants  \n");
		printf("8 : Quitter  \n");
		printf("9 : Exporter toutes les transactions vers un fichier  \n");
		printf("10 : Importer des transactions depuis un fichier  \n");
		scanf("%d",&choix);
		switch(choix){
		case 1:
			_1();
			break;
		case 2:
			_2();
			break;
		case 3:
			_3();
			break;
		case 4:
			_4();
			break;
		case 5:
			_5();
			break;
		case 6:
			_6();
			break;
		case 7:
			_7();
			break;
		case 9:
			_9();
			break;
		case 10:
			_10();
			break;
		default:
			choix = 0;

		}
	}
	return 0;
}








