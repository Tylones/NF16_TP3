#ifndef MENU_H
#define MENU_H
#include "tp3.h"

void menu(BlockChain bc);
void afficherBlocs(BlockChain bc);
void afficherTrans_bloc(BlockChain bc);
void afficherTransEtu_jour(BlockChain bc);
BlockChain credit(BlockChain bc);
void paiement(BlockChain bc);
int transferer(BlockChain bc);

#endif // MENU_H
