#include "ArvoreB.h"

void cria(Node **r, int grau) {
    *r = (Node*)malloc(sizeof(Node));
    (*r)->grauMinimo = grau; // Metade da capacidade do nó (quantidade de chaves)
    int nChaves = 2 * grau; // Numero máximo de chaves
    (*r)->chaves = (int *) malloc(sizeof(int) * nChaves);
    (*r)->filhos = (Node **) malloc(sizeof(Node *) * (nChaves + 1));
    (*r)->qtdChavesAtual = 0;
    (*r)->eFolha = 1;
}

void insereChave(Node** r, int novaChave, Node* novoFilho){

    int posicao = (*r)->qtdChavesAtual;

    while (novaChave < (*r)->chaves[posicao-1] && posicao>0){
        (*r)->chaves[posicao] = (*r)->chaves[posicao-1];
        (*r)->filhos[posicao+1] = (*r)->filhos[posicao];

        posicao--;
    }

    (*r)->chaves[posicao] = novaChave;
    (*r)->filhos[posicao+1] = novoFilho;

    (*r)->qtdChavesAtual++;
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
        status = 0; // Operacao realizada com sucesso
    } else {
        int tevePromocao, chavePromovida;
        Node novoNode;
        status = insereRecursivo(r, chave, &tevePromocao, &chavePromovida, &novoNode);

        if (tevePromocao != 0){ // Se houve promocao entao criamos um novo no raiz
            //cria(r,(*r)->grauMinimo);
            //(*r)->eFolha = 0;
        }

    }

    return status;
}

int insereRecursivo(Node **r, int chave, int* tevePromocao, int* chavePromovida, Node* novoNode){
//    if((*r)->qtdChavesAtual == 2*(*r)->grauMinimo) {
//        Node** novoFilho;
//        divide(r, novoIrmao,nodePai);
//        insereRecursivo(r, chave, nodePai);
//        return 1;
//    } else{
    int status;

    int i;
    for(i = 0; (i<=(*r)->qtdChavesAtual) && chave>(*r)->chaves[i]; i++);

    if(chave==(*r)->chaves[i]) {
        //TODO : Tratar erro
        return 1;

    }

    if(!(*r)->eFolha) {
        status = insereRecursivo(&(*r)->filhos[i], chave, tevePromocao, chavePromovida, novoNode);
        if(tevePromocao!=0) {
            if((*r)->qtdChavesAtual<2*(*r)->grauMinimo) {
                insereChave(r,chavePromovida,novoNode);
                *tevePromocao = 0;
            }
            else{
                // TODO: Fazer as verificacoes da divisao quando nao e folha
            }
        }
    }
    else{ // Se for folha
        printf("É folha\n");
        if((*r)->qtdChavesAtual<2*(*r)->grauMinimo){
            insereChave(r,chave,NULL);
            *tevePromocao = 0;
        }
        else{
            // TODO: Fazer as verficacoes da divisao quando e folha
            printf("Tera que dividir\n");
        }
    }

    return status;
}

void divide(Node **r, Node** novoIrmao, Node** nodePai){
    cria(novoIrmao, (*r)->grauMinimo);
    if((*r)->eFolha==0){
        (*novoIrmao)->eFolha = 0;
    }
    for(int i = (*r)->grauMinimo+1; i< 2*(*r)->grauMinimo; i++){
        (*novoIrmao)->chaves[i-(*r)->grauMinimo] = (*r)->chaves[i];
        (*r)->qtdChavesAtual--;
    }
    if(nodePai == NULL){
        Node** novaRaiz;
        cria(novaRaiz, (*r)->grauMinimo);
        insere(novaRaiz, (*r)->chaves[(*r)->grauMinimo]);
        (*r)->qtdChavesAtual--;
        (*novaRaiz)->filhos[0] = (*r);
        (*novaRaiz)->filhos[1] = (*novoIrmao);
        (*novaRaiz)->eFolha=0;
    } else{
        int posicao = (*nodePai)->qtdChavesAtual;
        while(posicao >0 && (*r)->chaves[(*r)->grauMinimo] < (*nodePai)->chaves[posicao]){
            posicao--;
        }
        posicao++;
        for(int i = (*nodePai)->qtdChavesAtual ; i >= posicao; i--){
            (*nodePai)->chaves[i] = (*nodePai)->chaves[i-1];
            (*nodePai)->filhos[i+2] = (*nodePai)->filhos[i+1];
        }
        (*nodePai)->chaves[posicao] = (*r)->chaves[(*r)->grauMinimo];
        (*nodePai)->filhos[posicao+1] = novoIrmao;
    }
    return;
}

int busca(Node** r, int chave, int *count) {
    count=0;

    for(int i=0; i <= (*r)->qtdChavesAtual; i++){
        if (chave = (*r)->chaves[i]) {
            return i;
        } else if (chave < (*r)->chaves[i]) {
            if ((*r)->filhos[i] != NULL) {
                return (buscaRecursivo((*r)->filhos[i], chave, &count));
            } else {
                return -1;
            }
            i++;
        }
        if (chave > (*r)->chaves[i]) {
            if ((*r)->filhos[i] != NULL) {
                return (buscaRecursivo((*r)->filhos[i], chave, &count));
            } else {
                return -1;
            }
        }
    }
}

int buscaRecursivo(Node** r, int chave, int* count){
    count++;

    for(int i=0; i <= (*r)->qtdChavesAtual; i++){
        if (chave = (*r)->chaves[i]) {
            return i;
        } else if (chave < (*r)->chaves[i]) {
            if ((*r)->filhos[i] != NULL) {
                return (buscaRecursivo((*r)->filhos[i], chave, &count));
            } else {
                return -1;
            }
            i++;
        }
        if (chave > (*r)->chaves[i]) {
            if ((*r)->filhos[i] != NULL) {
                return (buscaRecursivo((*r)->filhos[i], chave, &count));
            } else {
                return -1;
            }
        }
    }
}

