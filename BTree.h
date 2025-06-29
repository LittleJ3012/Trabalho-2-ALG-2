#ifndef BTREE_H
#define BTREE_H

//===============================//
//STRUCTS PARA A ANÁLISE ESTATÍSTICA//
//===============================//

// Definições das structs para guardar estatísticas sobre as operações na árvore 2-3-4
typedef struct EstatisticasBTree EstatisticasBTree;

//===============================//
//     STRUCTS ÁRVORE 2-3-4     //
//===============================//

// Definição das structs da árvore B e de seu nó
typedef struct noBTree noBTree;
typedef struct BTree BTree;

//===============================//
//     FUNÇÕES ÁRVORE 2-3-4     //
//===============================//

// Aloca uma nova árvore B
BTree* alocaBTree();

// Aloca um novo Nó
noBTree* criaNoBTree(int folha);

// Insere um novo nó
void insereBTree(BTree *arvore, int chave);

// Realiza Split em um nó cheio
void splitNoBTree(noBTree *pai, int indice);

// Insere em um nó que ainda tem espaço
void insereNaoCheio(noBTree *no, int chave);

// Remove uma chave de um nó da B Tree
void removeBTree(BTree* arvore, int chave);

// Imprime a B Tree 2-3-4
void imprimeBTree(BTree *arvore);

// Converte a árvore B em uma árvore rubro negra
struct RB; // Forward declaration para evitar inclusão circular
struct RB *converterArvore(BTree *arvore);

//===============================//
//   MÉTRICAS E ESTATÍSTICAS    //
//===============================//

// Atualiza a altura da árvore a cada operação
int calcularAltura(BTree *arvore);

// Resseta as métricas para evitar erros
void resetarMetricas();

// Conta o número de elementos da B Tree a fim de realizar as operações de remoção
int coletaElementosBTree(BTree* arvore, int* vetor, int maxTamanho);

// Geração automática das estatísticas da B-Tree
EstatisticasBTree *gerarEstatisticasInsercao_BTree(BTree *arvore, int qtd);
EstatisticasBTree *gerarEstatisticasRemocao_BTree(BTree *arvore, float percentual);

// Salva os dados das análises estatísticas em arquivos
void salvarEstatisticasInsercao_BTree(char *nomeArquivo, int qtd, EstatisticasBTree *estat);
void salvarEstatisticasRemocao_BTree(char *nomeArquivo, EstatisticasBTree *estat);

//===============================//
// GERAÇÃO DE DADOS             //
//===============================//

// Cria um novo arquivo com números inteiros aleatórios
int criaArquivo(char *nomeArquivo, int qtd, int semente);

#endif // BTREE_H
