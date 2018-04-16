#include "tp3.h"


T_Transaction *ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction)
{
	T_Transaction* new = malloc(sizeof(T_Transaction));
	//on verifie si le malloc a fonctionne
	if (new == NULL)
	    exit(EXIT_FAILURE);
	new->idEtu = idEtu;
	new->montant = montant;
	new->descr = malloc(strlen(descr)*sizeof(char));
	if(new->descr==NULL)
		exit(EXIT_FAILURE);
	strcpy(new->descr, descr);
	//new->descr = descr; il faut faire un strcpy,
	//on peut pas faire d'affectation direct en C pour les char
	new->next = listeTransaction;
	return new;
}



BlockChain ajouterBlock(BlockChain bc)
{
    //--------------A AJOUTER : date--------------
	BlockChain new = malloc(sizeof(T_Block));

	struct tm *instant;
	time_t secondes; //valeur du temps

	if (new == NULL)
	    exit(EXIT_FAILURE);

	if(bc == NULL){ //Si le nouveau bloc créé est le premier, l'id = 0
		new->idBlock = 0;
		new->next = NULL;
	}
	else {
		new->idBlock = bc->idBlock + 1;
		new->next = bc;

	}
	new->liste = NULL;

    secondes = time(NULL); //met la valeur a renvoyer dans temps equivalent a time(&secondes)
    instant = localtime(&secondes);
    new->date = instant;
    //printf("%d/%d a %d:%d:%d\n", instant->tm_mday, instant->tm_mon+1, instant->tm_hour, instant->tm_min, instant->tm_sec);
    //printf("%d/%d a %d:%d:%d\n", new->date->tm_mday, new->date->tm_mon+1);
    bc=new;

	return new;
}




float totalTransactionEtudiantBlock(int idEtu, T_Block b)
{
	float somme = 0;
	T_Transaction* tmp;

	tmp = b.liste;
	while(tmp != NULL){
		if(tmp->idEtu == idEtu)
			somme += tmp->montant;
		tmp = tmp->next;
	}
	return somme;
}



float soldeEtudiant(int idEtu, BlockChain bc)
{
	if(bc == NULL) //Condition d'arrêt de la fonction récursive
		return 0;
	return (totalTransactionEtudiantBlock(idEtu, *bc) + soldeEtudiant(idEtu, bc->next)); // On additionne le total des transactions de ce bloc
																						// avec celui du bloc suivant
}




void crediter(int idEtu, float montant, char *descr, BlockChain bc)
{
    if (montant > 0)
    {
        bc->liste = ajouterTransaction(idEtu,montant,descr,bc->liste);
        printf("\nCredit de %.2f EATCoin effectue sur le compte etudiant num %d le %d/%d/%d a %d:%d:%d (bloc transaction num : %d).\n",bc->liste->montant, bc->liste->idEtu,bc->date->tm_mday, bc->date->tm_mon+1,bc->date->tm_year+1900, bc->date->tm_hour, bc->date->tm_min, bc->date->tm_sec,bc->idBlock);
    }
	else
		printf("Erreur : montant a crediter inferieur a 0.\n");

}



int payer(int idEtu, float montant, char *descr, BlockChain bc)
{
	if(bc == NULL)

		return 0;
	if(soldeEtudiant(idEtu,bc) > montant){
        montant = montant *(-1);
		bc->liste = ajouterTransaction(idEtu,montant,descr,bc->liste);
		printf("Le repas a ete paye.\n");
		return 1;
	}
	else
        printf("Solde insuffisant, veuillez recharger votre compte.\n");
	return 0;
}


void consulter(int idEtu, BlockChain bc)
{
    float solde;
    solde = soldeEtudiant(idEtu, bc);
    int trouve = 0 ;
    int i = 0;
    T_Transaction *ptr_t = NULL;
	while (bc != NULL)
    {
        printf("----------HISTORIQUE DE L'ETUDIANT %d----------\n", idEtu);
		ptr_t = bc->liste;
        printf("Solde actuel : %.2f EATcoin.\n\n", solde);
		while(ptr_t != NULL && i < 5 ){
			if (ptr_t->idEtu == idEtu){
                printf("--Transactions du %d/%d/%d a %d:%d:%d--- \n", bc->date->tm_mday,bc->date->tm_mon+1, bc->date->tm_year+1900,bc->date->tm_hour, bc->date->tm_min, bc->date->tm_sec);
				printf("	id du bloc : %d\n", bc->idBlock);
				printf("	Description : %s\n", ptr_t->descr);
				printf("	Montant : %.2f EATCoin\n\n", ptr_t->montant);
				i++;
				trouve = 1;
			}

			ptr_t = ptr_t->next;

			if (trouve == 0)
                printf("L'etudiant %d n'a pas fait de transaction.\n", idEtu);
		}
		bc = bc->next;
	 }

}

int transfert(int idSource, int idDestination, float montant, char *descr, BlockChain bc)
{
	if(bc == NULL)
		return 0;
	if(payer(idSource, montant, descr, bc) == 1){
		crediter(idDestination, montant, descr, bc);
		return 1;
	}
	return 0;
}
