#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"
#include "RB.h"
#include "Conversao.h"

int main(void) {
    int programaRodando = 1;

    while (programaRodando) {
        
        //Variáveis necessárias para a função de criar o arquivo:
        
        int quantidade, semente;
        char nomeArquivo[100];

        printf("\n--- GERAR ARQUIVO DE ENTRADA ---\n");
        
        //Usuário informa o nome do arquivo que será criado com números inteiros
        printf("Digite o nome do arquivo a ser criado: ");
        scanf("%s", nomeArquivo);

        //Usuário informa o tamanho do arquivo (que será a árvore 2-3-4 original)
        printf("Digite a quantidade de elementos: ");
        scanf("%d", &quantidade);

        //Usuário digita a semente de geração randômica
        printf("Digite a semente de geração randômica: ");
        scanf("%d", &semente);

        //Chamada da função criaArquivo
        criaArquivo(nomeArquivo, quantidade, semente);

        //Chamada da função que realiza a alocação da árvore 2-3-4
        BTree *arvore234 = alocaBTree(2);
        resetarMetricas();

        //Verificação de erros ao abrir o arquivo que foi criado
        FILE *arquivo = fopen(nomeArquivo, "r");
        if (!arquivo) {
            printf("Erro ao abrir o arquivo!\n");
            continue;
        }

        //Insere todos os números do arquivo na árvore 2-3-4
        int valor;
        while (fscanf(arquivo, "%d", &valor) != EOF) {
            insereBTree(arvore234, valor);
        }
        fclose(arquivo);

        //Mensagem de validação
        printf("\n--- Árvore 2-3-4 criada com sucesso! ---\n");
        imprimeBTree(arvore234);

        //Início do menu principal da árvore 2-3-4
        int opMenu1;
        do {
            printf("\n--- MENU ÁRVORE 2-3-4 ---\n");
            printf("1 - Inserir novo elemento\n");
            printf("2 - Remover elemento da árvore\n");
            printf("3 - Imprimir árvore\n");
            printf("4 - Converter em árvore rubro-negra\n");
            printf("5 - Gerar novo arquivo (voltar ao início)\n");
            printf("6 - Sair do programa\n");
            printf("Escolha: ");
            scanf("%d", &opMenu1);

            if (opMenu1 == 1) {
                int novo;
                printf("Digite o número a ser inserido: ");
                scanf("%d", &novo);
                insereBTree(arvore234, novo);
            } 
            else if (opMenu1 == 2) {
                int rem;
                printf("Digite o número que deseja remover: ");
                scanf("%d", &rem);
                removeBTree(arvore234, rem);
                printf("Elemento %d removido da árvore.\n", rem);
            } 
            else if (opMenu1 == 3) {
                imprimeBTree(arvore234);
            } 
            else if (opMenu1 == 4) {
                RB *rubroNegra = converterArvore(arvore234);
                printf("\n--- Árvore Rubro-Negra ---\n");
                //Imprimindo a árvore rubro negra criada:
                percorrePreOrdem(rubroNegra, retornaRaizRB(rubroNegra));

                int opcaoRB;
                do {
                    printf("\n--- MENU ÁRVORE RUBRO-NEGRA ---\n");
                    printf("1 - Inserir novo elemento\n");
                    printf("2 - Remover elemento\n");
                    printf("3 - Imprimir árvore\n");
                    printf("4 - Sair\n");
                    printf("Escolha: ");
                    scanf("%d", &opcaoRB);

                    if (opcaoRB == 1) {
                        int val;
                        printf("Digite o número a ser inserido: ");
                        scanf("%d", &val);
                        noRB *novo = criaNoRB(rubroNegra, val);
                        insereArvoreRB(rubroNegra, novo);
                    } 
                    else if (opcaoRB == 2) {
                        int rem;
                        printf("Digite o número a ser removido: ");
                        scanf("%d", &rem);
                        removeArvoreRB(rubroNegra, rem);
                    } 
                    else if (opcaoRB == 3) {
                        percorrePreOrdem(rubroNegra, retornaRaizRB(rubroNegra));
                    }
                } while (opcaoRB != 4);
            }

        } while (opMenu1 != 5 && opMenu1 != 6);//Programa continua até que o usuário digite 5 ou 6

        // ===========================
        // ANÁLISE ESTATÍSTICA (FINAL)
        // ===========================

        //Chama a função de benchmarking para coletar os dados e salva-los em um arquivo
        printf("\nGerando benchmarking da 2-3-4 com inserções...\n");
        benchmarkInsercao_BTree(arvore234, quantidade, "estatisticas_insercao.txt");

        if(quantidade == 10000){//Realiza a análise estatística da remoção somente em testes
        //com 10 mil elementos
            
        printf("\nGerando benchmarking da 2-3-4 com remoções parciais...\n");
        float percentuaisBTree[] = {10, 20, 35, 50};//Porcentagens que serão utilizdas

        int *elementos = (int *)malloc(quantidade * sizeof(int));
        int totalElementos = coletaElementosBTree(arvore234, elementos, quantidade);

        for (int i = 0; i < 4; i++) {
            float pct = percentuaisBTree[i];
            resetarMetricas();//Métricas são resetadas para cada porcentagem testada

            BTree *copia = alocaBTree(2); //Cópia para evitar erros
            for (int j = 0; j < totalElementos; j++) {
                insereBTree(copia, elementos[j]);
            }

            //Remove um determinado número de elementos da B Tree, de acordo com a porcentagem
            //fornecida pelo usuário
            int remover = (int)((pct / 100.0f) * totalElementos);
            for (int j = 0; j < remover; j++) {
                removeBTree(copia, elementos[j]);
            }

            //Chama a função que guarda as informações sobre as análises estatísticas em 
            //um arquivo de texto
            benchmarkRemocao_BTree(copia, pct, "estatisticas_remocao.txt");
        }

        free(elementos); //Libera a memória do vetor auxiliar
    
        }
        
        if (opMenu1 == 6) {
            programaRodando = 0;//Para encerrar o loop while
        }
    }

    printf("\nPrograma encerrado. Obrigado por utilizar!\n");
    return 0;
}
