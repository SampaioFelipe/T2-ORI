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


    //Teste do divide para varios niveis

    for(int i=1; i<=16; i++){
        insere(&Btree,i);
    }
    printf("raiz\n");
    for(int i=0; i<4;i++){
        printf("%d ",Btree->chaves[i]);
    }
    printf("\nfilhos 1\n");
    for(int i=0;i<=4;i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", Btree->filhos[i]->chaves[j]);
        }
        printf("- ");
    }
    printf("\n");
    int count;

    printf("Teste de busca: %d\n", busca(&Btree, 2,&count));
    printf("%d\n",count);
    //printf("%d\n",Btree->filhos[3]->chaves[0]);
    //printf("%d\n",Btree->filhos[0]->filhos[0]->chaves[0]);

    return 0;
}
