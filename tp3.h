#ifndef TP3_H
#define TP3_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


typedef struct Transaction{
	int idEtu;
	float montant;
	char* descr;
	struct Transaction* next;
}T_Transaction;




typedef struct Block{
	int idBlock;
	struct tm *date; //pas de pointeurs si on fait un remplissage manuel
	T_Transaction *liste;
	struct Block *next;
}T_Block;


typedef T_Block* BlockChain;


T_Transaction *ajouterTransaction(int idEtu, float montant, char *descr, T_Transaction *listeTransaction);
BlockChain ajouterBlock(BlockChain bc);
BlockChain ajouterBlock2(BlockChain bc, struct tm*);
float totalTransactionEtudiantBlock(int idEtu, T_Block b);
float soldeEtudiant(int idEtu, BlockChain bc);
void crediter(int idEtu, float montant, char *descr, BlockChain bc);
int payer(int idEtu, float montant, char *descr, BlockChain bc);
int transfert(int idSource, int idDestination, float montant, char *descr, BlockChain bc);
void consulter(int idEtu, BlockChain bc);
void export(BlockChain bc);
void nettoyerFichier();
BlockChain import();


#endif // TP3_H
