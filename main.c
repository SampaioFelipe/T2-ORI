#include <stdio.h>
#include "ArvoreB.h"


int main(int argc, char* argv[]){
    Node** Btree;
	
	cria(Btree, 2);
	insere(Btree, 2);

	printf("Funciona");
//	printf((*Btree)->chaves[0]);


    return 0;
}
