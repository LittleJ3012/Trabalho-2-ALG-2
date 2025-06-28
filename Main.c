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

        EstatisticasBTree estat;
        estat.splits = contarSplits(arvore234);
        estat.merges = 0; // nenhuma remoção ainda
        estat.altura = calcularAltura(arvore234);
        estat.blocos = contarNos(arvore234);
        estat.percentualRemocao = 0;

        salvarEstatisticasInsercao("estatisticas_insercao.csv", quantidade, &estat);

        int opMenu1;
        do {
            printf("\n--- MENU ÁRVORE 2-3-4 ---\n");
            printf("1 - Inserir novo elemento\n");
            printf("2 - Remover elementos por porcentagem\n");
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

                estat.splits = contarSplits(arvore234);
                estat.altura = calcularAltura(arvore234);
                estat.blocos = contarNos(arvore234);
                salvarEstatisticasInsercao("estatisticas_insercao.csv", quantidade, &estat);

            } else if (opMenu1 == 2) {
                float porcentagem;
                printf("\nDigite a porcentagem de elementos a serem removidos da árvore (ex: 10 para 10%%): ");
                scanf("%f", &porcentagem);

                if (porcentagem <= 0 || porcentagem > 100) {
                    printf("Porcentagem inválida.\n");
                    continue;
                }

                int totalElementos = contarNos(arvore234);
                int numRemocoes = (int)((porcentagem / 100.0f) * totalElementos);

                int* elementos = (int*)malloc(totalElementos * sizeof(int));
                if (!elementos) {
                    printf("Erro ao alocar memória.\n");
                    continue;
                }

                int totalColetados = coletaElementosBTree(arvore234, elementos, totalElementos);

                if (totalColetados < numRemocoes) {
                    printf("Não há elementos suficientes para remover %.2f%%.\n", porcentagem);
                    free(elementos);
                    continue;
                }

                for (int i = 0; i < numRemocoes; i++) {
                    removeBTree(arvore234, elementos[i]);
                }

                free(elementos);

                estat.merges = contarMerges(); 
                estat.altura = calcularAltura(arvore234);
                estat.blocos = contarNos(arvore234);
                estat.percentualRemocao = porcentagem;
                salvarEstatisticasRemocao("estatisticas_remocao.csv", &estat);

                printf("\nRemovidos %d elementos da árvore (%.2f%%).\n", numRemocoes, porcentagem);
            }

            else if (opMenu1 == 3) {
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
                        int novo;
                        printf("Digite o número a ser inserido: ");
                        scanf("%d", &novo);
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

            else if (opMenu1 == 6) {
                programaRodando = 0;
            }

        } while (opMenu1 != 5 && opMenu1 != 6);
    }

    printf("\nPrograma encerrado. Obrigada por utilizar!\n");
    return 0;
}
