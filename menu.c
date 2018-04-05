#include "menu.h"
 /*
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
*/
