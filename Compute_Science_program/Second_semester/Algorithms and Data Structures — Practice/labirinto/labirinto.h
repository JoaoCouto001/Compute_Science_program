#ifndef _H_LABIRINTO
#define _H_LABIRINTO

/**
 * Célula do labirinto (cada quadrado).
 * 
 * char tipo: tipo da célula ('X' para parede, '0' para caminho, 'E' para entrada e 'S' para saída).
 * 
 * celula* 'direção': ponteiro para a célula acima/abaixo/ a esquerda/ a direita.
 * 
 * celula* proximo: ponteiro para a próxima célula do caminho encontrado pelo algoritmo.
 * 
 * int i, j: coordenadas da célula no labirinto (linha e coluna).
 * 
 * int visitado: flag para marcar se a célula já foi visitada pelo algoritmo (1 para visitada, 0 para não visitada).
 */
typedef struct celula{
    char tipo;
    struct celula* cima;
    struct celula* baixo;
    struct celula* esquerda;
    struct celula* direita;

    struct celula* proximo;
    int i;
    int j;

    int visitado;
}celula;

/**
 * Estrutura Labirinto.
 * 
 * struct celula* entrada: ponteiro para a célula de entrada do labirinto.
 * 
 * struct celula* saida: ponteiro para a célula de saída do labirinto.
 */
struct labirinto{
    struct celula* entrada;
    struct celula* saida;
}*labirinto;

// Libera a memória alocada para o labirinto.
int liberaMemoria();

/**
 * Lê o arquivo txt e cria o labirinto.
 * 
 * escolha: Qual labirinto será carregado (fácil, sem saída, difícil).
 * 
 * struct celula* ponteiro[10][10]: matriz de ponteiros para as células do labirinto.
 * 
 * struct celula* percorre: ponteiro auxiliar para percorrer a matriz de células.
 * 
 * @return Retorna 0 se o labirinto foi criado com sucesso, ou -1 se houve algum erro.
 */
int criaLabirinto(int escolha);

/**
 * Imprime o labirinto com a posição do jogador.
 * 
 * Lê a matriz de células do labirinto e imprime cada célula, substituindo a célula atual do jogador por 'P'.
 */
void imprimeLabirintoComJogador(celula* jogador);

// Imprime o labirinto, mas sem a posição do jogador (para o algoritmo).
void imprimeLabirinto();

// Função para jogar o labirinto.
void jogarLabirinto();

/**
 * Mostra o caminho encontrado pelo algoritmo.
 * 
 *  Usa uma lista encadeada de células (proximo) para percorrer o caminho do labirinto e imprimir as coordenadas de cada célula do caminho.
 */
void mostrarCaminho();

/**
 * Função recursiva para buscar a saída do labirinto.
 * 
 * A função explora as 4 direções (cima, baixo, esquerda e direita) a partir da célula atual, marcando as células visitadas e construindo o caminho encontrado.
 * 
 * @param atual Ponteiro para a célula atual sendo explorada.
 * @return Retorna 1 se a saída foi encontrada, ou 0 se não há caminho válido.
 */
int buscaSaida(celula *atual);

/**
 * Algoritmo usado para a resolução do labirinto.
 * 
 * Funciona recursivamente, explorando as 4 direções (cima, baixo, esquerda e direita) a partir da célula atual.
 */
void mazeCrawler();

#endif