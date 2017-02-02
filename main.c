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
    if(argc != 3)
    {
        printf("Quantidade de argumentos incorreta.\n");
        status = 1;
    }
    else
    {
        if(strcmp(argv[1],"-t") == 0)
        {
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
                    if(chave<0){
                        printf("Chave inválida\n");
                    }else if (insere(&Btree, chave) == 1) {
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
        }
        else
        {
            printf("Argumento errado\n");
            status = 1;
        }
    }

    return status;
}
