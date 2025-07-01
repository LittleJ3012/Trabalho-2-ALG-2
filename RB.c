#include <stdio.h>
#include <stdlib.h>
#include "RB.h"

//Funções da árvore rubro negra:

//Aloca memória para a árvore Red Black
RB *alocaArvoreRB(){
    // Aloca espaço para a estrutura da árvore
    RB *a = (RB*)malloc(sizeof(RB));
    if (a == NULL) {
        return NULL;
    }

    // Aloca e inicializa o nó sentinela
    a->sentinela = (noRB*)malloc(sizeof(noRB));
    if (a->sentinela == NULL) {
        free(a);
        return NULL;
    }

    // Configura o nó sentinela como um nó preto e "nulo"
    a->sentinela->esq = a->sentinela;
    a->sentinela->dir = a->sentinela;
    a->sentinela->pai = a->sentinela;
    a->sentinela->cor = 'P'; // Cor preta
    a->sentinela->chave = -1; // Valor para chave nula

    // Define a raiz como sendo o próprio sentinela (árvore vazia)
    a->sentinela->esq = a->sentinela; // raiz = sentinela->esq

    return a;
}

//Aloca um nó da árvore Red Black
noRB *criaNoRB(RB *a, int chave){
    noRB *novoNo = (noRB*)malloc(sizeof(noRB));

    if(!novoNo){
        return NULL;
    }

    novoNo->esq = a->sentinela;
    novoNo->dir = a->sentinela;
    novoNo->pai = a->sentinela;
    novoNo->cor = 'V';
    novoNo->chave = chave;
    return novoNo;
}

//Insere um novo nó na red black
void insereArvoreRB(RB *a, noRB *no){
    noRB *raiz = a->sentinela->esq;

    if(raiz == a->sentinela){
        a->sentinela->esq = no;
        no->pai = a->sentinela;
        no->esq = a->sentinela;
        no->dir = a->sentinela;
        no->cor = 'V';
        balanceaInsercao(a, no);
        return;
    }

    noRB *pai = a->sentinela;
    noRB *atual = raiz;

    while(atual != a->sentinela){
        pai = atual;
        if(no->chave < atual->chave){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }

    no->pai = pai;
    no->esq = a->sentinela;
    no->dir = a->sentinela;
    no->cor = 'V';

    if(no->chave < pai->chave){
        pai->esq = no;
    }else{
        pai->dir = no;
    }

    balanceaInsercao(a, no);
}

//Remove um elemento da árvore rubro negra
int removeArvoreRB(RB *a, int chave){
    noRB *atual = a->sentinela->esq;

    while(atual != a->sentinela && atual->chave != chave){
        if(chave < atual->chave){
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if(atual == a->sentinela){
        return 0; 
    }

    noRB *noRemovido = atual;
    noRB *filho;
    noRB *paiRemovido = atual->pai;
    char corOriginal = atual->cor;

    if(atual->esq != a->sentinela && atual->dir != a->sentinela){
        noRB *sucessor = atual->dir;
        while(sucessor->esq != a->sentinela){
            sucessor = sucessor->esq;
        }
        
        atual->chave = sucessor->chave;

        noRemovido = sucessor;
        paiRemovido = sucessor->pai;
        corOriginal = sucessor->cor;
    }

    if(noRemovido->esq != a->sentinela){
        filho = noRemovido->esq;
    } else {
        filho = noRemovido->dir;
    }

    if(filho != a->sentinela){
        filho->pai = noRemovido->pai;
    }
    
    if(noRemovido->pai == a->sentinela){
        a->sentinela->esq = filho; //Se for raiz
    } else if(noRemovido == noRemovido->pai->esq){
        noRemovido->pai->esq = filho; //Filho da esquerda
    } else {
        noRemovido->pai->dir = filho; //Filho da direita
    }

    // Só faz balanceamento se removeu um nó preto
    if(corOriginal == 'P'){
        balanceaRemocao(a, filho, paiRemovido);
    }
    
    free(noRemovido);

    return 1; 
}

//Imprime a árvore em pré ordem
void percorrePreOrdem(RB *a, noRB *no){
    if (no != a->sentinela){
        printf("\n%c - %d.", no->cor, no->chave);
        percorrePreOrdem(a, no->esq);
        percorrePreOrdem(a, no->dir);
    }
}

//Realiza o balanceamento após uma inserção
void balanceaInsercao(RB *a, noRB *z){
     while (z->pai->cor == 'V') {
        noRB *pai = z->pai;
        noRB *avo = pai->pai;

        if (pai == avo->esq) {
            noRB *tio = avo->dir;

            if (tio->cor == 'V') {
                // Caso 1: Tio é vermelho -> recoloração
                pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                z = avo; // Sobe a árvore
            } else {
                if (z == pai->dir) {
                    // Caso 2: Zig-zag esquerda-direita
                    z = pai;
                    rotacaoEsquerda(a, z);
                    pai = z->pai; // atualiza ponteiros após rotação
                    avo = pai->pai;
                }
                // Caso 3: Zig-zig esquerda-esquerda
                pai->cor = 'P';
                avo->cor = 'V';
                rotacaoDireita(a, avo);
            }

        } else {
            noRB *tio = avo->esq;

            if (tio->cor == 'V') {
                // Caso 1: Tio é vermelho -> recoloração
                pai->cor = 'P';
                tio->cor = 'P';
                avo->cor = 'V';
                z = avo;
            } else {
                if (z == pai->esq) {
                    // Caso 2: Zig-zag direita-esquerda
                    z = pai;
                    rotacaoDireita(a, z);
                    pai = z->pai;
                    avo = pai->pai;
                }
                // Caso 3: Zig-zig direita-direita
                pai->cor = 'P';
                avo->cor = 'V';
                rotacaoEsquerda(a, avo);
            }
        }
    }

    // Garante que a raiz está sempre preta
    a->sentinela->esq->cor = 'P';
}

//Realiza o balanceamento após uma remoção
void balanceaRemocao(RB *a, noRB *y, noRB *pai) {
    while (y != a->sentinela->esq && y->cor == 'P') {
        if (y == pai->esq) {
            // Irmão à direita
            noRB *w = pai->dir;

            // Caso 1: irmão vermelho
            if (w->cor == 'V') {
                w->cor = 'P';
                pai->cor = 'V';
                rotacaoEsquerda(a, pai);
            }
            // Caso 2: irmão e filhos pretos
            else if ((w->esq == a->sentinela || w->esq->cor == 'P') &&
                (w->dir == a->sentinela || w->dir->cor == 'P')) {
                w->cor = 'V';
                y = pai;
                pai = y->pai;
            }
            // Caso 3: irmão preto com filho esquerdo vermelho e direito preto
            else if (w->dir == a->sentinela || w->dir->cor == 'P') {
                if (w->esq != a->sentinela)
                    w->esq->cor = 'P';
                w->cor = 'V';
                rotacaoDireita(a, w);
            }
            // Caso 4: irmão preto com filho direito vermelho
            else if (w != a->sentinela) {
                w->cor = pai->cor;
                pai->cor = 'P';
                if (w->dir != a->sentinela)
                    w->dir->cor = 'P';
                rotacaoEsquerda(a, pai);
                y = a->sentinela->esq; // termina o loop
            }
            
        } else {
            // Irmão à esquerda
            noRB *w = pai->esq;

            // Caso 1: irmão vermelho
            if (w->cor == 'V') {
                w->cor = 'P';
                pai->cor = 'V';
                rotacaoDireita(a, pai);
            }
            // Caso 2: irmão e filhos pretos
            else if ((w->esq == a->sentinela || w->esq->cor == 'P') &&
                (w->dir == a->sentinela || w->dir->cor == 'P')) {
                w->cor = 'V';
                y = pai;
                pai = y->pai;
            }
            // Caso 3: irmão preto com filho direito vermelho e esquerdo preto
            else if (w->esq == a->sentinela || w->esq->cor == 'P') {
                if (w->dir != a->sentinela)
                    w->dir->cor = 'P';
                w->cor = 'V';
                rotacaoEsquerda(a, w);
            }
            // Caso 4: irmão preto com filho esquerdo vermelho
            else if (w != a->sentinela) {
                w->cor = pai->cor;
                pai->cor = 'P';
                if (w->esq != a->sentinela)
                    w->esq->cor = 'P';
                rotacaoDireita(a, pai);
                y = a->sentinela->esq; // termina o loop
            }
        }
    }

    if (y != a->sentinela)
        y->cor = 'P';

    // Garante que a raiz é preta
    a->sentinela->esq->cor = 'P';
}


//Realiza uma rotação à esquerda
void rotacaoEsquerda(RB *a, noRB *noDesbalanceado){
    noRB *x = noDesbalanceado->dir;
    noDesbalanceado->dir = x->esq;
    
    if(x->esq) x->esq->pai = noDesbalanceado;
    
    x->pai = noDesbalanceado->pai;
    
    if(noDesbalanceado->pai == a->sentinela){
        a->sentinela->esq = x;
    }else if(noDesbalanceado->pai->dir == noDesbalanceado){
        noDesbalanceado->pai->dir = x;
    }else{
        noDesbalanceado->pai->esq = x;
    }
    
    x->esq = noDesbalanceado;
    noDesbalanceado->pai = x;
}

//Realiza uma rotação à direita
void rotacaoDireita(RB *a, noRB *noDesbalanceado){
    noRB *y = noDesbalanceado->esq;
    noDesbalanceado->esq = y->dir;
    
    if(y->dir) y->dir->pai = noDesbalanceado;
    
    y->pai = noDesbalanceado->pai;
    
    if(noDesbalanceado->pai == a->sentinela){
        a->sentinela->esq = y;
    }else if(noDesbalanceado->pai->dir == noDesbalanceado){
        noDesbalanceado->pai->dir = y;
    }else{
        noDesbalanceado->pai->esq = y;
    }
    
    y->dir = noDesbalanceado;
    noDesbalanceado->pai = y;
}

//Retorna a raiz da árvore rubro NEGRA
noRB *retornaRaizRB(RB *a){
    return a->sentinela->esq;
}
