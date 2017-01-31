#include <stdio.h>
#include "ArvoreB.h"


int main(int argc, char* argv[]){

    ArvoreB Btree;
	
	cria(&Btree, 3);
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

    insere(&Btree, 11);
    printf("%d\n",Btree->chaves[3]);

    insere(&Btree, 12);
    printf("%d\n",Btree->chaves[3]);


    //teste do divide
    ArvoreB Btree2;

    cria(&Btree2, 2);
    int chavePromovida;
    divide(&Btree, 3, &chavePromovida, &Btree, &Btree2);
    printf("%d\n", Btree2->chaves[1]);
    printf("%d\n", Btree->chaves[1]);

    return 0;
}
