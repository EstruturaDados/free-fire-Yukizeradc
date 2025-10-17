#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definicao da struct Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Funcao para inserir um item na mochila
void inserirItem(struct Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens >= MAX_ITENS) {
        printf("A mochila esta cheia!\n");
        return;
    }

    printf("Digite o nome do item: ");
    fgets(mochila[*quantidadeItens].nome, 30, stdin);
    mochila[*quantidadeItens].nome[strcspn(mochila[*quantidadeItens].nome, "\n")] = 0;

    printf("Digite o tipo do item (arma, municao, cura): ");
    fgets(mochila[*quantidadeItens].tipo, 20, stdin);
    mochila[*quantidadeItens].tipo[strcspn(mochila[*quantidadeItens].tipo, "\n")] = 0;

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*quantidadeItens].quantidade);
    getchar(); // Limpa buffer

    (*quantidadeItens)++;
    printf("Item %s adicionado com sucesso!\n", mochila[*quantidadeItens - 1].nome);
}

// Funcao para remover um item pelo nome
void removerItem(struct Item mochila[], int *quantidadeItens) {
    char nome[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < *quantidadeItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *quantidadeItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*quantidadeItens)--;
            encontrado = 1;
            printf("Item %s removido com sucesso!\n", nome);
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }
}

// Funcao para listar todos os itens
void listarItens(struct Item mochila[], int quantidadeItens) {
    if (quantidadeItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < quantidadeItens; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Funcao para buscar um item pelo nome
void buscarItem(struct Item mochila[], int quantidadeItens) {
    char nome[30];
    printf("Digite o nome do item a ser buscado: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < quantidadeItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado.\n");
    }
}

int main() {
    struct Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;

    do {
        printf("\nMENU:\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

        switch(opcao) {
            case 1:
                inserirItem(mochila, &quantidadeItens);
                break;
            case 2:
                removerItem(mochila, &quantidadeItens);
                break;
            case 3:
                listarItens(mochila, quantidadeItens);
                break;
            case 4:
                buscarItem(mochila, quantidadeItens);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
