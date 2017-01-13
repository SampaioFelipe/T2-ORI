#include "ArvoreB.h"

void cria(Node **r, int grau) {
    (*r)->grauMinimo = grau; // Metade da capacidade do nó (quantidade de chaves)
    int nChaves = 2 * grau; // Numero máximo de chaves
    (*r)->chaves = (int *) malloc(sizeof(int) * nChaves);
    (*r)->filhos = (Node **) malloc(sizeof(Node *) * (nChaves + 1));
    (*r)->qtdChavesAtual = 0;
    (*r)->eFolha = 1;
}

int insere(Node **r, int chave) {
    int status;
    if (r == NULL) {
        return 1;
    }

    if ((*r)->qtdChavesAtual == 0) { // A árvore está vazia
        (*r)->chaves[0] = chave;
        (*r)->filhos[0] = NULL;
        (*r)->filhos[1] = NULL;
        (*r)->qtdChavesAtual++;
        status = 0;
    } else {
        int houvePromocao;
        int chavePromovida;
        Node* novoNode;
        status = insereRecursivo(r, chave, &houvePromocao, &chavePromovida, &novoNode);
        if (houvePromocao == 1) {
            //Tratamento da divisao
            printf("Houve divisao");
        }
    }

    return status;
}

int insereRecursivo(Node **r, int chave, int* promocao, int* chavePromovida, Node **novoNode) {

}

int busca(Node *r, int chave) {

}