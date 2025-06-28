#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto.h"

int main(void) {
    int programaRodando = 1;

    while (programaRodando) {
        int quantidade, semente;
        char nomeArquivo[100];

        printf("\n--- GERAR ARQUIVO DE ENTRADA ---\n");
        printf("Digite o nome do arquivo a ser criado: ");
        scanf("%s", nomeArquivo);

        printf("Digite a quantidade de elementos: ");
        scanf("%d", &quantidade);

        printf("Digite a semente de geração randômica: ");
        scanf("%d", &semente);

        criaArquivo(nomeArquivo, quantidade, semente);

        BTree *arvore234 = alocaBTree(2);
        resetarMetricas();

        FILE *arquivo = fopen(nomeArquivo, "r");
        if (!arquivo) {
            printf("Erro ao abrir o arquivo!\n");
            continue;
        }

        int valor;
        while (fscanf(arquivo, "%d", &valor) != EOF) {
            insereBTree(arvore234, valor);
        }
        fclose(arquivo);

        printf("\n--- Árvore 2-3-4 criada com sucesso! ---\n");
        imprimeBTree(arvore234);

        EstatisticasBTree *estat = gerarEstatisticasInsercao_BTree(arvore234, quantidade);
        salvarEstatisticasInsercao_BTree("estatisticas_insercao.csv", quantidade, estat);

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
                estat = gerarEstatisticasInsercao_BTree(arvore234, quantidade);
                salvarEstatisticasInsercao_BTree("estatisticas_insercao.csv", quantidade, estat);

            } else if (opMenu1 == 2) {
                int rem;
                printf("Digite o número que deseja remover: ");
                scanf("%d", &rem);
                removeBTree(arvore234, rem);
                printf("Elemento %d removido da árvore.\n", rem);

            } else if (opMenu1 == 3) {
                imprimeBTree(arvore234);

            } else if (opMenu1 == 4) {
                RB *rubroNegra = converterArvore(arvore234);
                printf("\n--- Árvore Rubro-Negra ---\n");
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

                    } else if (opcaoRB == 2) {
                        int rem;
                        printf("Digite o número a ser removido: ");
                        scanf("%d", &rem);
                        removeArvoreRB(rubroNegra, rem);

                    } else if (opcaoRB == 3) {
                        percorrePreOrdem(rubroNegra, retornaRaizRB(rubroNegra));
                    }
                } while (opcaoRB != 4);
            }

            else if (opMenu1 == 5) {
                programaRodando = 0; // Sai do loop para criar novo arquivo
            }

        } while (opMenu1 != 5 && opMenu1 != 6);

        // ============================
        // ANÁLISE ESTATÍSTICA PÓS MENU
        // ============================

        // Executa a análise de benchmarking apenas se a árvore tiver 10 mil elementos
            printf("\nAnálise de benchmarking (remoção por porcentagem)...\n");

            float percentuais[] = {10, 20, 35, 50};
            int totalElementos = contarNos(arvore234);
            int *elementos = (int*)malloc(totalElementos * sizeof(int));
            coletaElementosBTree(arvore234, elementos, totalElementos);

            for (int i = 0; i < 4; i++) {
                float pct = percentuais[i];
                resetarMetricas(); // Zera os contadores

                BTree *copia = alocaBTree(2);
                for (int j = 0; j < totalElementos; j++) {
                    insereBTree(copia, elementos[j]);
                }

                int remover = (int)((pct / 100.0f) * totalElementos);
                for (int j = 0; j < remover; j++) {
                    removeBTree(copia, elementos[j]);
                }

                EstatisticasBTree *estatRem = gerarEstatisticasRemocao_BTree(copia, pct);
                salvarEstatisticasRemocao_BTree("estatisticas_remocao.csv", estatRem);
                free(estatRem);
            }

            free(elementos);

        // Análise estatística da árvore Rubro-Negra convertida
        printf("\nGerando estatísticas da árvore Rubro-Negra final...\n");
        RB *rbFinal = converterArvore(arvore234);
        EstatisticasRB *estatRB = gerarEstatisticasRemocao_RB(rbFinal, quantidade);
        salvarEstatisticasRemocao_RB("estatisticas_rb.csv", estatRB);
        free(estatRB);

        free(estat);
        if (opMenu1 == 6) programaRodando = 0;
        
    }

    printf("\nPrograma encerrado. Obrigada por utilizar!\n");
    return 0;
}

