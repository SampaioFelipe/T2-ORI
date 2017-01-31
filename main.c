#include <stdio.h>
#include "ArvoreB.h"


int main(int argc, char* argv[]){

    ArvoreB Btree;
	
	cria(&Btree, 2);
//    insere(&Btree,4);
//	insere(&Btree, 5);
//    insere(&Btree, 2);
//    printf("%d\n", Btree->qtdChavesAtual);
//    int count;
//    printf("%d\n", busca(&Btree,5, &count));
//    printf("%d\n", count);
//	printf("Funciona\n");
//	//printf("%d\n", Btree->chaves[2]);

    insere(&Btree, 5);
    printf("%d\n",Btree->chaves[0]);

    insere(&Btree, 2);
    printf("%d\n",Btree->chaves[0]);

    insere(&Btree, 8);
    printf("%d\n",Btree->chaves[2]);

    insere(&Btree, 6);
    printf("%d\n",Btree->chaves[2]);

    insere(&Btree, 1);
    printf("%d\n",Btree->chaves[0]);
    insere(&Btree, 7);
    insere(&Btree, 9);
    insere(&Btree, 10);

    printf("%d\n",Btree->chaves[1]);
    printf("%d\n",Btree->filhos[2]->chaves[0]);

    return 0;
}
