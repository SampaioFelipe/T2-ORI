#include <stdio.h>
#include "ArvoreB.h"


int main(int argc, char* argv[]){

    ArvoreB Btree;
	
	cria(&Btree, 2);
	insere(&Btree, 2);

	printf("Funciona\n");
	printf("%d\n", Btree->chaves[0]);

    return 0;
}
