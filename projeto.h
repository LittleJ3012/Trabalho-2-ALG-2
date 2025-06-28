#ifndef PROJETO_H
#define PROJETO_H

//===============================//
//     STRUCTS ÁRVORE 2-3-4     //
//===============================//

typedef struct noBTree noBTree;

typedef struct BTree BTree;


//===============================//
//     FUNÇÕES ÁRVORE 2-3-4     //
//===============================//

// Aloca a estrutura principal da árvore
BTree *alocaBTree(int grau);

// Cria um novo nó da árvore B
noBTree *criaNoBTree(int grau, int folha);

// Insere uma chave na árvore B
void insereBTree(BTree *arvore, int chave);

// Função auxiliar que realiza o split de um nó cheio durante a inserção
void splitNoBTree(noBTree *pai, int indice, int grau);

// Insere em um nó que não está cheio (chamada recursiva de insereBTree)
void insereNaoCheio(noBTree *no, int chave, int grau);

// Remove uma chave da árvore B
void removeBTree(BTree* arvore, int chave);

// Imprime a árvore B (2-3-4)
void imprimeBTree(BTree *arvore);

// Converte a árvore 2-3-4 para rubro-negra
struct RB *converterArvore(BTree *arvore);


//===============================//
//     MÉTRICAS E ESTATÍSTICAS    //
//===============================//


// Conta quantos splits ocorreram
int contarSplits(BTree *arvore);

// Calcula a altura da árvore B
int calcularAltura(BTree *arvore);

// Conta a quantidade total de nós
int contarNos(BTree *arvore);

// Reseta as métricas globais de splits, merges etc.
void resetarMetricas();

// Roda testes de inserção e coleta estatísticas
void estatisticasInsercao(BTree *arvore, int tamanhoAmostra);

// Roda testes de remoção e coleta estatísticas
void estatisticasRemocao(BTree *arvore, int percentualRemocao);


//===============================//
//     STRUCTS ÁRVORE RB        //
//===============================//

typedef struct noRB noRB;

typedef struct RB RB;

//===============================//
//     FUNÇÕES ÁRVORE RB        //
//===============================//

// Aloca a árvore rubro-negra
RB *alocaArvoreRB();

// Cria um novo nó com a chave informada
noRB *criaNoRB(RB *a, int chave);

// Insere um elemento na árvore rubro-negra
void insereArvoreRB(RB *a, int chave);

// Imprime a árvore rubro-negra (preordem com número e cor)
void percorrePreOrdem(RB *a, noRB *no);

// Realiza o balanceamento após inserção
void balanceaInsercao(RB *a, noRB *z);

// Realiza o balanceamento após remoção
void balanceaRemocao(RB *a, noRB *y, noRB *pai);

// Rotação à esquerda
void rotacaoEsquerda(RB *a, noRB *noDesbalanceado);

// Rotação à direita
void rotacaoDireita(RB *a, noRB *noDesbalanceado);

// Retorna a raiz da árvore rubro-negra
noRB* retornaRaizRB(RB *a);

// Remove um nó com a chave informada da árvore rubro-negra
void removeArvoreRB(RB *a, int chave);


//===============================//
//FUNÇÃO PARA GERAR ARQUIVOS COM INTEIROS //
//===============================//

// Geração de arquivo com inteiros aleatórios
int criaArquivo(char *nomeArquivo, int qtd, int semente);


//===============================//
//FUNÇÕES PARA SALVAR AS ESTATÍSTICAS DA ÁRVORE 2-3-4 EM ARQUIVOS//
//===============================//
void salvarEstatisticasInsercao(char *nomeArquivo, int qtd, int splits, int altura, int blocos);
void salvarEstatisticasRemocao(char *nomeArquivo, int percentual, int altura, int blocos);


#endif // PROJETO_H
