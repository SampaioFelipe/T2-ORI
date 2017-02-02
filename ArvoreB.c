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

    while (novaChave < (*r)->chaves[posicao-1] && posicao>0){ // Verifica se a nova chave é menor que a maior chave do nó e se o nó não é vazio
        (*r)->chaves[posicao] = (*r)->chaves[posicao-1]; // Desloca o ponteiro para posição anterior do vetor chaves
        (*r)->filhos[posicao+1] = (*r)->filhos[posicao];

        posicao--;
    }

    (*r)->chaves[posicao] = novaChave; // Atribui a chave inserida para a posição designada no vetor chaves
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

    int status;

    //Procura pela chave ou pelo caminho que a insercao devera ser feita
    int i;
    for(i = 0; (i<(*r)->qtdChavesAtual) && chave>(*r)->chaves[i]; i++);

    if(chave==(*r)->chaves[i]) {
        // TODO: Tratar erro
        return 1;
    }

    if((*r)->eFolha == False) {
        status = insereRecursivo(&(*r)->filhos[i], chave, tevePromocao, chavePromovida, novoNode);
        if(*tevePromocao == True) { //TODO: Verificar se coloca status aqui
            if((*r)->qtdChavesAtual < 2 * (*r)->grauMinimo) { // Nao esta cheio
                insereChave(r,*chavePromovida,*novoNode);
                *tevePromocao = False;
            }
            else{
                // TODO: Testar as verificacoes da divisao quando nao e folha
                Node* novoFilho;
                int novaChavePromovida;
                divide(r, *chavePromovida, &novaChavePromovida, *novoNode, &novoFilho);
                *chavePromovida = novaChavePromovida;
                *novoNode = novoFilho;
            }
        }
    }
    else{ // Se for folha
        if((*r)->qtdChavesAtual<2*(*r)->grauMinimo){
            insereChave(r,chave,NULL);
            *tevePromocao = False;
        }
        else{
            divide(r, chave, chavePromovida, NULL, novoNode);
            *tevePromocao = True;
        }
    }
    return status;
}

void divide(Node **r, int chave, int* chavePromovida, Node* nodeDireita, Node** novoNode) {
    cria(novoNode, (*r)->grauMinimo);

    int mediana = (*r)->chaves[(*r)->grauMinimo];
    int i;
    if(chave < mediana)
    {
        for (i = (*r)->grauMinimo; i < 2 * (*r)->grauMinimo; i++) {
            (*novoNode)->chaves[i - (*r)->grauMinimo] = (*r)->chaves[i];
            (*r)->chaves[i]=0;
            (*novoNode)->filhos[i - (*r)->grauMinimo] = (*r)->filhos[i];
            (*r)->filhos[i] = NULL;
            (*novoNode)->qtdChavesAtual++;
            (*r)->qtdChavesAtual--;
        }
        (*novoNode)->filhos[i - (*r)->grauMinimo] = (*r)->filhos[i];
        (*r)->filhos[i] = NULL;
        insereChave(r, chave, nodeDireita);

    } else{

        for (i = (*r)->grauMinimo + 1; i < 2 * (*r)->grauMinimo; i++) {
            (*novoNode)->chaves[i - ((*r)->grauMinimo + 1)] = (*r)->chaves[i];
            (*r)->chaves[i]=0;
            (*novoNode)->filhos[i - ((*r)->grauMinimo + 1)] = (*r)->filhos[i];
            (*r)->filhos[i] = NULL;
            (*novoNode)->qtdChavesAtual++;
            (*r)->qtdChavesAtual--;
        }
        (*novoNode)->filhos[i - ((*r)->grauMinimo + 1)] = (*r)->filhos[i];
        (*r)->filhos[i] = NULL;

        insereChave(novoNode, chave, nodeDireita);
    }

    (*r)->qtdChavesAtual--;
    *chavePromovida = (*r)->chaves[(*r)->grauMinimo];
    (*r)->chaves[(*r)->grauMinimo] = 0;
}


int busca(Node** r, int chave, Node** pos) {
    int i=0;
    pos = NULL;
    if(r == NULL){
        return -1;
    } else{
        if(chave < (*r)->chaves[0]){
            return (buscaRecursivo(&(*r)->filhos[0],chave, &pos));
        } else{
            while (i < (*r)->qtdChavesAtual && i >= 0) {
                if(chave == (*r)->chaves[i]){
                    pos = r;
                    return i;
                } else if (chave > (*r)->chaves[i] && chave < (*r)->chaves[i + 1]) {
                    return (buscaRecursivo(&((*r)->filhos[i+1]), chave, &pos));
                }
                i++;
            }
            if(chave == (*r)->chaves[i]){
                pos = r;
                return i;
            }
            if(chave > (*r)->chaves[i]){
                return (buscaRecursivo(&((*r)->filhos[i]),chave, &pos));
            }
        }
    }
}

int buscaRecursivo(Node** r, int chave, Node** pos){
    int i=0;
    if((*r) == NULL){
        return -1;
    } else{
        if(chave < (*r)->chaves[0]){
            return buscaRecursivo(&(*r)->filhos[0],chave, &pos);
        } else{
            while (i <= (*r)->qtdChavesAtual && (*r)->chaves[i] != chave && i >= 0) {
                if(chave == (*r)->chaves[i]){
                    pos = r;
                    return i;
                } else if (chave > (*r)->chaves[i] && chave < (*r)->chaves[i + 1]) {
                    return buscaRecursivo(&((*r)->filhos[i+1]), chave, &pos);
                }
                i++;
            }
            if(chave == (*r)->chaves[i]){
                pos= r;
                return i;
            }

            if(chave > (*r)->chaves[i]){
                return buscaRecursivo(&((*r)->filhos[i]),chave, &pos);
            }
        }
    }
}

