#include "tp3.h"
#include "menu.h"

int main(){
	//Test pour qu'on puisse entrer des messages avec des espaces (le scanf s'arrête aux espaces)

	/*char test[255];
	printf("What is your name ?\n");
	fgets(test, 255, stdin);
	if ((strlen(test) > 0) && (test[strlen (test) - 1] == '\n'))
		test[strlen (test) - 1] = '\0';
	printf("Hello %s. Nice to meet you.\n", test);
*/

	BlockChain bc = NULL;
	bc = import();
    menu(bc);



    return 0;
}








