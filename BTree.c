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
    no->pai = NULL;
    
    for (int i = 0; i <= GRAU; i++) {
        no->filhos[i] = NULL;
    }
    
    return no;
}

// Realiza o split de um filho cheio e indice = indiceFilho
void splitNoBTree(noBTree *pai, int indiceFilho){
    noBTree *filho = pai->filhos[indiceFilho];
    noBTree *novoNo = criaNoBTree(filho->folha);
    novoNo->numChaves = 1;
    novoNo->pai = pai;

    novoNo->chaves[0] = filho->chaves[2];
    if(!filho->folha){
        // Copia os filhos da direita para o novo nó
        novoNo->filhos[0] = filho->filhos[2];
        novoNo->filhos[1] = filho->filhos[3];
        if (novoNo->filhos[0] != NULL) {
            novoNo->filhos[0]->pai = novoNo;
        }
        if (novoNo->filhos[1] != NULL) {
            novoNo->filhos[1]->pai = novoNo;
        }
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
        aux->pai = novoNo;
        splitNoBTree(novoNo, 0);
        insereNaoCheio(novoNo, chave);
    }
}

// Insere uma chave em um nó que ainda tem espaço
void insereNaoCheio(noBTree *no, int chave){
    int i = 0;

    // Verifica se a chave já existe, evitando valores duplicados
    for(i = 0; i < no->numChaves; i++){
        if(no->chaves[i] == chave){
            return;
        }
    }

    i = no->numChaves-1;
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

// Remove uma chave de um nó folha
void removeChaveFolha(noBTree *no, int indice){
    int i = 0;
    for(i = indice; i < no->numChaves - 1; i++){
        no->chaves[i] = no->chaves[i + 1];
    }
    no->numChaves--;
}

// Encontra o predecessor de uma chave (maior chave na sub-árvore esquerda)
int encontraPredecessor(noBTree *no, int indice){
    noBTree *aux = no->filhos[indice];
    while(!aux->folha){
        aux = aux->filhos[aux->numChaves];
    }
    return aux->chaves[aux->numChaves - 1];
}

// Encontra o sucessor de uma chave (menor chave na sub-árvore direita)
int encontraSucessor(noBTree *no, int indice){
    noBTree *aux = no->filhos[indice + 1];
    while(!aux->folha){
        aux = aux->filhos[0];
    }
    return aux->chaves[0];
}

// Faz merge de um filho com seu irmão direito
void mergeFilhos(noBTree *no, int indice){
    noBTree *filho = no->filhos[indice];
    noBTree *irmao = no->filhos[indice + 1];
    
    // Move a chave do nó atual para o filho
    filho->chaves[filho->numChaves] = no->chaves[indice];
    filho->numChaves++;
    
    // Copia as chaves do irmão para o filho
    int i = 0;
    for(i = 0; i < irmao->numChaves; i++){
        filho->chaves[filho->numChaves + i] = irmao->chaves[i];
    }
    
    // Copia os filhos do irmão se não for folha
    if(!filho->folha){
        for(i = 0; i <= irmao->numChaves; i++){
            filho->filhos[filho->numChaves + i] = irmao->filhos[i];
            if(irmao->filhos[i] != NULL){
                irmao->filhos[i]->pai = filho;
            }
        }
    }
    filho->numChaves += irmao->numChaves;
    
    // Remove a chave do nó atual
    for(i = indice; i < no->numChaves - 1; i++){
        no->chaves[i] = no->chaves[i + 1];
    }
    
    // Remove o ponteiro do irmão
    for(i = indice + 1; i < no->numChaves; i++){
        no->filhos[i] = no->filhos[i + 1];
    }
    
    no->numChaves--;
    free(irmao);
}

// Pega uma chave emprestada do irmão anterior
void pegaEmprestadoDoAnterior(noBTree *no, int indice){
    noBTree *filho = no->filhos[indice];
    noBTree *irmao = no->filhos[indice - 1];
    
    // Move todas as chaves do filho uma posição à frente
    int i = 0;
    for(i = filho->numChaves; i > 0; i--){
        filho->chaves[i] = filho->chaves[i - 1];
    }
    
    // Se não for folha, move os filhos também
    if(!filho->folha){
        for(i = filho->numChaves + 1; i > 0; i--){
            filho->filhos[i] = filho->filhos[i - 1];
        }
        filho->filhos[0] = irmao->filhos[irmao->numChaves];
        if(irmao->filhos[irmao->numChaves] != NULL){
            irmao->filhos[irmao->numChaves]->pai = filho;
        }
    }
    
    // Move a chave do pai para o filho
    filho->chaves[0] = no->chaves[indice - 1];
    filho->numChaves++;
    
    // Move a última chave do irmão para o pai
    no->chaves[indice - 1] = irmao->chaves[irmao->numChaves - 1];
    irmao->numChaves--;
}

// Pega uma chave emprestada do próximo irmão
void pegaEmprestadoDoProximo(noBTree *no, int indice){
    noBTree *filho = no->filhos[indice];
    noBTree *irmao = no->filhos[indice + 1];
    
    // Move a chave do pai para o final do filho
    filho->chaves[filho->numChaves] = no->chaves[indice];
    filho->numChaves++;
    
    // Se não for folha, move o primeiro filho do irmão
    if(!filho->folha){
        filho->filhos[filho->numChaves] = irmao->filhos[0];
        if(irmao->filhos[0] != NULL){
            irmao->filhos[0]->pai = filho;
        }
    }
    
    // Move a primeira chave do irmão para o pai
    no->chaves[indice] = irmao->chaves[0];
    
    // Remove a primeira chave do irmão
    int i = 0;
    for(i = 0; i < irmao->numChaves - 1; i++){
        irmao->chaves[i] = irmao->chaves[i + 1];
    }
    
    // Se não for folha, move os filhos do irmão
    if(!irmao->folha){
        for(i = 0; i < irmao->numChaves; i++){
            irmao->filhos[i] = irmao->filhos[i + 1];
        }
    }
    
    irmao->numChaves--;
}

// Garante que um filho tenha pelo menos 2 chaves antes de descer
void garanteChavesSuficientes(noBTree *no, int indice){
    noBTree *filho = no->filhos[indice];
    
    if(filho->numChaves >= 2){
        return;
    }
    
    // Verifica se pode pegar emprestado com algum dos irmãos
    if(indice > 0 && no->filhos[indice - 1]->numChaves >= 2){
        pegaEmprestadoDoAnterior(no, indice);
    } else if(indice < no->numChaves && no->filhos[indice + 1]->numChaves >= 2){
        pegaEmprestadoDoProximo(no, indice);
    } else {
        // Se não, faz merge com o irmão da direita se possível, caso contrário, com o da esquerda
        if(indice < no->numChaves){
            mergeFilhos(no, indice);
        } else {
            mergeFilhos(no, indice - 1);
        }
    }
}

// Remove uma chave de um nó específico
void removeChaveNo(noBTree *no, int chave){
    int indiceChave = -1;
    int i = 0;

    for(i=0; i<no->numChaves; i++){
        if(no->chaves[i] == chave){
            indiceChave = i;
            break;
        }
    }
    
    if(indiceChave != -1){
        if(no->folha){
            removeChaveFolha(no, indiceChave);
        } else {
            noBTree *filhoEsq = no->filhos[indiceChave];
            noBTree *filhoDir = no->filhos[indiceChave + 1];
            
            // Vê se algum dos filhos tem chaves suficientes, se não, faz merge
            if(filhoEsq->numChaves >= 2){
                int predecessor = encontraPredecessor(no, indiceChave);
                no->chaves[indiceChave] = predecessor;
                removeChaveNo(filhoEsq, predecessor);
            } else if (filhoDir->numChaves >= 2) {
                int sucessor = encontraSucessor(no, indiceChave);
                no->chaves[indiceChave] = sucessor;
                removeChaveNo(filhoDir, sucessor);
            } else {
                mergeFilhos(no, indiceChave);
                removeChaveNo(filhoEsq, chave);
            }
        }
    } else {
        // Chave não encontrada
        if(no->folha){
            return;
        }
        
        // Encontra o filho correto para descer
        int i = 0;
        while(i < no->numChaves && chave > no->chaves[i]){
            i++;
        }
        
        // Garante que o filho tenha pelo menos 2 chaves
        garanteChavesSuficientes(no, i);
        
        // Como pode ter ocorrido um merge, a estrutura pode ter mudado, então atualizamos o indice
        if(i > no->numChaves){
            removeChaveNo(no->filhos[i - 1], chave);
        } else {
            removeChaveNo(no->filhos[i], chave);
        }
    }
}

// Remove uma chave da árvore
void removeBTree(BTree *arvore, int chave) {
    if(arvore == NULL || arvore->raiz == NULL){
        return;
    }
    
    removeChaveNo(arvore->raiz, chave);
    
    // Se a raiz ficou vazia e não é folha, promove o único filho
    if(arvore->raiz->numChaves == 0 && !arvore->raiz->folha){
        noBTree *raizVelha = arvore->raiz;
        arvore->raiz = arvore->raiz->filhos[0];
        arvore->raiz->pai = NULL;
        free(raizVelha);
    }
}

void imprimeBTreeRec(noBTree *no, int nivel){
    if(no == NULL){
        return;
    }

    int i = 0;
    for(i = 0; i < nivel; i++){
        printf("  ");
    }
    
    printf("|-- [");
    for(i = 0; i < no->numChaves; i++){
        printf("%d", no->chaves[i]);
        if(i < no->numChaves - 1){
            printf(", ");
        }
    }
    printf("]\n");
    
    for(i = 0; i <= no->numChaves; i++){
        imprimeBTreeRec(no->filhos[i], nivel + 1);
    }
}

//Imprime a B Tree 2-3-4
void imprimeBTree(BTree *arvore){
    if(arvore == NULL || arvore->raiz == NULL){
        return;
    }
    imprimeBTreeRec(arvore->raiz, 0);
}

// Calcula a altura da árvore descendo pelo filho mais a esquerda
// pois pela propriedade da B Tree, a altura é a mesma para todos os nós
int calcularAltura(BTree *arvore) {
    int altura = 0;
    noBTree *aux = arvore->raiz;
    while(aux != NULL){
        altura++;
        aux = aux->filhos[0];
    }
    return altura;
}

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
