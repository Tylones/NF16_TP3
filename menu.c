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
                scanf("%d", &idEtu);
                printf("----------HISTORIQUE DE L'ETUDIANT %d----------\n", idEtu);
                consulter(idEtu, bc);
            break;

            case 5:
                bc = credit(bc);
            break;

            case 6:
                paiement(bc);
            break;

            case 7:
                transferer(bc);
            break;

            case 8:
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
                printf("Vous avez quitte. \n");
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
        printf("\nLa BlockChain est vide.\n");
        return;
    }

	BlockChain ptr = bc;
    printf("\n---Affichage de la liste des blocs que contient la BlockChain---\n");
	while(ptr != NULL){
		printf("\nBlock numero : %d (le %d/%d/%d) \n", ptr->idBlock, ptr->date->tm_mday, ptr->date->tm_mon+1, ptr->date->tm_year+1900);
        ptr = ptr->next;

	}
	ptr = NULL;

}

void afficherTrans_bloc(BlockChain bc){
	BlockChain b = bc;
	int id;

	if (bc == NULL)
    {
        printf("\nLa BlockChain est vide.\n");
        return;
    }

	printf("Quel bloc voulez vous afficher (saisir id) ? \n");
	scanf("%d",&id);

	while(b != NULL && b->idBlock != id){
		b = b->next;
	}

	if(b == NULL){
		printf("\nAucun bloc ne correspond a l'id saisi. \n");
		return;
	}
	else{
        printf("\n---Transactions du bloc %d---\n", bc->idBlock);
		T_Transaction* tmp = b->liste;
		while(tmp != NULL){
			printf("	idEtu : %d \n", tmp->idEtu);
			printf("	Montant : %.2f EATCoin\n", tmp->montant);
			printf("	Description : %s \n\n", tmp->descr);

			tmp = tmp->next;
		}
	}

}

void afficherTransEtu_jour(BlockChain bc){
	int id;
	int trouve = 0 ;

	if (bc == NULL)
    {
        printf("\nLa BlockChain est vide.\n");
        return;
    }

	T_Transaction* tmp = bc ->liste;
	printf("Veuillez saisir l'identifiant de l'etudiant : ");
	scanf("%d",&id);
    printf("\n--Transactions du %d/%d/%d de l'etudiant %d--- \n", bc->date->tm_mday,bc->date->tm_mon+1, bc->date->tm_year+1900,id);
	while(tmp != NULL){

        if(tmp->idEtu == id){

            //printf("	idEtu : %d \n", tmp->idEtu);
            printf("	Description : %s \n", tmp->descr);
            printf("	Montant : %.2f EATCoin \n\n", tmp->montant);
            trouve = 1;
        }

        tmp = tmp->next;
	}
	if (trouve == 0)
        printf("\nL'etudiant %d n'a pas fait de transaction aujourd'hui.\n", id);
}

//pour remplir la bc
BlockChain credit(BlockChain bc)
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
    }

    printf("Veuillez saisir l'identifiant de l'etudiant : ");
    scanf("%d", &id);
    printf("Veuillez saisir le montant a crediter : ");
    scanf("%f", &montant);
    //printf("ici");
    //printf("id bloc avant crediter : %d", bc->idBlock);
    crediter(id, montant, "Credit", bc);


    return bc;


}

void paiement(BlockChain bc)
{
    int id, result;
    float montant;
    char *descr = malloc(strlen(descr)*sizeof(char));
    printf("\n---Achat repas---\n");
    printf("Veuillez saisir l'identifiant de l'etudiant : ");
    scanf("%d", &id);
    printf("Veuillez saisir le montant a payer : ");
    scanf("%f", &montant);
    printf("Veuillez saisir le repas : ");
    scanf("%s", descr);
    //printf("ici");
    result = payer(id,montant,descr,bc);
    printf("Le repas a ete paye.\n");
}

int transferer(BlockChain bc)
{
    int source, dest;
    float montant;
    char *descr = malloc(strlen(descr)*sizeof(char));
    printf("Veuillez saisir l'id du compte Etu source.\n");
    scanf("%d", &source);
    printf("Veuillez saisir l'id du compte Etu destinataire.\n");
    scanf("%d", &dest);
    printf("Veuillez saisir le montant de la transaction.\n");
    scanf("%f", &montant);
    printf("Veuillez saisir une description.\n");
    scanf("%s", descr);
    transfert(source,dest,montant,descr,bc);
    printf("Le virement a un autre etudiant a ete fait.\n");
}
