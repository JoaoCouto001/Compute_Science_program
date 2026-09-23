#ifndef ARVORE_H
#define ARVORE_H

// Estrutura do no conforme a definição do slide 6
// Contem o valor armazenado e dois ponteiros para as subarvores
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
} No;

// Prototipos das operacoes basicas solicitadas (slide 7)
No* novo_no(int valor);
No* insere(No *raiz, int valor);
No* buscar(No *raiz, int valor);
No* remover(No *raiz, int valor);

// Funcoes auxiliares para os testes e remocao
No* maximo(No *raiz);            // Encontra o predecessor (maior elemento da subarvore esquerda)
void imprimir_em_ordem(No *raiz);  // Caminhamento para verificar se a arvore esta ordenada
void liberar_arvore(No *raiz);     // Libera toda a memoria alocada para evitar memory leak

#endif