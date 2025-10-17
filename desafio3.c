#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

int comparacoes = 0;

// Função para limpar o buffer do stdin
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para mostrar todos os componentes
void mostrarComponentes(Componente comp[], int n) {
    printf("\nComponentes:\n");
    printf("%-30s %-15s %-10s\n", "Nome", "Tipo", "Prioridade");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-30s %-15s %-10d\n", comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
    printf("\n");
}

// Bubble Sort por nome (string)
void bubbleSortNome(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n -1; i++) {
        for (int j = 0; j < n - i -1; j++) {
            comparacoes++;
            if (strcmp(comp[j].nome, comp[j+1].nome) > 0) {
                Componente temp = comp[j];
                comp[j] = comp[j+1];
                comp[j+1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo (string)
void insertionSortTipo(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = comp[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (strcmp(comp[j].tipo, chave.tipo) > 0) {
                comp[j+1] = comp[j];
                j--;
            } else {
                break;
            }
        }
        comp[j+1] = chave;
    }
}

// Selection Sort por prioridade (int)
void selectionSortPrioridade(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            comparacoes++;
            if (comp[j].prioridade < comp[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Componente temp = comp[i];
            comp[i] = comp[min_idx];
            comp[min_idx] = temp;
        }
    }
}

// Busca binária por nome (após ordenação por nome)
int buscaBinariaPorNome(Componente comp[], int n, char chave[]) {
    int inicio = 0;
    int fim = n - 1;
    comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(comp[meio].nome, chave);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

int main() {
    Componente componentes[MAX_COMPONENTES];
    int n = 0;
    int opcao;
    char buscaNome[30];

    printf("Cadastro de Componentes (max 20). Para parar, digite nome vazio.\n");
    while (n < MAX_COMPONENTES) {
        printf("Componente %d\n", n+1);
        printf("Nome: ");
        fgets(componentes[n].nome, 30, stdin);
        componentes[n].nome[strcspn(componentes[n].nome, "\n")] = 0;
        if (strlen(componentes[n].nome) == 0) break;

        printf("Tipo: ");
        fgets(componentes[n].tipo, 20, stdin);
        componentes[n].tipo[strcspn(componentes[n].tipo, "\n")] = 0;

        printf("Prioridade (1-10): ");
        scanf("%d", &componentes[n].prioridade);
        limparBuffer();

        n++;
        printf("\n");
    }

    do {
        printf("Escolha uma opcao:\n");
        printf("1 - Ordenar por nome (Bubble Sort)\n");
        printf("2 - Ordenar por tipo (Insertion Sort)\n");
        printf("3 - Ordenar por prioridade (Selection Sort)\n");
        printf("4 - Buscar componente-chave por nome (Busca Binaria)\n");
        printf("5 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        clock_t inicio_tempo, fim_tempo;
        double tempo;

        switch(opcao) {
            case 1:
                inicio_tempo = clock();
                bubbleSortNome(componentes, n);
                fim_tempo = clock();
                tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
                printf("Ordenacao por nome concluida.\nComparacoes: %d\nTempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 2:
                inicio_tempo = clock();
                insertionSortTipo(componentes, n);
                fim_tempo = clock();
                tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
                printf("Ordenacao por tipo concluida.\nComparacoes: %d\nTempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 3:
                inicio_tempo = clock();
                selectionSortPrioridade(componentes, n);
                fim_tempo = clock();
                tempo = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;
                printf("Ordenacao por prioridade concluida.\nComparacoes: %d\nTempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(componentes, n);
                break;

            case 4:
                printf("Digite o nome do componente-chave para busca binaria (deve estar ordenado por nome): ");
                fgets(buscaNome, 30, stdin);
                buscaNome[strcspn(buscaNome, "\n")] = 0;

                int idx = buscaBinariaPorNome(componentes, n, buscaNome);
                printf("Comparacoes na busca: %d\n", comparacoes);

                if (idx != -1) {
                    printf("Componente encontrado:\n");
                    printf("%-30s %-15s %-10d\n", componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                } else {
                    printf("Componente nao encontrado.\n");
                }
                break;

            case 5:
                mostrarComponentes(componentes, n);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
