#include "menu.h"
#include "tp3.h"


void menu(BlockChain bc)
{
	int choix = 0;
	int idEtu;
	while (choix != 8)
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
        printf("9. Exporter toutes les transactions vers un fichier\n\n");

		scanf("%d", &choix);

        switch(choix)
        {
            case 1:
                afficherBlocs(bc);
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
                //printf("id block : %d", bc->idBlock);
            break;

            case 6:
                paiement(bc);
            break;

            case 7:
                transferer(bc);
            break;

            case 8:
                printf("Exit. \n");
                //on libere la memoire
                while (bc != NULL)
                {
                    T_Transaction *liste_transaction = bc->liste;
                    while (liste_transaction != NULL)
                    {
                        T_Transaction *tmp = liste_transaction->next; //on recupere l'adresse de suivant avant de free
                        free(liste_transaction);
                        liste_transaction = tmp;
                    }
                    BlockChain tmpB = bc->next;
                    free(bc);
                    bc = tmpB;
                }
                bc = NULL;
            break;

            case 9:

            break;

            case 10:

            break;

            default : printf("Choix incorrect. \n");


        }

    }
    return 1;

}


void afficherBlocs(BlockChain bc)
{
	if (bc == NULL)
    {
        printf("La BlockChain est vide.\n");
        return;
    }

	BlockChain ptr = bc;
    printf("\n---Affichage de la liste des blocs que contient la BlockChain---\n");
	while(ptr != NULL){
		printf("Block numero : %d (le %d/%d/d) \n", ptr->idBlock, ptr->date->tm_mday, ptr->date->tm_mon, ptr->date->tm_year+1900);
        ptr = ptr->next;

	}
	ptr = NULL;

}

void afficherTrans_bloc(BlockChain bc){
	BlockChain b = bc;
	int id;
	printf("Quel bloc voulez vous afficher (saisir id) ? \n");
	scanf("%d",&id);

	while(b != NULL && b->idBlock != id){
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

//pour remplir la bc
void credit(BlockChain bc)
{
    time_t secondes;
    struct tm *instant;
    int id;
    float montant;
    //on recupere la date du jour
    secondes = time(NULL); //met la valeur a renvoyer dans temps equivalent a time(&secondes)
    instant = localtime(&secondes);
    instant->tm_year += 1900;
    printf("\n---Credit---\n");
    printf("\nLe %d/%d/%d a %d:%d:%d\n", instant->tm_mday, instant->tm_mon+1,instant->tm_year, instant->tm_hour, instant->tm_min, instant->tm_sec);

    if (bc == NULL || instant != bc->date){ //si bc est null OU si la date ne correspond pas a la date du bloc courant
        bc = ajouterBlock(bc);
        printf("ici : Ok on est entre dans le if (bc null ou instant != bc->date) donc ajouterBlock a ete fait\n");
        printf("id block apres l'ajout (on est dans credit de menu.c): %d\n", bc->idBlock);
    }

    printf("Veuillez saisir l'identifiant de l'etudiant : ");
    scanf("%d", &id);
    printf("Veuillez saisir le montant a crediter : ");
    scanf("%f", &montant);
    //printf("ici");
    //printf("id bloc avant crediter : %d", bc->idBlock);
    crediter(id, montant, "Credit", bc);

    printf("Le compte a ete recharge. \n\n");

}

int paiement(BlockChain bc)
{
    int id;
    float montant;
    char *descr;
    printf("Veuillez saisir l'identifiant de l'etudiant.\n");
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
