#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

struct noBTree {
    int *chaves;
    struct noBTree **filhos;
    struct noBTree *pai;
    int numChaves;
    int folha;
};

struct BTree {
    noBTree *raiz;
};

BTree* alocaBTree() {
    BTree *arvore = (BTree *)malloc(sizeof(BTree));
    if (!arvore) {
        return NULL;
    }
    arvore->raiz = criaNoBTree(1);
    return arvore;
}

noBTree* criaNoBTree(int folha) {
    noBTree *no = (noBTree *)malloc(sizeof(noBTree));
    if (!no) {
        return NULL;
    }
    no->ehFolha = folha;
    no->chaves = malloc(GRAU * sizeof(int));
    no->filhos = malloc((GRAU + 1) * sizeof(noBTree *));
    no->numChaves = 0;
    return no;
}

void insereBTree(BTree *arvore, int chave){
    noBTree *aux = arvore->raiz;

    // Desce na árvore até encontrar uma folha
    while(!aux->ehFolha){
        int iteradorChave=0;
        int indiceFilho=0;

        while(iteradorChave < aux->numChaves && chave > aux->chaves[iteradorChave]){
            iteradorChave++;
        }

        // Indica qual filho deve ser visitado
        indiceFilho = iteradorChave; 
        aux = &aux->filhos[indiceFilho];
    }

    // TODO: Inserir chave na folha
}

struct EstatisticasBTree{
    int splits;
    int merges;
    int altura;
    int blocos;
    float percentualRemocao;
};


struct EstatisticasRB{
    int rotacoesEsq;
    int rotacoesDir;
    int altura;
    int blocos;
};

int criaArquivo(char *nomeArquivo, int qtd, int semente){
    int num;
    
    FILE *arq = fopen(nomeArquivo, "w");
    if(!arq){
        return 1;
    }
    
    srand(semente);
    
    for(int i=0; i< qtd; i++){
        num = rand() % 1000;
        fprintf(arq, "%d\n", num);
    }
    
    fclose(arq);
    return 0;
    
}


int coletaElementosBTreeRec(noBTree* no, int* vetor, int indice) {
    if (no == NULL) return indice;

    int i;
    for (i = 0; i < no->numChaves; i++) {
        if (!no->folha)
            indice = coletaElementosBTreeRec(no->filhos[i], vetor, indice);
        vetor[indice++] = no->chaves[i];
    }

    if (!no->folha)
        indice = coletaElementosBTreeRec(no->filhos[i], vetor, indice);

    return indice;
}

int coletaElementosBTree(BTree* arvore, int* vetor, int maxTamanho) {
    if (arvore == NULL || arvore->raiz == NULL) return 0;
    return coletaElementosBTreeRec(arvore->raiz, vetor, 0);
}



