#include <stdio.h>
#include "ArvoreB.h"


int main(int argc, char* argv[]){

    ArvoreB Btree;
	
	cria(&Btree, 2);
	insere(&Btree, 2);
    printf("%d\n",Btree->chaves[0]);

    insere(&Btree, 4);
    printf("%d\n",Btree->chaves[1]);

    insere(&Btree, 3);
    printf("%d\n",Btree->chaves[2]);

    insere(&Btree, 1);
    printf("%d\n",Btree->chaves[3]);

    insere(&Btree, 5);
    printf("%d\n",Btree->chaves[3]);

    return 0;
}
