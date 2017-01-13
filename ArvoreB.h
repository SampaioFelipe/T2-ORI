//NAME
//   arvoreB - cria, busca e insere chaves em uma Árvore B
//
//SYNOPSIS
//   arvoreB -t grau_minimo
//
//DESCRIPTION
//   -t grau_minimo
//Com a opção -t, especifica-se o grau mínimo da Árvore B e cria-se a árvore.
//Após a criação, o programa deve apresentar um menu com três opções: 1 - Inserção, 2 - Busca, 3 - Sair.

#ifndef ARVOREB_ARVOREB_H
#define ARVOREB_ARVOREB_H

#include <stdlib.h>
#include <stdio.h>
typedef struct Node{
    int* chaves;
    struct Node** filhos;
    int eFolha;
    int grauMinimo;
    int qtdChavesAtual;
}Node;

void cria(Node** r, int grau);
int insere(Node** r, int chave);
int insereRecursivo(Node** r, int chave, int* promocao, int* chavePromovida, Node** novoNode);
int busca(Node* r, int chave);
int buscaRecursivo(Node* r, int chave);

#endif //ARVOREB_ARVOREB_H
