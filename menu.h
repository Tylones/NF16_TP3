#ifndef MENU_H
#define MENU_H


void menu(BlockChain bc);
void afficherBlocs(BlockChain bc);
void afficherTrans_bloc(BlockChain bc);
void afficherTransEtu_jour(BlockChain bc);
BlockChain credit(BlockChain bc);
void paiement(BlockChain bc);
int transferer(BlockChain bc);
int readInt();
float readFloat();
int clean_stdin();

#endif // MENU_H
