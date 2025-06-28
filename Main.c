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

        // Gera arquivo com inteiros aleatórios
        criaArquivo(nomeArquivo, quantidade, semente);

        // Cria árvore 2-3-4 a partir do arquivo
        BTree *arvore234 = alocaBTree(2);  // grau mínimo 2 (2-3-4)

        resetarMetricas(); // Zera contadores de splits e nós

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

        // Calcula estatísticas e salva no CSV
        int splits = contarSplits(arvore234);
        int altura = calcularAltura(arvore234);
        int blocos = contarNos(arvore234);
        salvarEstatisticasInsercao("estatisticas_insercao.csv", quantidade, splits, altura, blocos);

        int opMenu1;
        do {
            printf("\n--- MENU ÁRVORE 2-3-4 ---\n");
            printf("1 - Inserir novo elemento\n");
            printf("2 - Remover elemento\n");
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

            } else if (opMenu1 == 2) {
                int rem;
                printf("Digite o número a ser removido: ");
                scanf("%d", &rem);
                removeBTree(arvore234, rem);

                // Atualiza estatísticas após remoção 
                int novaAltura = calcularAltura(arvore234);
                int novosBlocos = contarNos(arvore234);
                salvarEstatisticasRemocao("estatisticas_remocao.csv", 0, novaAltura, novosBlocos); // 0 = "remoção manual"

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
            } else if (opMenu1 == 6) {
                programaRodando = 0;
            }
        } while (opMenu1 != 5 && opMenu1 != 6);
    }

    printf("\nPrograma encerrado. Obrigada por utilizar!\n");
    return 0;
}
