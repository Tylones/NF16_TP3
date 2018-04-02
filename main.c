#include "tp3.h"

BlockChain bc;


void _1();
void _2();
void _3();
void _4();
void _5();
void _6();
void _7();
void _9();
void _10();





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


void _1(){
	BlockChain b = bc;
	T_Transaction* tmp;
	while(b != NULL){
		printf("Block numéro : %d \n", b->idBlock);

		tmp = b->liste;
		while(tmp != NULL){
			printf("Transaction : \n");
			printf("	idEtu : %d \n", tmp->idEtu);
			printf("	montant : %f \n", tmp->montant);
			printf("	description : %s \n", tmp->descr);
			printf("\n\n");
			tmp = tmp->next;
		}

		b = b->next;
	}
}

void _2(){
	BlockChain b = bc;
	int id;
	printf("Quel bloc voulez vous afficher ? \n");
	scanf("%d",&id);
	while(b != NULL || b->idBlock != id){
		b = b->next;
	}
	if(b == NULL){
		//do something
		return;
	}
	else{
		T_Transaction* tmp = b->liste;
		while(tmp != NULL){
			printf("Transaction : \n");
			printf("	idEtu : %d \n", tmp->idEtu);
			printf("	montant : %f \n", tmp->montant);
			printf("	description : %s \n", tmp->descr);
			printf("\n\n");
			tmp = tmp->next;
		}
	}

}

void _3(){
	int id;
	T_Transaction* tmp = bc ->liste;
	printf("Pour quel étudiant voulez vous afficher les transactions du jour ? \n");
	scanf("%d",&id);
	while(tmp != NULL){
		if(tmp->idEtu == id){
			printf("Transaction : \n");
			printf("	idEtu : %d \n", tmp->idEtu);
			printf("	montant : %f \n", tmp->montant);
			printf("	description : %s \n", tmp->descr);
			printf("\n\n");
		}
		tmp = tmp->next;
	}
}

void _4(){

}

void _5(){

}

void _6(){

}

void _7(){

}

void _9(){

}

void _10(){

}






