#include <stdio.h>
#include "tp3.h"
int main()
{
	BlockChain bc;
	ajouterBlock(bc);
	crediter(0,10,"Créditer de 10e",bc);
	payer(0, -3.25, "Repas RU", bc);
	printf("Hello World!\n");
	return 0;
}
