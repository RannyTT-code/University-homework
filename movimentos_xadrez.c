#include <stdio.h>

// ==========================
// Funções recursivas
// ==========================

// --- Torre ---
void moverTorre(int casas) {
    if (casas == 0) return; // condição de parada
    printf("Direita\n");
    moverTorre(casas - 1); // chamada recursiva
}

// --- Bispo ---
void moverBispoRecursivo(int verticais, int horizontais) {
    if (verticais == 0 || horizontais == 0) return; // condição de parada

    // Loop externo = vertical | Loop interno = horizontal
    for (int v = 1; v <= 1; v++) { // move uma casa vertical
        for (int h = 1; h <= 1; h++) { // move uma casa horizontal
            printf("Cima Direita\n");
        }
    }

    // chamada recursiva (reduz uma casa diagonal)
    moverBispoRecursivo(verticais - 1, horizontais - 1);
}

// --- Rainha ---
void moverRainha(int casas) {
    if (casas == 0) return;
    printf("Esquerda\n");
    moverRainha(casas - 1);
}

// ==========================
// Cavalo (loops complexos)
// ==========================
void moverCavalo() {
    int movVertical = 2; // duas casas para cima
    int movHorizontal = 1; // uma casa para direita

    printf("Movimento do CAVALO:\n");

    for (int i = 1, j = movVertical; i <= movVertical && j > 0; i++, j--) {
        if (i == 2) {
            // movimento final do L
            for (int k = 1; k <= movHorizontal; k++) {
                if (k == 0) continue; // (não será usado aqui, mas exemplo de controle)
                printf("Direita\n");
                break; // finaliza após completar o L
            }
        }
        printf("Cima\n");
    }
}

// ==========================
// Função principal
// ==========================
int main() {
    // Quantidade de casas para cada peça
    int casasTorre = 5;
    int casasBispo = 5;
    int casasRainha = 8;

    printf("Movimento da TORRE:\n");
    moverTorre(casasTorre);

    printf("\nMovimento do BISPO:\n");
    moverBispoRecursivo(casasBispo, casasBispo);

    printf("\nMovimento da RAINHA:\n");
    moverRainha(casasRainha);

    printf("\n");
    moverCavalo();

    return 0;
}
