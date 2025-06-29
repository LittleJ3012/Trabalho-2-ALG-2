#ifndef RB_H
#define RB_H

#include "BTree.h" 

//===============================//
//STRUCT PARA A ANÁLISE ESTATÍSTICA//
//===============================//

// Definição da struct para guardar estatísticas sobre as operações na Red Black
typedef struct EstatisticasRB EstatisticasRB;

//===============================//
// STRUCTS ÁRVORE RUBRO NEGRA    //
//===============================//

typedef struct noRB noRB;
typedef struct RB RB;

//===============================//
//     FUNÇÕES ÁRVORE RB        //
//===============================//

//Aloca memória para a árvore Red Black
RB *alocaArvoreRB();

//Aloca um nó da árvore Red Black
noRB *criaNoRB(RB *a, int chave);

//Insere um novo nó na red black
void insereArvoreRB(RB *a, noRB *no);

//Remove um elemento da árvore rubro negra
int removeArvoreRB(RB *a, int chave);

//Imprime a árvore em pré ordem
void percorrePreOrdem(RB *a, noRB *no);

//Realiza o balanceamento após uma inserção
void balanceaInsercao(RB *a, noRB *z);

//Realiza o balanceamento após uma remoção
void balanceaRemocao(RB *a, noRB *y, noRB *pai);

//Realiza uma rotação à esquerda
void rotacaoEsquerda(RB *a, noRB *noDesbalanceado);

//Realiza uma rotação à direita
void rotacaoDireita(RB *a, noRB *noDesbalanceado);

//Retorna a raiz da árvore rubro NEGRA
noRB *retornaRaizRB(RB *a);

//Calcula a altura da árvore Rubro NEGRA
int alturaRB(RB *a, noRB *no);

// Geração automática das estatísticas da RB
void salvarEstatisticasRemocao_RB(char *nomeArquivo, EstatisticasRB *estat);
EstatisticasRB *gerarEstatisticasRemocao_RB(RB *arvore, float percentual, int qtd);

void benchmarkRemocao_RB(BTree *original, float percentual, char *arquivoCSV);

//Resseta as rotações da árvore rubro negra
void resetarRubroNegra(RB *a);

#endif 
