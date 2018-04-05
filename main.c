#include "tp3.h"
#include "menu.h"

int main(){

    BlockChain bc = NULL;

    int choix = 0;
    int continuer = 0;

    choix = menu();
    continuer = action(choix, bc);


    return 0;
}








