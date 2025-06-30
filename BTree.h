#ifndef BTREE_H
#define BTREE_H

//===============================//
//STRUCTS PARA A ANÁLISE ESTATÍSTICA//
//===============================//

// Definições das structs para guardar estatísticas sobre as operações na árvore 2-3-4
typedef struct EstatisticasBTree EstatisticasBTree;

struct EstatisticasBTree {
    int splits;
    int merges;
    int altura;
    int blocos;
    int rotacoes;
    float percentualRemocao;
};


//===============================//
//     STRUCTS ÁRVORE 2-3-4     //
//===============================//

// Definição das structs da árvore B e de seu nó
typedef struct noBTree noBTree;
typedef struct BTree BTree;

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


//===============================//
//     FUNÇÕES ÁRVORE 2-3-4     //
//===============================//

// Aloca uma nova árvore B
BTree* alocaBTree();

// Aloca um novo Nó
noBTree* criaNoBTree(int folha);

// Insere um novo nó
void insereBTree(BTree *arvore, int chave);

// Remove uma chave de um nó da B Tree
void removeBTree(BTree* arvore, int chave);

// Imprime a B Tree 2-3-4
void imprimeBTree(BTree *arvore);



//===============================//
//  FUNÇÕES AUXILIARES INSERÇÃO  //
//===============================//

// Realiza Split em um nó cheio
void splitNoBTree(noBTree *pai, int indice);

// Insere em um nó que ainda tem espaço
void insereNaoCheio(noBTree *no, int chave);



//===============================//
//  FUNÇÕES AUXILIARES REMOÇÃO   //
//===============================//

// Remove uma chave de um nó folha
void removeChaveFolha(noBTree *no, int indice);

// Encontra o predecessor de uma chave (maior chave na sub-árvore esquerda)
int encontraPredecessor(noBTree *no, int indice);

// Encontra o sucessor de uma chave (menor chave na sub-árvore direita)
int encontraSucessor(noBTree *no, int indice);

// Faz merge de um filho com seu irmão direito
void mergeFilhos(noBTree *no, int indice);

// Pega uma chave emprestada do irmão anterior
void rotacionaEsquerda(noBTree *no, int indice);

// Pega uma chave emprestada do próximo irmão
void rotacionaDireita(noBTree *no, int indice);

// Garante que um filho tenha pelo menos 2 chaves antes de descer
void garanteChavesSuficientes(noBTree *no, int indice);

// Remove uma chave de um nó específico (função recursiva principal)
void removeChaveNo(noBTree *no, int chave);



//===============================//
//   MÉTRICAS E ESTATÍSTICAS    //
//===============================//

// Atualiza a altura da árvore a cada operação
int calcularAltura(BTree *arvore);

// Resseta as métricas para evitar erros
void resetarMetricas();

// Função recursiva para contar blocos (nós) da árvore
int contarNos(noBTree *no);

// Conta o número de elementos da B Tree a fim de realizar as operações de remoção
int coletaElementosBTree(BTree* arvore, int* vetor, int maxTamanho);

// Geração automática das estatísticas da B-Tree
EstatisticasBTree *gerarEstatisticasInsercao_BTree(BTree *arvore, int qtd);
EstatisticasBTree *gerarEstatisticasRemocao_BTree(BTree *arvore, float percentual);

// Salva os dados das análises estatísticas  de inserção e remoção em arquivos
void salvarEstatisticasInsercao_BTree(char *nomeArquivo, int qtd, EstatisticasBTree *estat);
void salvarEstatisticasRemocao_BTree(char *nomeArquivo, EstatisticasBTree *estat);

//Funções que encapsulam as funções de geração e salvamento e que serão chamadas na main: 

//A variável quantidade é a quantidade de elementos que o usuário digitou na hora de criar o arquivo
//com os números inteiros
void benchmarkInsercao_BTree(BTree *arvore, int quantidade, char *arquivoCSV);

//O percentual indica a porcentagem de elementos a serem removidos da árvore 2-3-4 para fins de análise
void benchmarkRemocao_BTree(BTree *arvore, float percentual, char *arquivoCSV);


// Variável global de estatísticas
extern EstatisticasBTree estatGlobal;


//===============================//
// GERAÇÃO DE DADOS             //
//===============================//

// Cria um novo arquivo com números inteiros aleatórios
int criaArquivo(char *nomeArquivo, int qtd, int semente);

#endif // BTREE_H
