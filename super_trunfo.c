#include <stdio.h>
#include <string.h>

// Estrutura para representar uma carta
struct Carta {
    char estado[30];
    char codigo[5];
    char cidade[30];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_demografica;
    float pib_per_capita;
};

// Função para exibir as regras
void mostrarRegras() {
    printf("\n===== REGRAS DO JOGO SUPER TRUNFO =====\n");
    printf("1. Cada jogador possui uma carta representando uma cidade.\n");
    printf("2. O jogador escolhe DOIS atributos para comparar.\n");
    printf("3. A carta com a maior soma dos atributos vence a rodada.\n");
    printf("4. Exceção: na Densidade Demográfica, vence o menor valor.\n");
    printf("5. Se as somas forem iguais, ocorre um EMPATE!\n");
    printf("========================================\n\n");
}

// Função para exibir os atributos disponíveis
void mostrarAtributosDisponiveis(int escolhido1) {
    printf("\nEscolha o atributo para comparação:\n");
    if (escolhido1 != 1) printf("1 - População\n");
    if (escolhido1 != 2) printf("2 - Área\n");
    if (escolhido1 != 3) printf("3 - PIB\n");
    if (escolhido1 != 4) printf("4 - Pontos Turísticos\n");
    if (escolhido1 != 5) printf("5 - Densidade Demográfica\n");
    if (escolhido1 != 6) printf("6 - PIB per Capita\n");
}

// Função para obter o valor do atributo escolhido
float obterValor(struct Carta c, int atributo) {
    switch (atributo) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.pontos_turisticos;
        case 5: return c.densidade_demografica;
        case 6: return c.pib_per_capita;
        default: return 0;
    }
}

// Função para imprimir o nome do atributo
void nomeAtributo(int atributo) {
    switch (atributo) {
        case 1: printf("População"); break;
        case 2: printf("Área"); break;
        case 3: printf("PIB"); break;
        case 4: printf("Pontos Turísticos"); break;
        case 5: printf("Densidade Demográfica"); break;
        case 6: printf("PIB per Capita"); break;
    }
}

// Função principal do jogo
void jogarPartida() {
    struct Carta carta1 = {"São Paulo", "SP01", "São Paulo", 12300000, 1521.0, 699000000.0, 50, 0, 0};
    struct Carta carta2 = {"Rio de Janeiro", "RJ01", "Rio de Janeiro", 6748000, 1182.3, 420000000.0, 35, 0, 0};

    carta1.densidade_demografica = carta1.populacao / carta1.area;
    carta2.densidade_demografica = carta2.populacao / carta2.area;
    carta1.pib_per_capita = carta1.pib / carta1.populacao;
    carta2.pib_per_capita = carta2.pib / carta2.populacao;

    int escolha1, escolha2;

    printf("\n===== JOGO SUPER TRUNFO =====\n");
    printf("Carta 1: %s (%s)\n", carta1.cidade, carta1.estado);
    printf("Carta 2: %s (%s)\n", carta2.cidade, carta2.estado);

    mostrarAtributosDisponiveis(0);
    printf("\nEscolha o primeiro atributo: ");
    scanf("%d", &escolha1);

    mostrarAtributosDisponiveis(escolha1);
    printf("\nEscolha o segundo atributo: ");
    scanf("%d", &escolha2);

    float valor1_attr1 = obterValor(carta1, escolha1);
    float valor2_attr1 = obterValor(carta2, escolha1);
    float valor1_attr2 = obterValor(carta1, escolha2);
    float valor2_attr2 = obterValor(carta2, escolha2);

    // Lógica de comparação (tratando a densidade demográfica como exceção)
    float pontos1 = 0, pontos2 = 0;

    if (escolha1 == 5) { // Densidade Demográfica
        if (valor1_attr1 < valor2_attr1) pontos1++;
        else if (valor2_attr1 < valor1_attr1) pontos2++;
    } else {
        if (valor1_attr1 > valor2_attr1) pontos1++;
        else if (valor2_attr1 > valor1_attr1) pontos2++;
    }

    if (escolha2 == 5) { // Densidade Demográfica
        if (valor1_attr2 < valor2_attr2) pontos1++;
        else if (valor2_attr2 < valor1_attr2) pontos2++;
    } else {
        if (valor1_attr2 > valor2_attr2) pontos1++;
        else if (valor2_attr2 > valor1_attr2) pontos2++;
    }

    float soma1 = valor1_attr1 + valor1_attr2;
    float soma2 = valor2_attr1 + valor2_attr2;

    printf("\n===== RESULTADO DA RODADA =====\n");
    printf("%s (Carta 1)\n", carta1.cidade);
    printf("%s (Carta 2)\n", carta2.cidade);

    printf("\nAtributo 1: ");
    nomeAtributo(escolha1);
    printf("\n  %s: %.2f\n  %s: %.2f\n", carta1.cidade, valor1_attr1, carta2.cidade, valor2_attr1);

    printf("\nAtributo 2: ");
    nomeAtributo(escolha2);
    printf("\n  %s: %.2f\n  %s: %.2f\n", carta1.cidade, valor1_attr2, carta2.cidade, valor2_attr2);

    printf("\nSoma dos atributos:\n");
    printf("  %s: %.2f\n  %s: %.2f\n", carta1.cidade, soma1, carta2.cidade, soma2);

    if (soma1 > soma2)
        printf("\n🏆 %s venceu a rodada!\n", carta1.cidade);
    else if (soma2 > soma1)
        printf("\n🏆 %s venceu a rodada!\n", carta2.cidade);
    else
        printf("\n🤝 Empate!\n");

    printf("========================================\n\n");
}

// Função principal
int main() {
    int opcao;

    printf("===== MENU SUPER TRUNFO =====\n");
    printf("1 - Jogar Partida\n");
    printf("2 - Regras do Jogo\n");
    printf("3 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            jogarPartida();
            break;
        case 2:
            mostrarRegras();
            break;
        case 3:
            printf("\nSaindo do jogo... Até a próxima!\n");
            break;
        default:
            printf("\nOpção inválida.\n");
            break;
    }

    return 0;
}
