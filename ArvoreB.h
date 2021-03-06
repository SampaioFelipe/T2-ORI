/*
Pré Condição: Sistema em funcionamento adequado
Pós-Condição: Criação da Árvore B, capacidade de realizar buscas de chaves na árvore, e inserção de chaves.
*/

#ifndef ARVOREB_ARVOREB_H
#define ARVOREB_ARVOREB_H

#include <stdlib.h>
#include <stdio.h>

typedef enum Bool{True, False} Bool;

typedef struct Node* ArvoreB;

typedef struct Node{
    int* chaves;
    struct Node** filhos;
    Bool eFolha;
    int grauMinimo;
    int qtdChavesAtual;
}Node;

void cria(Node** r, int grau);
void insereChave(Node** r, int novaChave, Node* novoFilho);
int insere(Node** r, int chave);
int insereRecursivo(Node **r, int chave, Bool* tevePromocao, int* chavePromovida, Node** novoNode);
void divide(Node **r, int chave, int* chavePromovida, Node* nodeDireita, Node** novoNode);

int busca(Node** r, int chave, Node** pos);
int buscaRecursivo(Node** r, int chave, Node** pos);

#endif //ARVOREB_ARVOREB_H
