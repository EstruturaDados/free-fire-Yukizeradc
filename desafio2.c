#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== Estruturas =====
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

#define MAX 100

Item mochilaVetor[MAX];
int tamanhoVetor = 0;

// Inserir item no vetor
void inserirItemVetor(Item novo) {
    if (tamanhoVetor < MAX) {
        mochilaVetor[tamanhoVetor++] = novo;
        printf("Item inserido no vetor!\n");
    } else {
        printf("Mochila cheia!\n");
    }
}

// Remover item por nome
void removerItemVetor(char nome[]) {
    int i, j;
    for (i = 0; i < tamanhoVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (j = i; j < tamanhoVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            tamanhoVetor--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

// Listar itens
void listarItensVetor() {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < tamanhoVetor; i++) {
        printf("%s - %s - %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
    }
}

No* inicio = NULL;

// Inserir item
void inserirItemLista(Item novo) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = inicio;
    inicio = novoNo;
    printf("Item inserido na lista!\n");
}

// Remover item por nome
void removerItemLista(char nome[]) {
    No *atual = inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado!\n");
        return;
    }

    if (anterior == NULL) inicio = atual->proximo;
    else anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido da lista!\n");
}

// Listar itens
void listarItensLista() {
    No* atual = inicio;
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    while (atual != NULL) {
        printf("%s - %s - %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

int comparacoes = 0;

// Busca sequencial
int buscarSequencialVetor(char nome[]) {
    comparacoes = 0;
    for (int i = 0; i < tamanhoVetor; i++) {
        comparacoes++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("Item encontrado!\n");
            return i;
        }
    }
    printf("Item nao encontrado!\n");
    return -1;
}

// Ordenar vetor (Bubble Sort)
void ordenarVetor() {
    Item temp;
    for (int i = 0; i < tamanhoVetor - 1; i++) {
        for (int j = 0; j < tamanhoVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados!\n");
}

// Busca binária
int buscarBinariaVetor(char nome[]) {
    int inicio = 0, fim = tamanhoVetor - 1;
    comparacoes = 0;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0) {
            printf("Item encontrado!\n");
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Item nao encontrado!\n");
    return -1;
}

void menu() {
    int opcao, estrutura;
    Item novo;
    char nome[30];

    printf("Escolha a estrutura: 1-Vetor 2-Lista: ");
    scanf("%d", &estrutura);

    do {
        printf("\n--- MENU ---\n");
        printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar item\n5. Ordenar (vetor)\n0. Sair\n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Nome: "); gets(novo.nome);
                printf("Tipo: "); gets(novo.tipo);
                printf("Quantidade: "); scanf("%d", &novo.quantidade);
                if (estrutura == 1) inserirItemVetor(novo);
                else inserirItemLista(novo);
                break;
            case 2:
                printf("Nome: "); gets(nome);
                if (estrutura == 1) removerItemVetor(nome);
                else removerItemLista(nome);
                break;
            case 3:
                if (estrutura == 1) listarItensVetor();
                else listarItensLista();
                break;
            case 4:
                printf("Nome: "); gets(nome);
                if (estrutura == 1) {
                    buscarSequencialVetor(nome);
                    printf("Comparacoes: %d\n", comparacoes);
                } else printf("(Busca apenas sequencial na lista)\n");
                break;
            case 5:
                if (estrutura == 1) ordenarVetor();
                else printf("Nao ha ordenacao na lista encadeada!\n");
                break;
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
