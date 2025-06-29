#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

//===============================//
//    CONSTANTES ÁRVORE 2-3-4    //
//===============================//

const int GRAU = 3;
const int ORDEM = 4;

//Structs para as análises estatísticas
struct EstatisticasBTree{
    int splits;
    int merges;
    int altura;
    int blocos;
    float percentualRemocao;
};

//Structs da B Tree / 2-3-4
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

//Função que aloca uma B Tree
BTree* alocaBTree() {
    BTree *arvore = (BTree *)malloc(sizeof(BTree));
    if (!arvore) {
        return NULL;
    }
    arvore->raiz = criaNoBTree(1);
    return arvore;
}

//Alocando um nó na B Tree
noBTree* criaNoBTree(int folha) {
    noBTree *no = (noBTree *)malloc(sizeof(noBTree));
    if (!no) {
        return NULL;
    }
    no->folha = folha;
    no->chaves = malloc(GRAU * sizeof(int));
    no->filhos = malloc((GRAU + 1) * sizeof(noBTree *));
    no->numChaves = 0;
    return no;
}

// Realiza o split de um filho cheio e indice = indiceFilho
void splitNoBTree(noBTree *pai, int indiceFilho){
    noBTree *filho = pai->filhos[indiceFilho];
    noBTree *novoNo = criaNoBTree(filho->folha);
    novoNo->numChaves = 1;

    novoNo->chaves[0] = filho->chaves[2];
    if(!filho->folha){
        // Copia os filhos da direita para o novo nó
        novoNo->filhos[0] = filho->filhos[2];
        novoNo->filhos[1] = filho->filhos[3];
        novoNo->filhos[0]->pai = novoNo;
        novoNo->filhos[1]->pai = novoNo;
    }

    filho->numChaves = 1;

    // Desloca os filhos para a direita para abrir espaço para o novo nó
    int i = 0;
    for(i=pai->numChaves; i>indiceFilho; i--){
        pai->filhos[i+1] = pai->filhos[i];
    }
    pai->filhos[indiceFilho+1] = novoNo;
    
    // Desloca as chaves para a direita e insere a nova chave
    for(i=pai->numChaves-1; i>=indiceFilho; i--){
        pai->chaves[i+1] = pai->chaves[i];
    }
    pai->chaves[indiceFilho] = filho->chaves[1];
    pai->numChaves++;
}

// Insere um nó na árvore 2-3-4
void insereBTree(BTree *arvore, int chave){
    noBTree *aux = arvore->raiz;

    if(aux->numChaves < GRAU){
        insereNaoCheio(aux, chave);
    } else {
        noBTree *novoNo = criaNoBTree(0);
        arvore->raiz = novoNo;
        novoNo->filhos[0] = aux;
        splitNoBTree(novoNo, 0);
        insereNaoCheio(novoNo, chave);
    }
}

// Insere uma chave em um nó que ainda tem espaço
void insereNaoCheio(noBTree *no, int chave){
    int i = no->numChaves-1;

    if(no->folha){
        // Caso seja uma folha, insere a chave na posição correta
        while(i>=0 && chave < no->chaves[i]){
            no->chaves[i+1] = no->chaves[i];
            i--;
        }
        no->chaves[i+1] = chave;
        no->numChaves++;
    } else {
        // Caso não seja folha, procura o filho correto para inserir descer na árvore
        while(i>=0 && chave < no->chaves[i]){
            i--;
        }
        i++;
        // Caso o filho tenha o número máximo de chaves, realiza o split
        if(no->filhos[i]->numChaves == GRAU){
            splitNoBTree(no, i);
            if(chave > no->chaves[i]){
                i++;
            }
        }
        insereNaoCheio(no->filhos[i], chave);
    }
}

//Remove uma chave de um nó da B Tree
void removeBTree(BTree* arvore, int chave);

//Imprime a B Tree 2-3-4
void imprimeBTree(BTree *arvore);

//Converte a árvore B em um árvore rubro negra
struct RB *converterArvore(BTree *arvore);


//Conta o número de splits durante as operações
int contarSplits(BTree *arvore);

//Conta o número de Merges
int contarMerges(); 

//Atualiza a altura da árvore a cada operação
int calcularAltura(BTree *arvore);

//Conta o total de nós da árvore a cada operação
int contarNos(BTree *arvore);

//Resseta as métricas para evitar erros
void resetarMetricas();


//Função auxiliar para realizar as remoções com base em porcentagem (análise estatística)
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

//Função principal para realizar a remoção com base na porcentagem fornecida
int coletaElementosBTree(BTree* arvore, int* vetor, int maxTamanho) {
    if (arvore == NULL || arvore->raiz == NULL) return 0;
    return coletaElementosBTreeRec(arvore->raiz, vetor, 0);
}



//Salva os dados das análises estatísticas em arquivos
void salvarEstatisticasInsercao_BTree(char *nomeArquivo, int qtd, EstatisticasBTree *estat);


void salvarEstatisticasRemocao_BTree(char *nomeArquivo, EstatisticasBTree *estat);


//Cria um arquivo com uma determinada quantidade de números aleatórios
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
