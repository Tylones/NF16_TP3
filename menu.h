#ifndef MENU_H
#define MENU_H
#include "tp3.h"


int menu(void);
int action(int choix, BlockChain bc);
void afficherBlocs(BlockChain bc);
void afficherTrans_bloc(BlockChain bc);
void afficherTransEtu_jour(BlockChain bc);
void credit(BlockChain bc);
int paiement(BlockChain bc);
int transferer(BlockChain bc);

#endif // MENU_H
