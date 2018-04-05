#include "tp3.h"


T_Transaction *ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction)
{
	T_Transaction* new = malloc(sizeof(T_Transaction));



	//on verifie si le malloc a fonctionne
	if (new == NULL)
	    exit(EXIT_FAILURE);
	new->idEtu = idEtu;
	new->montant = montant;
	new->descr = malloc(100*sizeof(char));
	if(!new->descr)
		exit(EXIT_FAILURE);
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
		time_t t;
		time(&t);
		new->idBlock = 0;
		new->next = NULL;
		new->date = *localtime(&t);

	}
	else {
		new->idBlock = bc->idBlock + 1;
		new->next = bc;
		new->date = addinterval(bc->date,0,0,1);
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
	bc->liste = ajouterTransaction(idEtu,montant,descr,bc->liste);
}



int payer(int idEtu, float montant, char *descr, BlockChain bc)
{
	if(bc == NULL)
		return 0;
	if(soldeEtudiant(idEtu,bc) > montant){ // Comme le montant à payer va être représenté par une valeur négative (e.g. : -3.25€), on le multiplie par -1 pour pouvoir le comparer au solde
		bc->liste = ajouterTransaction(idEtu,montant,descr,bc->liste);
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

		while(ptr_t != NULL){
			if (ptr_t->idEtu == idEtu){
				printf("id du bloc de la %deme transaction est : %d\n",i, bc->idBlock);
				printf("\tLa description de cette transaction est : %s", ptr_t->descr);
				printf("\tLe montant de cette transaction est : %f", ptr_t->montant);
				i++;
			}

			ptr_t = ptr_t->next;
		}

		bc = bc->next;
	 }


	if(i < 5)
		printf("L'étudiant à moins de 5 transactions"); //Afficher un message si l'étudiant à moins de 5 transactions ?

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

Date ajouterJour(Date d){
	Date tmp;
	tmp.jour = d.jour + 1;
	if((d.mois == 2 && tmp.jour == 29)
	   || ((d.mois == 1 || d.mois == 3 || d.mois == 5 || d.mois == 7 || d.mois == 8 || d.mois == 9 || d.mois == 12) && tmp.jour == 32)
	   || ((d.mois == 2 || d.mois == 4 || d.mois == 6 ||  d.mois == 9 || d.mois == 11) && tmp.jour == 0) ){
		tmp.jour = 1;
		tmp.mois = d.mois + 1;
	}
	if(tmp.mois == 13){
		tmp.mois = 1;
		tmp.annee = d.annee + 1;
	}

	return tmp;
}

struct tm addinterval(struct tm x, int y, int m, int d) {
	x.tm_year += y;
	x.tm_mon += m;
	x.tm_mday += d;
	mktime(&x); /* normalize result */
	return x;
}

int egalDate(Date d1, Date d2)
{
	return(d1.jour == d2.jour && d1.mois == d2.mois && d1.annee == d2.annee);
}
