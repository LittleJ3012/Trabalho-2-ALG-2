#ifndef PROJETO_H
#define PROJETO_H

//===============================//
//STRUCTS PARA A ANÁLISE ESTATÍSTICA//
//===============================//

// Definições das structs para guardar estatísticas sobre as operações nas árvores
typedef struct EstatisticasBTree EstatisticasBTree;

typedef struct EstatisticasRB EstatisticasRB;

//===============================//
//     STRUCTS ÁRVORE 2-3-4     //
//===============================//

//Definição das structs da árvore B e de seu nó
typedef struct noBTree noBTree;
typedef struct BTree BTree;

//===============================//
//     FUNÇÕES ÁRVORE 2-3-4     //
//===============================//

//Aloca uma nova árvore B
BTree *alocaBTree(int grau);

//Aloca um novo Nó
noBTree *criaNoBTree(int grau, int folha);

//Insere um novo nó
void insereBTree(BTree *arvore, int chave);

//Realiza Split em um nó cheio
void splitNoBTree(noBTree *pai, int indice, int grau);

//Insere em um nó que ainda tem espaço
void insereNaoCheio(noBTree *no, int chave, int grau);

//Remove uma chave de um nó da B Tree
void removeBTree(BTree* arvore, int chave);

//Imprime a B Tree 2-3-4
void imprimeBTree(BTree *arvore);

//Converte a árvore B em um árvore rubro negra
struct RB *converterArvore(BTree *arvore);

//===============================//
//   MÉTRICAS E ESTATÍSTICAS    //
//===============================//

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

//Conta o número de elementos da B Tree a fim de realizar as operações de remoção
int coletaElementosBTree(BTree* arvore, int* vetor, int maxTamanho);

// Geração automática das estatísticas da B-Tree
EstatisticasBTree *gerarEstatisticasInsercao_BTree(BTree *arvore, int qtd);
EstatisticasBTree *gerarEstatisticasRemocao_BTree(BTree *arvore, float percentual);

//Salva os dados das análises estatísticas em arquivos
void salvarEstatisticasInsercao_BTree(char *nomeArquivo, int qtd, EstatisticasBTree *estat);
void salvarEstatisticasRemocao_BTree(char *nomeArquivo, EstatisticasBTree *estat);


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
void percorrePreOrdem(RB *a, noRB *no);
void balanceaInsercao(RB *a, noRB *z);
void balanceaRemocao(RB *a, noRB *y, noRB *pai);
void rotacaoEsquerda(RB *a, noRB *noDesbalanceado);
void rotacaoDireita(RB *a, noRB *noDesbalanceado);
noRB *retornaRaizRB(RB *a);
void removeArvoreRB(RB *a, int chave);




// Geração automática das estatísticas da RB
EstatisticasRB *gerarEstatisticasRemocao_RB(RB *arvore, int qtd);
void salvarEstatisticasRemocao_RB(char *nomeArquivo, EstatisticasRB *estat);


//===============================//
// GERAÇÃO DE DADOS             //
//===============================//

//Cria um novo arquivo com números inteiros aleatórios
int criaArquivo(char *nomeArquivo, int qtd, int semente);



#endif // PROJETO_H
