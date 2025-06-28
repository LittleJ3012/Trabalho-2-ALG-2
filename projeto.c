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


void salvarEstatisticasInsercao(char *nomeArquivo, int qtd, int splits, int altura, int blocos) {
    FILE *fp = fopen(nomeArquivo, "a");
    if (fp == NULL) {
        printf("Erro ao salvar estatísticas.\n");
        return;
    }
    fprintf(fp, "%d,%d,%d,%d\n", qtd, splits, altura, blocos);
    fclose(fp);
}

void salvarEstatisticasRemocao(char *nomeArquivo, int percentual, int altura, int blocos) {
    FILE *fp = fopen(nomeArquivo, "a");
    if (fp == NULL) {
        printf("Erro ao salvar estatísticas.\n");
        return;
    }
    fprintf(fp, "%d%%,%d,%d\n", percentual, altura, blocos);
    fclose(fp);
}


