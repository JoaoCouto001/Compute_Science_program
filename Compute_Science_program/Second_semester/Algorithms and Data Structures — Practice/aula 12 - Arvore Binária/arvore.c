#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// Aloca e inicializa um novo no na memoria
No* novo_no(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: falha ao alocar memoria para o no.\n");
        return NULL;
    }
    
    // Define os valores iniciais 
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Insercao em Arvore Binaria de Busca 
No* insere(No *raiz, int valor) {
    //Se achou uma posicao vaga (ponteiro NULL), cria o no
    if (raiz == NULL) {
        return novo_no(valor);
    }

    //Navega recursivamente (menores a esquerda, maiores a direita)
    if (valor < raiz->valor) {
        raiz->esquerda = insere(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = insere(raiz->direita, valor);
    }
    // Se o valor for igual, nao insere duplicados

    return raiz;
}

// Busca recursiva por um elemento (slide 8)
No* buscar(No *raiz, int valor) {
    // Se a arvore for vazia ou se encontrou o valor procurado na raiz
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    // Busca na subarvore esquerda se for menor, senao na direita
    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    }
    return buscar(raiz->direita, valor);
}

// Auxiliar: Encontra o maior elemento a partir de um no (mais a direita possivel)
// Usado para encontrar o predecessor na remocao de nos com 2 filhos
No* maximo(No *raiz) {
    No *atual = raiz;
    while (atual != NULL && atual->direita != NULL) {
        atual = atual->direita;
    }
    return atual;
}

// Remocao lidando com os 3 casos apresentados na aula (slides 11, 13 e 14)
No* remover(No *raiz, int valor) {
    if (raiz == NULL) {
        return NULL; // Valor nao encontrado na arvore
    }

    // Navega ate encontrar o no alvo
    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        // Encontrou o no a ser removido!

        // CASO 1: No folha (sem filhos) - Slide 11
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL; // Retorna NULL para desvincular do pai
        }

        // CASO 2: No com apenas 1 filho - Slide 13
        else if (raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp; // Retorna o filho da direita para o pai reconectar
        } else if (raiz->direita == NULL) {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp; // Retorna o filho da esquerda para o pai reconectar
        }

        // CASO 3: No com 2 filhos - Slide 14
        else {
            // 1. Encontra o predecessor (maior elemento da subarvore esquerda)
            No *predecessor = maximo(raiz->esquerda);

            // 2. Troca o valor do no atual pelo valor do predecessor
            raiz->valor = predecessor->valor;

            // 3. Remove o predecessor original da subarvore esquerda
            raiz->esquerda = remover(raiz->esquerda, predecessor->valor);
        }
    }
    return raiz;
}

// Caminhamento em Ordem: Visita Esquerda -> Raiz -> Direita
void imprimir_em_ordem(No *raiz) {
    if (raiz != NULL) {
        imprimir_em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimir_em_ordem(raiz->direita);
    }
}

// Desaloca todos os nos em pos-ordem para evitar vazamento de memoria
void liberar_arvore(No *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        free(raiz);
    }
}
int main() {
    No *raiz = NULL;
    int valores[] = {4, 2, 6, 1, 3, 5, 7, 8};
    int n = sizeof(valores) / sizeof(valores[0]);

    // Inserção
    for (int i = 0; i < n; i++) {
        raiz = insere(raiz, valores[i]);
    }

    printf("Árvore em ordem: ");
    imprimir_em_ordem(raiz);
    printf("\n");

    // Busca
    int busca = 3;
    No *encontrado = buscar(raiz, busca);
    if (encontrado != NULL) {
        printf("Valor %d encontrado na árvore.\n", busca);
    } else {
        printf("Valor %d não encontrado.\n", busca);
    }

    // Remoção de nó folha
    printf("\nRemovendo nó folha (3)...\n");
    raiz = remover(raiz, 3);
    printf("Árvore em ordem: ");
    imprimir_em_ordem(raiz);
    printf("\n");

    // Remoção de nó com 1 filho
    printf("\nRemovendo nó com 1 filho (7)...\n");
    raiz = remover(raiz, 7);
    printf("Árvore em ordem: ");
    imprimir_em_ordem(raiz);
    printf("\n");

    // Remoção de nó com 2 filhos
    printf("\nRemovendo nó com 2 filhos (4)...\n");
    raiz = remover(raiz, 4);
    printf("Árvore em ordem: ");
    imprimir_em_ordem(raiz);
    printf("\n");

    liberar_arvore(raiz);
    return 0;
}