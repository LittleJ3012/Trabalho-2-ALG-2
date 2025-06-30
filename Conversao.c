#include <stdlib.h>
#include "Conversao.h"

noRB *converterRecursivo(RB *arvoreRB, noBTree *noB) {
    // caso base. Se nao tem mais filhos (é folha), aponta para a sentinela
    if (noB == NULL) {
        return arvoreRB->sentinela;
    }

    // caso de nó vazio (0 chaves) - retorna sentinela
    if (noB->numChaves == 0) {
        return arvoreRB->sentinela;
    }

    noRB *subRaiz; //raiz da subarvore que estamos tratando

    if (noB->numChaves == 1) { // se só tem 1 chave
        /*
        [X]                 (X - Preto)
        /  \                   /    \
    [esq]  [dir]     (avalia esq)  (avalia direito)
        */
        subRaiz = criaNoRB(arvoreRB, noB->chaves[0]);
        subRaiz->cor = 'P'; // no caso de apenas 1 chave pintamos o nó de preto e continuamos
        subRaiz->esq = converterRecursivo(arvoreRB, noB->filhos[0]); //percorre recursivamente a esquerda e depois a direita, usando pre ordem
        subRaiz->dir = converterRecursivo(arvoreRB, noB->filhos[1]);

        if(subRaiz->esq != arvoreRB->sentinela){
            subRaiz->esq->pai = subRaiz;
        }
        if(subRaiz->dir != arvoreRB->sentinela){
            subRaiz->dir->pai = subRaiz;
        }
        
    } else if (noB->numChaves == 2) { // se tem 2 chaves
        /* Representaçao para auxiliar o entendimento das funcoes

        [X,Y]                     (X - Preto)
        /  \  \                    /    \
  [f.esq][f.dir][f.dir] (avalia esq)  (Y - Vermelho)
                                        /       \
                                (avalia esq)  (avalia direito)
        */
        subRaiz = criaNoRB(arvoreRB, noB->chaves[0]); //pintamos o primeiro elemento de preto
        subRaiz->cor = 'P';
        noRB *filhoDir = criaNoRB(arvoreRB, noB->chaves[1]); //pintamos o segundo elemento de vermelho
        filhoDir->cor = 'V'; 
        
        subRaiz->dir = filhoDir; 
        filhoDir->pai = subRaiz;
        
        subRaiz->esq = converterRecursivo(arvoreRB, noB->filhos[0]);
        filhoDir->esq = converterRecursivo(arvoreRB, noB->filhos[1]);
        filhoDir->dir = converterRecursivo(arvoreRB, noB->filhos[2]);
        
        if(subRaiz->esq != arvoreRB->sentinela){
            subRaiz->esq->pai = subRaiz;
        }
        if(filhoDir->esq != arvoreRB->sentinela){
            filhoDir->esq->pai = filhoDir;
        }
        if(filhoDir->dir != arvoreRB->sentinela){
            filhoDir->dir->pai = filhoDir;
        }

    

    } else if (noB->numChaves == 3) {
        /* Representaçao para auxiliar o entendimento das funcoes
        
       [X,Y,Z]                              (Y    -    Preto)
        /\ /\                              /                \
   [f.esq][f.esq][f.dir][f.dir]     (X - Vermelho)          (Z - Vermelho)
                                    /       \                  /       \
                            (avalia esq)(avalia direito)  (avalia esq)(avalia direito)
                            
        */
        subRaiz = criaNoRB(arvoreRB, noB->chaves[1]); // segundo elemento de preto, seus filhos (1 e 2) de vemelho
        subRaiz->cor = 'P';
        noRB *filhoEsq = criaNoRB(arvoreRB, noB->chaves[0]);
        filhoEsq->cor = 'V';
        noRB *filhoDir = criaNoRB(arvoreRB, noB->chaves[2]);
        filhoDir->cor = 'V';
        
        subRaiz->esq = filhoEsq;
        filhoEsq->pai = subRaiz;

        subRaiz->dir = filhoDir;
        filhoDir->pai = subRaiz;
        
        filhoEsq->esq = converterRecursivo(arvoreRB, noB->filhos[0]);
        filhoEsq->dir = converterRecursivo(arvoreRB, noB->filhos[1]);
        filhoDir->esq = converterRecursivo(arvoreRB, noB->filhos[2]);
        filhoDir->dir = converterRecursivo(arvoreRB, noB->filhos[3]);

        if(filhoEsq->esq != arvoreRB->sentinela)
            filhoEsq->esq->pai = filhoEsq;
        if(filhoEsq->dir != arvoreRB->sentinela)
            filhoEsq->dir->pai = filhoEsq;
        if(filhoDir->esq != arvoreRB->sentinela)
            filhoDir->esq->pai = filhoDir;
        if(filhoDir->dir != arvoreRB->sentinela)
            filhoDir->dir->pai = filhoDir;
    }
    
    return subRaiz;
}

RB *converterArvore(BTree *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        return NULL;
    }

    RB *arvoreRB = alocaArvoreRB();
    if(!arvoreRB){
        return NULL;
    }

    arvoreRB->sentinela->esq = converterRecursivo(arvoreRB, arvore->raiz); 
    if (arvoreRB->sentinela->esq != arvoreRB->sentinela) { // se a arvore nao estiver vazia
        arvoreRB->sentinela->esq->pai = arvoreRB->sentinela;
    }

    return arvoreRB;
}