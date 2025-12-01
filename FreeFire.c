#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

typedef enum {
    POR_NOME = 1,
    POR_TIPO = 2,
    POR_PRIORIDADE = 3
} CriterioOrdenacao;

Item mochila[MAX];
int numItens = 0;
bool ordenadaPorNome = false;


void limparTela() {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
}

void listarItens() {
    if (numItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\n--- Itens na mochila ---\n");
    for (int i = 0; i < numItens; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("Prioridade: %d\n", mochila[i].prioridade);
    }
}

void inserirItem() {
    if (numItens == MAX) {
        printf("\nA mochila está cheia!\n");
        return;
    }

    Item novo;

    printf("\nNome: ");
    scanf("%s", novo.nome);

    printf("Tipo: ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);

    mochila[numItens] = novo;
    numItens++;

    ordenadaPorNome = false;

    printf("\nItem adicionado!\n");
}

void removerItem() {
    if (numItens == 0) {
        printf("\nNenhum item para remover.\n");
        return;
    }

    char nomeBuscado[30];
    printf("\nNome do item que deseja remover: ");
    scanf("%s", nomeBuscado);

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscado) == 0) {
            mochila[i] = mochila[numItens - 1];
            numItens--;
            printf("Item removido.\n");
            return;
        }
    }

    printf("Item não encontrado.\n");
}

int comparar(Item a, Item b, CriterioOrdenacao criterio) {
    if (criterio == POR_NOME)
        return strcmp(a.nome, b.nome);

    if (criterio == POR_TIPO)
        return strcmp(a.tipo, b.tipo);

    if (criterio == POR_PRIORIDADE)
        return b.prioridade - a.prioridade; // maior prioridade primeiro

    return 0;
}

int insertionSort(CriterioOrdenacao criterio) {
    int comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item aux = mochila[i];
        int j = i - 1;

        while (j >= 0 && comparar(mochila[j], aux, criterio) > 0) {
            mochila[j + 1] = mochila[j];
            j--;
            comparacoes++;
        }

        mochila[j + 1] = aux;
        comparacoes++;
    }

    return comparacoes;
}

void menuDeOrdenacao() {
    int opc;
    printf("\nOrdenar por:\n");
    printf("1 - Nome\n");
    printf("2 - Tipo\n");
    printf("3 - Prioridade\n");
    printf("Opção: ");
    scanf("%d", &opc);

    if (opc < 1 || opc > 3) {
        printf("Opção inválida.\n");
        return;
    }

    int comp = insertionSort(opc);
    
    if (opc == 1) ordenadaPorNome = true;
    else ordenadaPorNome = false;

    printf("\nItens ordenados! Comparações feitas: %d\n", comp);
}

void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("\nA mochila precisa estar ordenada por nome para usar busca binária.\n");
        return;
    }

    char nomeBuscado[30];
    printf("\nNome do item para buscar: ");
    scanf("%s", nomeBuscado);

    int inicio = 0, fim = numItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBuscado);

        if (cmp == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            return;
        }

        if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nItem não encontrado.\n");
}

void exibirMenu() {
    printf("\n--- MENU ---\n");
    printf("1 - Adicionar item\n");
    printf("2 - Remover item\n");
    printf("3 - Listar itens\n");
    printf("4 - Ordenar itens\n");
    printf("5 - Busca binária por nome\n");
    printf("0 - Sair\n");
    printf("Opção: ");
}

int main() {
    int opc;

    do {
        exibirMenu();
        scanf("%d", &opc);

        switch (opc) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opc != 0);

    return 0;
}