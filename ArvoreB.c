#include "ArvoreB.h"

void cria(Node **r, int grau) {
    //(*r)->grauMinimo = grau; // Metade da capacidade do nó (quantidade de chaves)
    int nChaves = 2 * grau; // Numero máximo de chaves
    //(*r)->chaves = (int *) malloc(sizeof(int) * nChaves);
    //(*r)->filhos = (Node **) malloc(sizeof(Node *) * (nChaves + 1));
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
        //Verifico onde a chave será inserida e se ela já existe
        //Verifico se o nó onde ela será inserida está cheio
            //Se estiver cheio primeiro faço a divisão e depois insiro

    }

    return status;
}

int insereRecursivo(Node **r, int chave, Node** nodePai){
    if((*r)->qtdChavesAtual == 2*(*r)->grauMinimo) {
        Node** novoIrmao;
        divide(r, novoIrmao,nodePai);
        insereRecursivo(r, chave, nodePai);
        return 1;
    } else{
        if(!(*r)->eFolha){
            int posicao=1;

            if(chave<(*r)->chaves[0]){
                    insereRecursivo((*r)->filhos[0], chave, r);
                    return 1;
            }
            while(posicao < (*r)->qtdChavesAtual){
                if (chave > (*r)->chaves[posicao-1] && chave < (*r)->chaves[posicao]) {
                        insereRecursivo((*r)->filhos[posicao], chave, r);
                    return 1;
                }
                posicao++;
            }
            if(chave>(*r)->chaves[(*r)->qtdChavesAtual]){
                insereRecursivo((*r)->filhos[posicao],chave, *r);
                return 1;
            }
        } else{
            int posicao = (*r)->qtdChavesAtual;
            while(posicao < (*r)->chaves[posicao-1] && posicao > 0){
                posicao--;
            }

            for(int i = (*r)->qtdChavesAtual-1; i >= posicao; i++){
                (*r)->chaves[i+1] = (*r)->chaves[i];
                (*r)->chaves[i+2] = (*r)->chaves[i+1];
                (*r)->chaves[i+1] = (*r)->chaves[i];
            }
            (*r)->chaves[posicao] = chave;
            (*r)->filhos[posicao] = NULL;

        }
    }

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

//    while (i < (*r)->qtdChavesAtual) {
//        if (chave = (*r)->chaves[i]) {
//            return i;
//        } else if (chave < (*r)->chaves[i]) {
//            if ((*r)->filhos[i] != NULL) {
//                return (busca((*r)->filhos[i], chave));
//            } else {
//                return -1;
//            }
//            i++;
//        }
//        if (chave > (*r)->chaves[i]) {
//            if ((*r)->filhos[i] != NULL) {
//                count++;
//                return (busca((*r)->filhos[i], chave));
//            } else {
//                return -1;
//            }
//        }
//
//    }
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

