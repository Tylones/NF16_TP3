#include "tp3.h"


T_Transaction *ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction)
{
	T_Transaction* new = malloc(sizeof(T_Transaction));
	//on verifie si le malloc a fonctionne
	if (new == NULL)
	    exit(EXIT_FAILURE);
	new->idEtu = idEtu;
	new->montant = montant;
	strcpy(new->descr, descr);
	//new->descr = descr; il faut faire un strcpy,
	//on peut pas faire d'affectation direct en C pour les char
	new->next = listeTransaction;
	return new;
}



BlockChain ajouterBlock(BlockChain bc)
{
	BlockChain new = malloc(sizeof(T_Block));
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
	
	return new;
}




float totalTransactionEtudiantBlock(int idEtu, T_Block b)
{
	int somme = 0;
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
	if(bc == NULL || montant < 0){
		printf("Erreur : montant à créditer inférieur à 0");
		return;
	}
	ajouterTransaction(idEtu,montant,descr,bc->liste);
}



int payer(int idEtu, float montant, char *descr, BlockChain bc)
{
	if(bc == NULL)
		return 0;
	if(soldeEtudiant(idEtu,bc) > montant * -1){ // Comme le montant à payer va être représenté par une valeur négative (e.g. : -3.25€), on le multiplie par -1 pour pouvoir le comparer au solde
		ajouterTransaction(idEtu, montant, descr, bc->liste);
		return 1;
	}
	return 0;
}


void consulter(int idEtu, BlockChain bc)
{
    soldeEtudiant(idEtu, bc);

    int i = 0;
    T_Transaction *ptr_t = NULL;
	while (i != 5 && bc != NULL)
    {
        printf("----------Historique des 5 dernieres transaction de l'etu n°%d----------\n", idEtu);
		ptr_t = bc->liste;
		if (ptr_t->idEtu == idEtu){
			printf("id du bloc de la %deme transaction est : %d\n",i, bc->idBlock);
			printf("\tLa description de cette transaction est : %s", bc->liste->descr);
			printf("\tLe montant de cette transaction est : %f", bc->liste->montant);

            i++;
			bc = bc->next;
        }
    }

	if(i < 5)
		printf("L'étudiant à moins de 5 transactions"); //Afficher un message si l'étudiant à moins de 5 transactions ?

}

int transfert(int idSource, int idDestination, float montant, char *descr, BlockChain bc)
{
	if(bc == NULL)
		return 0;
	if(montant > soldeEtudiant(idSource,bc))
		return 0;
	ajouterTransaction(idSource, montant * -1, descr, bc->liste); // On part du principe que le montant du transfert est positif, de ce fait, on le multiplie par -1 pour le débiter à la source
	ajouterTransaction(idDestination, montant, descr, bc->liste);
	return 1;
}
