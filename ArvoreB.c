#include "ArvoreB.h"

void cria(Node **r, int grau) {
    *r = (Node*)malloc(sizeof(Node));
    (*r)->grauMinimo = grau; // Metade da capacidade do nó (quantidade de chaves)
    int nChaves = 2 * grau; // Numero máximo de chaves
    (*r)->chaves = (int *) malloc(sizeof(int) * nChaves);
    (*r)->filhos = (Node **) malloc(sizeof(Node*) * (nChaves + 1));
    (*r)->qtdChavesAtual = 0;
    (*r)->eFolha = True;
}

void insereChave(Node** r, int novaChave, const Node* novoFilho){

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

    if ((*r)->qtdChavesAtual == 0)
    { // A árvore está vazia
        (*r)->chaves[0] = chave;
        (*r)->filhos[0] = NULL;
        (*r)->filhos[1] = NULL;
        (*r)->qtdChavesAtual++;
        status = 0; // Operacao realizada com sucesso
    } else {
        Bool tevePromocao;
        int chavePromovida;
        Node* novoNode;
        status = insereRecursivo(r, chave, &tevePromocao, &chavePromovida, &novoNode);

        if (tevePromocao == True){ // Se houve promocao entao criamos um novo no raiz
            //Cria um novo node interno
            Node* novaRaiz;
            cria(&novaRaiz,(*r)->grauMinimo);
            novaRaiz->eFolha = False;

            novaRaiz->chaves[0] = chavePromovida;
            novaRaiz->filhos[0] = *r;
            novaRaiz->filhos[1] = novoNode;
            novaRaiz->qtdChavesAtual++;

            *r = novaRaiz;
        }
    }
    return status;
}

int insereRecursivo(Node **r, int chave, Bool* tevePromocao, int* chavePromovida, Node** novoNode){
//    if((*r)->qtdChavesAtual == 2*(*r)->grauMinimo) {
//        Node** novoFilho;
//        divide(r, novoIrmao,nodePai);
//        insereRecursivo(r, chave, nodePai);
//        return 1;
//    } else{
    int status;

    //Procura pela chave ou pelo caminho que a insercao devera ser feita
    int i;
    for(i = 0; (i<=(*r)->qtdChavesAtual) && chave>(*r)->chaves[i]; i++);

    if(chave==(*r)->chaves[i]) {
        //TODO : Tratar erro
        return 1;

    }

    if((*r)->eFolha == False) {
        status = insereRecursivo(&(*r)->filhos[i], chave, tevePromocao, chavePromovida, novoNode);
        if(*tevePromocao == True) {
            if((*r)->qtdChavesAtual<2*(*r)->grauMinimo) { // Nao esta cheio
                insereChave(r,*chavePromovida,*novoNode);
                *tevePromocao = False;
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
            *tevePromocao = False;
        }
        else{
            // TODO: Fazer as verficacoes da divisao quando e folha
            printf("Tera que dividir\n");
        }
    }

    return status;
}

void divide(Node **r, int chave, int* chavePromovida, Node* nodeDireita, Node** novoNo) {
    printf("Entrando no processo de divisao\n");
    cria(novoNo, (*r)->grauMinimo);

    int mediana = (*r)->chaves[(*r)->grauMinimo];

    if(chave < mediana)
    {
        for (int i = (*r)->grauMinimo; i < 2 * (*r)->grauMinimo; i++) { // m
            printf("Transferindo: %d\n", (*r)->chaves[i]);
            (*novoNo)->chaves[i - (*r)->grauMinimo] = (*r)->chaves[i];
            (*novoNo)->filhos[i + 1 - (*r)->grauMinimo] = (*r)->filhos[i];
            (*novoNo)->qtdChavesAtual++;
            (*r)->qtdChavesAtual--;
        }
    } else{
        for (int i = (*r)->grauMinimo+1; i < 2 * (*r)->grauMinimo; i++) { // m+1
            printf("Transferindo: %d\n", (*r)->chaves[i]);
            (*novoNo)->chaves[i - ((*r)->grauMinimo+1)] = (*r)->chaves[i];
            (*novoNo)->filhos[i + 1 - ((*r)->grauMinimo+1)] = (*r)->filhos[i];
            (*novoNo)->qtdChavesAtual++;
            (*r)->qtdChavesAtual--;
        }
    }

    *chavePromovida = (*r)->chaves[(*r)->grauMinimo];
}


int busca(Node** r, int chave, int *count) {
    *count=0;
    int i=0;
    if(r == NULL){
        return -1;
    } else{
        if(chave < (*r)->chaves[0]){
            return buscaRecursivo((*r)->filhos[0],chave, count);
        } else if (chave == (*r)->chaves[0]) {
            return 0;
        } else{
            while (i < (*r)->qtdChavesAtual && i >= 0) {
                if(chave == (*r)->chaves[i]){
                    return i;
                } else if (chave > (*r)->chaves[i] && chave < (*r)->chaves[i + 1]) {
                    return buscaRecursivo((*r)->filhos[i+1], chave, count);
                }
                i++;
            }

            if(chave > (*r)->chaves[i]){
                return buscaRecursivo((*r)->filhos[i],chave, count);
            }
        }

    }
}

int buscaRecursivo(Node** r, int chave, int* count){
    (*count)++;
    int i=0;
    if(r == NULL){
        return -1;
    } else{
        if(chave < (*r)->chaves[0]){
            return buscaRecursivo((*r)->filhos[0],chave, count);
        } else if (chave == (*r)->chaves[0]) {
            return 0;
        } else{
            while (i < (*r)->qtdChavesAtual && (*r)->chaves[i] != chave && i > 0) {
                if(chave == (*r)->chaves[i]){
                    return i;
                } else if (chave > (*r)->chaves[i] && chave < (*r)->chaves[i + 1]) {
                    return buscaRecursivo((*r)->filhos[i+1], chave, count);
                }
                i++;
            }

            if(chave > (*r)->chaves[i]){
                return buscaRecursivo((*r)->filhos[i],chave, count);
            }
        }
    }
}

