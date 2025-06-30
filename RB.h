#ifndef RB_H
#define RB_H

#include "BTree.h" 

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

#endif 
