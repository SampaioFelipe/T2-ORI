/*
* Nome: ArvoreB
* Autores: Felipe Sampaio de Souza, Pedro Henrique Mauad, Pedro Henrique Migliatti
* Pre-requisitos: Sistema Operacional Linux
* Entrada: [ -t (grau minimo da árvore)] + [resposta do menu| 1. Inserir 2. Buscar 3. Sair] + [valor da chave ( no caso de escolha 1 ou 2)]
* Descricao: Programa para execução em na linha de comando que cria uma Árvore B e permite a realização de inserção de chaves,
bem como a realização da busca de chaves na Árvore criada.
*1)Argumentos: O primeiro argumento a ser passado se refere ao grau mínimo dá árvore B a ser criada.
    -t = grau_minimo (passa-se o grau mínimo da árvore B).
    
*Em seguida um menu é disponibilizado para realização de operações na árvore:
    - 1. Inserção: Permite a inserção de chaves na árvore
    - 2. Busca: Permite a busca de chaves na árvore
    - 3. Sair: Encerra o programa

*2)Retorno:
    - 1 : Não foi possível executar as operações pois os parametros passados são inválidos
    - 0 : Execução concluída com sucesso
*/

#include <stdio.h>
#include <string.h>
#include "ArvoreB.h"


int main(int argc, char* argv[]){

    int status;

    if(argc != 3)
    {
        printf("Quantidade de argumentos incorreta.\n");
        status = 1; // Irá retornar erro na especificacao da chamada do programa
    }
    else
    {
        if(strcmp(argv[1],"-t") == 0)
        {
            status = 0; // Irá retornar sucesso

            int op;
            int chave;
            Node* pos;
            int rBusca;
            ArvoreB Btree;
            cria(&Btree,atoi(argv[2]));

            do{
                printf("Selecione uma opção:\n");
                printf("1 - Inserir uma chave\n");
                printf("2 - Buscar uma chave\n");
                printf("3 - Sair\n");

                scanf("%d", &op);

                while ((getchar()) != '\n'); // Limpa o buffer

                if(op == 1) {
                    printf("Qual chave você deseja inserir?\n");
                    scanf("%d", &chave);
                    while ((getchar()) != '\n'); // Limpa o buffer
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
        }
        else
        {
            printf("Argumento inválido.\n");
            status = 1; // Irá retorna erro na especificacao da chamada do programa
        }
    }

    return status;
}
