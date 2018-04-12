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
    printf("%d/%d a %d:%d:%d\n", instant->tm_mday, instant->tm_mon+1, instant->tm_hour, instant->tm_min, instant->tm_sec);
    printf("%d/%d a %d:%d:%d\n", new->date->tm_mday, new->date->tm_mon+1);
    bc=new;
    printf("On est dans le bloc numero : %d(on est fin ajouterBlock)\n", bc->idBlock );
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
    if (montant > 0)
    {
        printf("id block dans crediter de tp3.c : %d",bc->idBlock);
        bc->liste = ajouterTransaction(idEtu,montant,descr,bc->liste);
        printf("\nCredit de %.2f EATCoin effectue sur le compte etudiant num %d (bloc transaction num : %d).\n",bc->liste->montant, bc->liste->idEtu,bc->idBlock);
    }
	else
		printf("Erreur : montant à crediter inférieur à 0");

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
