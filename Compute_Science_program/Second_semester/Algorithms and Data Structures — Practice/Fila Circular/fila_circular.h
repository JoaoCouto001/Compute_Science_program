#ifndef FILA_CIRCULAR_H
#define FILA_CIRCULAR_H

#include <stdbool.h>

typedef struct fila Fila;

Fila* criar_fila(int capacidade);
bool esta_vazia(Fila* f);
bool esta_cheia(Fila* f);
void enfileirar(Fila* f, int valor);
int desenfileirar(Fila* f);
int obter_primeiro(Fila* f);

#endif