#include <stdio.h>

// Função de inserção na fila circular (indexação de 1 a M)
int insere(int no, int F[], int M, int *f, int *r) {
    int insere_val = -1; // Retorna -1 em caso de fila cheia
    int prov = (*r % M) + 1; // Cálculo da posição provisória (r mod M + 1)

    if (prov != *f) { // Verifica se há espaço disponível
        *r = prov; // Atualiza a retaguarda
        F[*r] = no; // Insere o elemento
        insere_val = *r;
        
        if (*f == 0) { // Se a fila estava vazia, inicializa o início em 1
            *f = 1;
        }
    }

    return insere_val; // Retorna a posição de inserção ou -1
}



print