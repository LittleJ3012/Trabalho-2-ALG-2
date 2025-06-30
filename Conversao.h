#ifndef CONVERSAO_H
#define CONVERSAO_H

#include "BTree.h"
#include "RB.h"

// Converte a árvore B em uma árvore rubro negra
RB *converterArvore(BTree *arvore);

// Converte um nó da árvore B em um nó da árvore rubro negra
noRB *converterRecursivo(RB *arvoreRB, noBTree *noB);

#endif // CONVERSAO_H