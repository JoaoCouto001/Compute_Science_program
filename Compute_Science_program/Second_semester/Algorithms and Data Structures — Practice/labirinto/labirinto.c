#include <stdlib.h>
#include <stdio.h>

// Celula da matriz do labirinto.
typedef struct celula
{
    char tipo;
    struct celula *cima;
    struct celula *baixo;
    struct celula *esquerda;
    struct celula *direita;

    // Para mostrar o caminho do labirinto.
    struct celula *proximo;
    int i;
    int j;

    // Para marcar se a célula já foi visitada pelo algoritmo.
    int visitado;
} celula;

// Estrutura labirinto.
struct labirinto
{
    struct celula *entrada;
    struct celula *saida;
} *labirinto;

/**
 * Libera a memória alocada para o labirinto.
 * 
 * Usada ao escolher outro labirinto ou ao encerrar o programa.
 */
int liberaMemoria(){
    celula *linha = labirinto->entrada;

    // Libera cada célula do labirinto.
    while (linha != NULL){
        celula *proximaLinha = linha->baixo;
        celula *col = linha;

        while (col != NULL){
            celula *temp = col;
            col = col->direita;
            free(temp);
        }

        linha = proximaLinha;
    }
    // Libera a estrutura do labirinto.
    free(labirinto);
    labirinto = NULL;

    return 0;
}

/**  Leitura do arquivo txt e criação do labirinto.
 *
 * O labirinto é lido de um arquivo txt, onde cada célula é representada por um caractere.
 *
 * Uma matriz de ponteiros é usada para armazenar e mapear as células do labirinto.
 */
int criaLabirinto(int escolha)
{
    // Libera memória do labirinto anterior, se houver.
    if(labirinto != NULL)
    liberaMemoria();

    struct celula *ponteiro[10][10];
    struct celula *percorre;

    //Alocação de memória para a estrutura do labirinto
    labirinto = (struct labirinto *)malloc(sizeof(struct labirinto));
    if (labirinto == NULL)
    {
        printf("Erro ao alocar memoria para o labirinto.\n");
        return 1;
    }
    labirinto->entrada = NULL;
    labirinto->saida = NULL;

    // Leitura do arquivo.
    FILE *arquivo;

    if(escolha == 1)
        arquivo = fopen("labirinto_facil.txt", "r");

    else if(escolha == 2)
        arquivo = fopen("labirinto_sem_saida.txt", "r");

    else if(escolha == 3)
        arquivo = fopen("labirinto_dificil.txt", "r");
        
    if (arquivo == NULL)
    {
        printf("Erro ao ler arquivo, certifique-se que existe o arquivo correspondente.");
        return 1;
    }

    //  Lê a matriz.
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            celula *novo = (struct celula *)malloc(sizeof(celula));
            novo->tipo = fgetc(arquivo);
            novo->proximo = NULL;
            novo->visitado = 0;

            while (novo->tipo == '\n' || novo->tipo == '\r')
            {
                novo->tipo = fgetc(arquivo);
            }
            ponteiro[i][j] = novo;

            if (novo->tipo == 'E')
                labirinto->entrada = novo;
            else if (novo->tipo == 'S')
                labirinto->saida = novo;
        }
    }

    // Mapeia o labirinto.
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            percorre = ponteiro[i][j];
            percorre->i = i;
            percorre->j = j;

            // Se i = 0, então 'cima' = fora do labirinto.
            if (i > 0)
                percorre->cima = ponteiro[i - 1][j];
            else
                percorre->cima = NULL;

            // Se i = 9, então 'baixo' = fora do labirinto.
            if (i < 9)
                percorre->baixo = ponteiro[i + 1][j];
            else
                percorre->baixo = NULL;

            // Se j = 0; então 'esquerda' = fora do labirinto;
            if (j > 0)
                percorre->esquerda = ponteiro[i][j - 1];
            else
                percorre->esquerda = NULL;

            // Se j = 9; então 'direita' = fora do labirinto.
            if (j < 9)
                percorre->direita = ponteiro[i][j + 1];
            else
                percorre->direita = NULL;
        }
    }

    return 0;
}

// Função para imprimir o labirinto com a posição do jogador.
void imprimeLabirintoComJogador(celula* jogador) {
    if (labirinto == NULL || labirinto->entrada == NULL) {
        printf("Labirinto não inicializado.\n");
        return;
    }

    // Percorre o labirinto e imprime cada célula.
    celula* linha = labirinto->entrada;
    while (linha != NULL) {
        celula* col = linha;
        while (col != NULL) {
            if (col == jogador) {
                printf("P ");
            } else {
                printf("%c ", col->tipo);
            }
            col = col->direita;
        }
        printf("\n");
        linha = linha->baixo;
    }
}

// função de imprimir o labirinto (sem o jogador)
void imprimeLabirinto() {
    imprimeLabirintoComJogador(NULL);
}

// Função para jogar o labirinto.
void jogarLabirinto() {
    //
    if (labirinto == NULL || labirinto->entrada == NULL) {
        printf("\nErro: O labirinto nao foi carregado.\n");
        return;
    }

    celula* atual = labirinto->entrada;
    char comando;

    printf("\n================ MODO JOGO ================\n");
    printf("Controlo: [W] Cima | [S] Baixo | [A] Esquerda | [D] Direita | [Q] Sair\n");

    // Loop principal do jogo.
    while (atual != NULL) {
        printf("\n-------------------------------------------\n");
        imprimeLabirintoComJogador(atual);

        if (atual->tipo == 'S') {
            printf("\n🎉 Parabéns! Chegou a saída ('S') do labirinto!\n");
            break;
        }

        printf("\nMovimento (W/A/S/D) ou Q para sair: ");
        scanf(" %c", &comando);

        celula* proxima = NULL;

        // Determina a próxima célula com base no comando do jogador.
        switch (comando) {
            case 'w': case 'W':
                proxima = atual->cima;
                break;
            case 's': case 'S':
                proxima = atual->baixo;
                break;
            case 'a': case 'A':
                proxima = atual->esquerda;
                break;
            case 'd': case 'D':
                proxima = atual->direita;
                break;
            case 'q': case 'Q':
                printf("\nSaindo do jogo...\n");
                liberaMemoria();
                return;
            default:
                printf("\nOpção inválida! Use W, A, S, D ou Q.\n");
                continue;
        }

        // Verifica se o movimento é válido.
        if (proxima == NULL) {
            printf("\n⚠️  Movimento inválido! Está tentando sair dos limites do labirinto.\n");
        } else if (proxima->tipo == 'X') {
            printf("\n⚠️  Movimento inválido! Encontrou uma parede ('X').\n");
        } else {
            atual = proxima;
        }
    }
}

// Função para mostrar o caminho encontrado pelo algoritmo.
void mostrarCaminho(){
    celula *atual = labirinto->entrada;

    while (atual != NULL){
        printf("%d,%d\n", atual->i, atual->j);

        if (atual == labirinto->saida)
            break;

        atual = atual->proximo;
    }
    printf("\n");
}

// Função recursiva para buscar a saída do labirinto.
int buscaSaida(celula *atual){
    // caso base: célula inválida, parede (X) ou já visitada
    if (atual == NULL || atual->tipo == 'X' || atual->visitado)
        return 0;

    // marca como visitada — permanente, nunca desfaz.
    atual->visitado = 1;

    // caso base de sucesso: chegou na saída.
    if (atual->tipo == 'S')
        return 1;

    // tenta explorar as células adjacentes (baixo, direita, cima, esquerda) em busca da saída.
    if (buscaSaida(atual->baixo)){
        atual->proximo = atual->baixo;
        if (atual->tipo != 'E') atual->tipo = '*';
        return 1;
    }
    if (buscaSaida(atual->direita)){
        atual->proximo = atual->direita;
        if (atual->tipo != 'E') atual->tipo = '*';
        return 1;
    }
    if (buscaSaida(atual->cima)){
        atual->proximo = atual->cima;
        if (atual->tipo != 'E') atual->tipo = '*';
        return 1;
    }
    if (buscaSaida(atual->esquerda)){
        atual->proximo = atual->esquerda;
        if (atual->tipo != 'E') atual->tipo = '*';
        return 1;
    }

    return 0;
}

// Algoritmo para resolver o labirinto.
void mazeCrawler()
{
    if (labirinto == NULL || labirinto->entrada == NULL){
        printf("\nErro: O labirinto não foi carregado.\n");
        return;
    }

    printf("\nBuscando caminho com o algoritmo:\n");
    if (buscaSaida(labirinto->entrada)){
        printf("\n=== Labirinto resolvido ===\n\n");
        mostrarCaminho();
        imprimeLabirinto();
    }
    else
        printf("\nNenhum caminho válido foi encontrado até a saída ('S').\n");
}

int main() {
    int opcao = 0;
    int escolha = 0;

    do {
        printf("\n--------------------------------------------------------\n");
        printf("\e[1mAlunos:\e[0m Gabriel de Souza Goncalves, Joao Guilherme Couto\n");
        printf("\e[1mProfessor:\e[0m Iago Augusto de Carvalho  \e[1mUNIFAL-MG\e[0m\n");
        printf("--------------------------------------------------------\n");

        printf("\n***********************\e[1mLABIRINTO\e[0m*************************");
        printf("\n*                                                       *");
        printf("\n*             \e[1mSeja bem vindo ao labirinto!\e[0m              *");
        printf("\n*                                                       *");
        printf("\n*\e[1m '1'\e[0m para o tutorial.                                  *");
        printf("\n*\e[1m '2'\e[0m para comecar o labirinto (Modo Jogador).          *");
        printf("\n*\e[1m '3'\e[0m para usar o algoritmo de resolução.               *");
        printf("\n*\e[1m '4'\e[0m para escolher qual labirinto usar.                *");
        printf("\n*\e[1m '5'\e[0m para sair.                                        *");
        printf("\n*                                                       *");
        printf("\n*********************************************************");
        printf("\n\n-> ");

        if (scanf("%d", &opcao) != 1)
            break;

        switch (opcao){
            case 1:
                printf("\n--- TUTORIAL ---\n");
                printf("E = Entrada | S = Saída | X = Parede | 0 = Caminho livre | P = Jogador\n");
                printf("No modo jogo, utilize W/A/S/D para navegar.\n");
                break;

            case 2:
                if(labirinto != NULL)
                jogarLabirinto();

                else
                    printf("\nErro: Nenhum labirinto carregado. Escolha um labirinto primeiro (opção 4).\n");
                
                break;

            case 3:
                if(labirinto != NULL)
                mazeCrawler();

                else
                    printf("\nErro: Nenhum labirinto carregado. Escolha um labirinto primeiro (opção 4).\n");
                    
                break;

            case 4:
                printf("\nOpções: "
                       "\n1. labirinto fácil."
                       "\n2. labirinto sem saída."
                       "\n3. labirinto difícil."
                       "\nEscolha o labirinto (1-3): ");

                scanf("%d", &escolha);

                if(escolha < 1 || escolha > 3){
                    printf("\nOpção inválida! Tente novamente!\n");
                    break;
                }

                if (criaLabirinto(escolha) == 0)
                    printf("\nLabirinto carregado com sucesso!\n");
                else
                    printf("\nErro ao carregar o labirinto.\n");

                break;

            case 5:
                printf("\nEncerrando programa...\n");

                if(labirinto != NULL)
                    liberaMemoria();

                break;

            default:
                printf("\nOpção inválida! Tente novamente!\n");
        }
    } while (opcao != 5);

    return 0;
}