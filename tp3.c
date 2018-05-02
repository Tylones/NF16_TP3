#include "tp3.h"
#include "menu.h"

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
   // bc=new;

	return new;
}


BlockChain ajouterBlock2(BlockChain bc, struct tm* date)
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
	new->date = date;
	new->liste = NULL;
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
		printf("Erreur : montant a crediter inferieur a 0 ou nul.\n");


}



int payer(int idEtu, float montant, char *descr, BlockChain bc)
{
	if(bc == NULL)

		return 0;
	if(soldeEtudiant(idEtu,bc) > montant){
        montant = montant *(-1);
		bc->liste = ajouterTransaction(idEtu,montant,descr,bc->liste);
		return 1;
	}
	else
        printf("Solde insuffisant, veuillez recharger votre compte.\n");
	return 0;
}


void consulter(int idEtu, BlockChain bc)
{
    if (bc == NULL)
    {
        printf("\nLa BlockChain est vide.\n");
        return;
    }
    float solde;
    solde = soldeEtudiant(idEtu, bc);
    int trouve = 0 ;
    int i = 0;
    T_Transaction *ptr_t = NULL;
    printf("Solde actuel : %.2f EATcoin.\n\n", solde);
	while (bc != NULL)
    {
        ptr_t = bc->liste;
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
		}
		bc = bc->next;
	 }
	 if (trouve == 0)
                printf("L'etudiant %d n'a pas fait de transaction.\n", idEtu);

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

void nettoyerFichier(){
	remove("sauvegarde.txt");
}



void export(BlockChain bc) // Fonction récursive qui va faire en sorte que les blocks les plus anciens soient sauvegardés en premier dans le fichier
{
	if(bc != NULL){
		export(bc->next);
		FILE *fp = fopen("sauvegarde.txt","a");
		T_Transaction *tmp = bc->liste;
		while (tmp != NULL) {
			fprintf(fp,"date(%d/%d/%d);%d;%f;%s\n", bc->date->tm_mday, bc->date->tm_mon+1, bc->date->tm_year+1900, tmp->idEtu, tmp->montant, tmp->descr);
			tmp = tmp->next;
		}
		fclose(fp);
	}
}

BlockChain import()
{
	BlockChain bc = NULL;
	FILE *fp = fopen("sauvegarde.txt","r");
	if(fp == NULL)
		return NULL;
	int DD,MM,YYYY,idEtu;
	float montant;
	char buff[255], descr[255];
	struct tm* date;
	while(!feof(fp) && fgets(buff,255,fp) != NULL && strcmp("\n",buff)){
		sscanf(buff,"date(%d/%d/%d);%d;%f;%s",&DD,&MM,&YYYY,&idEtu,&montant,descr);
		date = malloc(sizeof(struct tm));
		date->tm_mday = DD;
		date->tm_mon = MM-1;
		date->tm_year = YYYY-1900;
		if(bc == NULL || bc->date->tm_mday != date->tm_mday || bc->date->tm_mon != date->tm_mon || bc->date->tm_year != date->tm_year){ //Si la BlockChain est vide ou bien que la date de la transaction ne correspond pas à celle de premier block
			bc = ajouterBlock2(bc,date);
		}
		bc->liste = ajouterTransaction(idEtu,montant,descr,bc->liste);
	}

	return bc;

}

