/*
* Nome: ArvoreB
* Autores: Felipe Sampaio de Souza, Pedro Henrique Mauad, Pedro Henrique Migliatti
* Pre-requisitos: Sistema Operacional Linux
* Entrada: [ -t (grau minimo da árvore)] + [resposta do menu| 1. Inserir 2. Buscar 3. Sair] + [valor da chave ( no caso de escolha 1 ou 2)]
* Descricao:
*/

#include <stdio.h>
#include <string.h>
#include "ArvoreB.h"


int main(int argc, char* argv[]){

    int status;
    //TODO: Excluir os printf de teste
//    if(argc != 3)
//    {
//        printf("Quantidade de argumentos incorreta.\n");
//        status = 1;
//    }
//    else
//    {
//        if(strcmp(argv[1],"-t") == 0)
//        {
            int op;
            int chave;
            Node* pos;
            int *rBusca;
            ArvoreB Btree;
            cria(&Btree,2); //atoi(argv[2]));

            do{
                printf("Selecione uma opção:\n");
                printf("1 - Inserir uma chave\n");
                printf("2 - Buscar uma chave\n");
                printf("3 - Inserir uma chave\n");
                scanf("%d", &op);

                if(op == 1) {
                    printf("Qual chave você deseja inserir?\n");
                    scanf("%d", &chave);
                    if (insere(&Btree, chave) == 1) {
                        printf("A chave já existe na árvore\n\n");
                    } else {
                        rBusca = busca(&Btree, chave, &pos);
                        printf("A chave %d, foi inserida no nó da posição de memória %p e no indice %d \n\n", chave,
                               pos, rBusca);
                    }
                }
                if(op == 2){
                    printf("Qual chave você deseja buscar?\n");
                    scanf("%d", &chave);
                    rBusca = busca(&Btree, chave, &pos);
                    if(rBusca == -1){
                        printf("CHAVE NÃO ECONTRADA!\n");
                    } else{
                        printf("A chave %d, está no nó da posição de memória %p e no indice %d\n\n", chave, pos, rBusca);
                    }
                }

            }while (op!=3);
            //TODO: Criar a arvore com o grau passado em argv[2] (é necessário transformar em int)
            //TODO: Fazer um loop de interação que possibilite que o usuário faça: 1 - Inserção, 2 - Busca, 3 - Sair
            printf("Argumento correto\n");
      //  }
//        else
//        {
//            printf("Argumento errado\n");
//            status = 1;
//        }
    //}

  //  return status;


//    ArvoreB Btree;
//
//	cria(&Btree, 2);
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

//    for(int i=17; i>=1; i--){
//        printf("Inserindo: %d\n", i);
//        insere(&Btree,i);
//    }
//    printf("raiz\n");
//    for(int i=0; i<4;i++){
//        printf("%d ",Btree->chaves[i]);
//    }
//    printf("\nfilhos 1\n");
//    for(int i=0;i<=4;i++) {
//        for (int j = 0; j < 4; j++) {
//            if(Btree->filhos[i] != NULL)
//                printf("%d ", Btree->filhos[i]->chaves[j]);
//        }
//        printf("- ");
//    }
//    printf("\nfilhos 2\n");
//    for(int i=0;i<=4;i++) {
//        for (int j = 0; j < 4; j++) {
//            if(Btree->filhos[1]->filhos[i] != NULL)
//                printf("%d ", Btree->filhos[1]->filhos[i]->chaves[j]);
//        }
//        printf("- ");
//    }
//    printf("\n");
////    int count;

//    printf("Teste de busca: %d\n", busca(&Btree, 2,&count));
//    printf("%d\n",count);
    //printf("%d\n",Btree->filhos[3]->chaves[0]);
    //printf("%d\n",Btree->filhos[0]->filhos[0]->chaves[0]);

    return 0;
}
