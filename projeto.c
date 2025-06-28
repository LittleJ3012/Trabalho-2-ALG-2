#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

struct noBTree {
    int *chaves;
    int grau; // grau mínimo (t)
    struct noBTree **filhos;
    int numChaves;
    int folha;
};

struct BTree {
    noBTree *raiz;
    int grauMinimo; 
};

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



