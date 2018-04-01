#include "tp3.h"


T_Transaction *ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction)
{
	T_Transaction* new = malloc(sizeof(T_Transaction));
	new->idEtu = idEtu;
	new->montant = montant;
	new->descr = descr;
	new->next = listeTransaction;
	return new;
}



BlockChain ajouterBlock(BlockChain bc)
{
	BlockChain new = malloc(sizeof(Block));
	if(bc == NULL) //Si le nouveau bloc créé est le premier, l'id = 0
		new->idBlock = 0;
	else
		new->idBlock = bc->idBlock + 1;
	new->liste = NULL;
	new->next = bc;
	return new;
}




float totalTransactionEtudiantBlock(int idEtu, T_Block b)
{
	int somme = 0;
	T_Transaction* tmp;
	if(b == NULL)
		return somme;
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
	int somme = 0;
	if(bc == NULL) //Condition d'arrêt de la fonction récursive
		return 0;
	return (totalTransactionEtudiantBlock(idEtu, *bc) + soldeEtudiant(idEtu, bc->next)); // On additionne le total des transactions de ce bloc
																						// avec celui du bloc suivant
}




void crediter(int idEtu, float montant, char *descr, BlockChain bc)
{
	if(bc == NULL || montant < 0)
		return;
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
