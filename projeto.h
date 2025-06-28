#ifndef PROJETO_H
#define PROJETO_H

//===============================//
//    CONSTANTES ÁRVORE 2-3-4    //
//===============================//

const int GRAU = 3;
const int ORDEM = 4;

//===============================//
//     STRUCTS ÁRVORE 2-3-4     //
//===============================//

typedef struct noBTree noBTree;
typedef struct BTree BTree;

// Struct para guardar estatísticas
typedef struct EstatisticasBTree EstatisticasBTree;
typedef struct EstatisticasRB EstatisticasRB;

//===============================//
//     FUNÇÕES ÁRVORE 2-3-4     //
//===============================//

BTree *alocaBTree();
noBTree *criaNoBTree(int folha);
void insereBTree(BTree *arvore, int chave);
void splitNoBTree(noBTree *pai, int indice);
void insereNaoCheio(noBTree *no, int chave);
void removeBTree(BTree* arvore, int chave);
void imprimeBTree(BTree *arvore);
struct RB *converterArvore(BTree *arvore);

//===============================//
//   MÉTRICAS E ESTATÍSTICAS    //
//===============================//

int contarSplits(BTree *arvore);
int contarMerges(); // novo
int calcularAltura(BTree *arvore);
int contarNos(BTree *arvore);
void resetarMetricas();
int coletaElementosBTree(BTree* arvore, int* vetor, int maxTamanho);
void salvarEstatisticasInsercao(char *nomeArquivo, int qtd, EstatisticasBTree *estat);
void salvarEstatisticasRemocao(char *nomeArquivo, EstatisticasBTree *estat);

//===============================//
//     STRUCTS ÁRVORE RB        //
//===============================//

typedef struct noRB noRB;
typedef struct RB RB;

//===============================//
//     FUNÇÕES ÁRVORE RB        //
//===============================//

RB *alocaArvoreRB();
noRB *criaNoRB(RB *a, int chave);
void insereArvoreRB(RB *a, int chave);
void percorrePreOrdem(RB *a, noRB *no);
void balanceaInsercao(RB *a, noRB *z);
void balanceaRemocao(RB *a, noRB *y, noRB *pai);
void rotacaoEsquerda(RB *a, noRB *noDesbalanceado);
void rotacaoDireita(RB *a, noRB *noDesbalanceado);
noRB* retornaRaizRB(RB *a);
void removeArvoreRB(RB *a, int chave);

//===============================//
// GERAÇÃO DE DADOS             //
//===============================//

int criaArquivo(char *nomeArquivo, int qtd, int semente);

#endif // PROJETO_H

