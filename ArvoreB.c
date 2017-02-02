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
        (*r)->filhos[posicao+1] = (*r)->filhos[posicao]; // Desloca o ponteiro do filho a direita para a posição anterior do vetor filhos

        posicao--;
    }

    (*r)->chaves[posicao] = novaChave; // Atribui a chave inserida para a posição designada no vetor chaves
    (*r)->filhos[posicao+1] = novoFilho; // Atribui o novo filho a direita da chave inserida na posição designada no vetor filhos

    (*r)->qtdChavesAtual++;
}

int insere(Node **r, int chave) {
    int status;
    if (r == NULL) { // Caso não exista o nó, retorne flag de status
        return 1;
    }

    if ((*r)->qtdChavesAtual == 0)
    { // A árvore está vazia
        (*r)->chaves[0] = chave; // Atribui o valor da chave para a primeira posição do vetor chaves
        (*r)->filhos[0] = NULL; // Como existe apenas uma única chave, não existe filho a esquerda
        (*r)->filhos[1] = NULL; // Como existe apenas uma única chave, não existe filho a direita
        (*r)->qtdChavesAtual++; // Incrementa quantidade total de chaves existentes na árvore
        status = 0; // Operacao realizada com sucesso
    } else {
        Bool tevePromocao;
        int chavePromovida;
        Node* novoNode;
        status = insereRecursivo(r, chave, &tevePromocao, &chavePromovida, &novoNode);


        if (tevePromocao == True){ // Se houve promocao entao criamos um novo no raiz
            //Cria um novo node interno
            Node* novaRaiz;
            cria(&novaRaiz,(*r)->grauMinimo); // Cria-se um novo nó, com nova raiz e grau mínimo definido
            novaRaiz->eFolha = False; // Criação de um novo nó acima dos nós folha, condição deve ser falsa

            novaRaiz->chaves[0] = chavePromovida; // chave promovida será a primeira chave do novo nó
            novaRaiz->filhos[0] = *r; // O nó existente se torna o filho a esquerda
            novaRaiz->filhos[1] = novoNode; // O novo nó criado se torna o filho a direita
            novaRaiz->qtdChavesAtual++; // Aumenta a quantidade de chaves totais na árvore

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

    if(chave==(*r)->chaves[i]) { // Se a chave inserida já existe, retorne flag de status
        return 1;
    }

    if((*r)->eFolha == False) { // Se não for no folha chamar insereRecursivo
        status = insereRecursivo(&(*r)->filhos[i], chave, tevePromocao, chavePromovida, novoNode); 
        if(*tevePromocao == True) { // Ocorreu promoção de chave
            if((*r)->qtdChavesAtual < 2 * (*r)->grauMinimo) { // Nao esta cheio
                insereChave(r,*chavePromovida,*novoNode); // Insere a chave no novo nó
                *tevePromocao = False;
            }
            else{ // Se está cheio
                Node* novoFilho;
                int novaChavePromovida;
                divide(r, *chavePromovida, &novaChavePromovida, *novoNode, &novoFilho); // Divida o nó 
                *chavePromovida = novaChavePromovida; // Promova uma nova chave
                *novoNode = novoFilho; // Novo nó criado será o novo filho a direita do nó acima
            }
        }
    }
    else{ // Se for folha
        if((*r)->qtdChavesAtual<2*(*r)->grauMinimo){ // E não estiver cheio
            insereChave(r,chave,NULL); // Insere
            *tevePromocao = False; // Não há promoção de chaves
        }
        else{ // Se estiver cheio
            divide(r, chave, chavePromovida, NULL, novoNode); // Divida o nó
            *tevePromocao = True; // Promova uma chave
        }
    }
    return status;
}

void divide(Node **r, int, chave, int* chavePromovida, Node* nodeDireita, Node** novoNode) { // Divide o nó, promovendo uma chave
    cria(novoNode, (*r)->grauMinimo); // Cria o novo nó com grau mínimo definido

    int mediana = (*r)->chaves[(*r)->grauMinimo]; // Define a mediana do vetor chaves
    int i;
    if(chave < mediana)
    {
        for (i = (*r)->grauMinimo; i < 2 * (*r)->grauMinimo; i++) { // Transfere metade das chaves do nó existente para o nó criado
            (*novoNode)->chaves[i - (*r)->grauMinimo] = (*r)->chaves[i]; // Adiciona chave mediana do nó existente no início do nó criado
            (*r)->chaves[i]=0; 
            (*novoNode)->filhos[i - (*r)->grauMinimo] = (*r)->filhos[i]; // Promove chave do meio para o nó pai
            (*r)->filhos[i] = NULL; // Nó já existente não possui filhos
            (*novoNode)->qtdChavesAtual++; // Aumenta a quantidade de chaves no nó criado
            (*r)->qtdChavesAtual--; // Diminui a quantidade de chaves no nó já existente
        }
        (*novoNode)->filhos[i - (*r)->grauMinimo] = (*r)->filhos[i]; // Adiciona chave mediana do nó existente no início do nó criado
        (*r)->filhos[i] = NULL; // Nó já existente não possui filhos
        insereChave(r, chave, nodeDireita);

    } else{

        for (i = (*r)->grauMinimo + 1; i < 2 * (*r)->grauMinimo; i++) { // Transfere metade das chaves do nó existente para o nó criado
            (*novoNode)->chaves[i - ((*r)->grauMinimo + 1)] = (*r)->chaves[i]; // Adiciona chave mediana do nó existente no início do nó criado
            (*r)->chaves[i]=0;
            (*novoNode)->filhos[i - ((*r)->grauMinimo + 1)] = (*r)->filhos[i]; // Promove chave do meio para o nó pai
            (*r)->filhos[i] = NULL; // Nó já existente não possui filhos
            (*novoNode)->qtdChavesAtual++; // Aumenta a quantidade de chaves no nó criado
            (*r)->qtdChavesAtual--; // Diminui a quantidade de chaves no nó já existente
        }
        (*novoNode)->filhos[i - ((*r)->grauMinimo + 1)] = (*r)->filhos[i]; // Adiciona chave mediana do nó existente no início do nó criado
        (*r)->filhos[i] = NULL; // Nó já existente não possui filhos

        insereChave(novoNode, chave, nodeDireita);
    }

    (*r)->qtdChavesAtual--; // Diminui a quantidade de chaves no nó já existente 
    *chavePromovida = (*r)->chaves[(*r)->grauMinimo]; // Aponta a chave promovida para mediana do nó
    (*r)->chaves[(*r)->grauMinimo] = 0; 
}


int busca(Node** r, int chave, Node** pos) {
    int i=0;
    *pos = NULL;
    if(r == NULL){ // Se o nó for vazio, retorne flag de status
        return -1;
    } else{
        if(chave < (*r)->chaves[0]){ // Se a chave for menor que a posição incial do nó
            return (buscaRecursivo(&(*r)->filhos[0],chave, pos)); 
        } else{
            while (i < (*r)->qtdChavesAtual && i >= 0) { // Enquanto houver chaves disponíveis
                if(chave == (*r)->chaves[i]){ // Compare a chave da posição no vetor, com a chave buscada
                    *pos = (*r); // Se achar, aponte
                    return i; // Retorne a chave
                } else if (chave > (*r)->chaves[i] && chave < (*r)->chaves[i + 1]) { // Se chave for maior que posição e menor que mediana
                    return (buscaRecursivo(&((*r)->filhos[i+1]), chave, pos)); // Busque no recursivamente no filho
                }
                i++;
            }
            if(chave == (*r)->chaves[i]){ // Compare a chave da posição no vetor, com a chave buscada
                *pos = (*r); // Se achar, aponte
                return i; // Retorne a chave
            }
            if(chave > (*r)->chaves[i]){ // Se chave for maior que a da posição
                return (buscaRecursivo(&((*r)->filhos[i]),chave, pos)); // Busque no recursivamente no filho
            }
        }
    }
}

int buscaRecursivo(Node** r, int chave, Node** pos){
    int i=0;
    if((*r) == NULL){ // Se o nó for vazio, retorne flag de status
        return -1;
    } else{
        if(chave < (*r)->chaves[0]){ // Se a chave for menor que a posição incial do nó
            return buscaRecursivo(&(*r)->filhos[0],chave, pos);
        } else{
            while (i <= (*r)->qtdChavesAtual && (*r)->chaves[i] != chave && i >= 0) { // Enquanto houver chaves disponíveis
                if(chave == (*r)->chaves[i]){ // Compare a chave da posição no vetor, com a chave buscada
                    *pos = (*r);  // Se achar, aponte
                    return i; // Retorne a chave
                } else if (chave > (*r)->chaves[i] && chave < (*r)->chaves[i + 1]) { // Se chave for maior que posição e menor que mediana
                    return buscaRecursivo(&((*r)->filhos[i+1]), chave, pos); // Busque no recursivamente no filho
                }
                i++;
            }
            if(chave == (*r)->chaves[i]){ // Compare a chave da posição no vetor, com a chave buscada
                *pos=(*r); // Se achar, aponte
                return i; // Retorne a chave
            }

            if(chave > (*r)->chaves[i]){ // Se chave for maior que a da posição
                return buscaRecursivo(&((*r)->filhos[i]),chave, pos); // Busque no recursivamente no filho
            }
        }
    }
}

