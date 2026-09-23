#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "fila_circular.h"

struct fila {
    int inicio;
    int fim;
    int qtd;
    int capacidade;
    int *itens;
};

Fila* criar_fila(int capacidade) {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->itens = (int*) malloc(capacidade * sizeof(int));
    f->qtd = 0;
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = -1;
    printf("\nFila criada com sucesso!\n");
    return f;
}

bool esta_vazia(Fila* f) {
    return f->qtd == 0;
}

bool esta_cheia(Fila* f) {
    return f->qtd == f->capacidade;
}

void enfileirar(Fila* f, int valor) {
    if (esta_cheia(f)) {
        printf("\nFila cheia, remova um item primeiro.\n");
        return;
    }
    f->fim = (f->fim + 1) % f->capacidade;
    f->itens[f->fim] = valor;
    f->qtd++;
}

int desenfileirar(Fila* f) {
    if (esta_vazia(f)) {
        printf("\nFila vazia. Impossivel remover elementos\n");
        return -1;
    }
    int removido = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->qtd--;
    return removido;
}

int obter_primeiro(Fila* f) {
    if (esta_vazia(f)) {
        printf("\nFila vazia. Impossivel obter elementos\n");
        return INT_MIN;
    }
    return f->itens[f->inicio];
}

int main() {
    int val, opcao;

    printf("\nDigite o tamanho da fila: ");
    if (scanf("%d", &val) != 1) return 0;

    Fila* fila1 = criar_fila(val);

    while (1) {
        printf("\n************************* MENU ************************\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Obtem elemento\n");
        printf("4. Fila vazia?\n");
        printf("5. Fila cheia?\n");
        printf("6. Sair\n");
        printf("Digite sua escolha : ");

        if (scanf("%d", &opcao) != 1) break;

        switch (opcao) {
            case 1:
                printf("\nDigite o valor ");
                scanf("%d", &val);
                enfileirar(fila1, val);
                break;
            case 2:
                printf("\nElemento retirado : %d", desenfileirar(fila1));
                break;
            case 3:
                printf("\nElemento do topo: %d", obter_primeiro(fila1));
                break;
            case 4:
                if (esta_vazia(fila1)) {
                    printf("\nFila vazia");
                } else {
                    printf("\nFila nao esta vazia");
                }
                break;
            case 5:
                if (esta_cheia(fila1)) {
                    printf("\nFila cheia.");
                } else {
                    printf("\nFila nao esta cheia.");
                }
                break;
            case 6:
                free(fila1->itens);
                free(fila1);
                return 1;
            default:
                printf("\nOpcao errada!");
                break;
        }
    }
    return 0;
}