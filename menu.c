#include "menu.h"
#include "tp3.h"


int menu(void)
{
	int choix;
	do
	{
		printf("\n-------------Bienvenue sur EATcoin-------------\n");
		printf("\n");
		printf("1. Afficher la liste des blocs de la BlockChain\n");
		printf("2. Afficher toutes les transactions d'un bloc\n");
		printf("3. Afficher toutes les transactions du jour pour un etudiant\n");
		printf("4. Afficher l'historique pour un etudiant\n");
		printf("5. Crediter un compte\n");
		printf("6. Payer un repas\n");
		printf("7. Transferer des EATCoins entre 2 etudiants\n");
		printf("8. Quitter\n");
        printf("9. Exporter toutes les transactions vers un fichier\n");
		scanf("%d", &choix);

		while(getchar() != '\n');

	} while(choix < 1 || choix > 9);

	return choix;
}

int action(int choix, BlockChain bc)
{
    int idEtu;

	switch(choix)
	{

		case 1:
			if( bc == NULL)
                printf("La BlockChain est vide\n");
			else afficherBlocs(bc);
		break;

		case 2:
			afficherTrans_bloc(bc);
		break;

		case 3:
			afficherTransEtu_jour(bc);
		break;

		case 4:
		    printf("Pour quel etudiant voulez-vous afficher son historique ? \n");
		    scanf("%d", idEtu);
		    consulter(idEtu, bc);
		break;

		case 5:
		    credit(bc);
		break;

		case 6:
		    paiement(bc);
		break;

		case 7:
            transferer(bc);
		break;

		case 8:
		    printf("Exit. \n");
            return 0;
		break;
/*
		case 9:

        break;

        case 10:

        break;
*/
	}

	return 1;
}


void afficherBlocs(BlockChain bc)
{
	BlockChain ptr = bc;

	while(ptr != NULL){
		printf("Block numéro : %d \n", ptr->idBlock);

		//TO DO AFFICHER DATE DU BLOC

        ptr = ptr->next;

	}
}

void afficherTrans_bloc(BlockChain bc){
	BlockChain b = bc;
	int id;
	printf("Quel bloc voulez vous afficher (saisir id) ? \n");
	scanf("%d",&id);

	while(b != NULL || b->idBlock != id){
		b = b->next;
	}

	if(b == NULL){
		printf("Aucun bloc ne correspond a l'id saisi. \n");
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

void afficherTransEtu_jour(BlockChain bc){
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

void credit(BlockChain bc)
{
    int id;
    float montant;
    char *descr;
    printf("Veuillez saisir l'id du compte Etu.\n");
    scanf("%d", &id);
    printf("Veuillez saisir le montant a crediter.\n");
    scanf("%f", &montant);
    printf("Veuillez saisir une description.\n");
    scanf("%s", descr);

    crediter(id, montant, descr, bc);
}

int paiement(BlockChain bc)
{
    int id;
    float montant;
    char *descr;
    printf("Veuillez saisir l'id du compte Etu.\n");
    scanf("%d", &id);
    printf("Veuillez saisir le montant a payer.\n");
    scanf("%f", &montant);
    printf("Veuillez saisir une description.\n");
    scanf("%s", descr);
    payer(id,montant,descr,bc);
}

int transferer(BlockChain bc)
{
    int source, dest;
    float montant;
    char *descr;
    printf("Veuillez saisir l'id du compte Etu source.\n");
    scanf("%d", &source);
    printf("Veuillez saisir l'id du compte Etu destinataire.\n");
    scanf("%d", &dest);
    printf("Veuillez saisir le montant de la transaction.\n");
    scanf("%f", &montant);
    printf("Veuillez saisir une description.\n");
    scanf("%s", descr);
    transfert(source,dest,montant,descr,bc);
}
