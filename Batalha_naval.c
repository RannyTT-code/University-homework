#include <stdio.h>

#define TAMANHO 10    // Tamanho fixo do tabuleiro
#define NAVIO 3       // Valor para partes de navios
#define AGUA 0        // Valor para água
#define HABILIDADE 5  // Valor para área afetada pela habilidade
#define TAM_HAB 5     // Tamanho fixo das matrizes de habilidade (5x5)
#define TAM_NAVIO 3   // Tamanho dos navios

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para imprimir o tabuleiro com símbolos
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL (NÍVEL AVANÇADO) ===\n\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf("~ ");   // Água
            else if (tabuleiro[i][j] == NAVIO)
                printf("# ");   // Navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");   // Área de efeito
        }
        printf("\n");
    }
}

// Função para posicionar um navio horizontal
void posicionarNavioHorizontal(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (coluna + i < TAMANHO)
            tabuleiro[linha][coluna + i] = NAVIO;
    }
}

// Função para posicionar um navio vertical
void posicionarNavioVertical(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha + i < TAMANHO)
            tabuleiro[linha + i][coluna] = NAVIO;
    }
}

// Função para posicionar um navio diagonal ↘
void posicionarNavioDiagonalDireita(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha + i < TAMANHO && coluna + i < TAMANHO)
            tabuleiro[linha + i][coluna + i] = NAVIO;
    }
}

// Função para posicionar um navio diagonal ↙
void posicionarNavioDiagonalEsquerda(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (linha + i < TAMANHO && coluna - i >= 0)
            tabuleiro[linha + i][coluna - i] = NAVIO;
    }
}

// Cria uma matriz de habilidade em forma de CONE
void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Cria uma matriz de habilidade em forma de CRUZ
void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Cria uma matriz de habilidade em forma de OCTAEDRO (losango)
void criarOctaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }
}

// Aplica uma habilidade ao tabuleiro com base na sua matriz e origem
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int habilidade[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origemLinha - centro + i;
                int coluna = origemColuna - centro + j;
                if (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO) {
                    if (tabuleiro[linha][coluna] == AGUA)  // não sobrescreve navios
                        tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    // 1️⃣ Inicializa tabuleiro e posiciona navios
    inicializarTabuleiro(tabuleiro);
    posicionarNavioHorizontal(tabuleiro, 1, 2);
    posicionarNavioVertical(tabuleiro, 5, 7);
    posicionarNavioDiagonalDireita(tabuleiro, 3, 3);
    posicionarNavioDiagonalEsquerda(tabuleiro, 6, 4);

    // 2️⃣ Cria as habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // 3️⃣ Define as origens das habilidades (centros)
    int origemConeLinha = 2, origemConeColuna = 5;
    int origemCruzLinha = 6, origemCruzColuna = 2;
    int origemOctaedroLinha = 7, origemOctaedroColuna = 7;

    // 4️⃣ Aplica as habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // 5️⃣ Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
