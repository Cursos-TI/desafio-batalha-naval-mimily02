#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs()

#define TAM 10
#define TAM_HABILIDADE 5

// Função para exibir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAM][TAM]) {
    for(int i = 0; i < TAM; i++) {
        for(int j = 0; j < TAM; j++) {
            if(tabuleiro[i][j] == 0) printf("~ ");
            else if(tabuleiro[i][j] == 3) printf("N ");
            else if(tabuleiro[i][j] == 5) printf("* ");
        }
        printf("\n");
    }
    printf("\n");
}

// Função para posicionar navio horizontal
void posiciona_navio_horizontal(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho) {
    if(coluna + tamanho <= TAM) {
        for(int i = 0; i < tamanho; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    }
}

// Função para posicionar navio vertical
void posiciona_navio_vertical(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho) {
    if(linha + tamanho <= TAM) {
        for(int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

// Função para posicionar navio diagonal ↘
void posiciona_navio_diagonal_desc(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho) {
    if(linha + tamanho <= TAM && coluna + tamanho <= TAM) {
        for(int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna + i] = 3;
        }
    }
}

// Função para posicionar navio diagonal ↙
void posiciona_navio_diagonal_asc(int tabuleiro[TAM][TAM], int linha, int coluna, int tamanho) {
    if(linha + tamanho <= TAM && coluna - (tamanho - 1) >= 0) {
        for(int i = 0; i < tamanho; i++) {
            tabuleiro[linha + i][coluna - i] = 3;
        }
    }
}

// Função para sobrepor matriz de habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origem_linha, int origem_coluna) {
    int offset = TAM_HABILIDADE / 2;
    
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            int linha_tab = origem_linha + (i - offset);
            int coluna_tab = origem_coluna + (j - offset);
            if(linha_tab >= 0 && linha_tab < TAM && coluna_tab >= 0 && coluna_tab < TAM) {
                if(habilidade[i][j] == 1 && tabuleiro[linha_tab][coluna_tab] != 3) {
                    tabuleiro[linha_tab][coluna_tab] = 5;
                }
            }
        }
    }
}

// Função para criar matriz de cone
void criar_cone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (j >= TAM_HABILIDADE/2 - i && j <= TAM_HABILIDADE/2 + i) ? 1 : 0;
        }
    }
}

// Função para criar matriz de cruz
void criar_cruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (i == TAM_HABILIDADE/2 || j == TAM_HABILIDADE/2) ? 1 : 0;
        }
    }
}

// Função para criar matriz de octaedro (losango)
void criar_octaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for(int i = 0; i < TAM_HABILIDADE; i++) {
        for(int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;
        }
    }
}

int main(void) {
    int tabuleiro[TAM][TAM] = {0};
    
    // Posicionar quatro navios
    posiciona_navio_horizontal(tabuleiro, 0, 0, 4);
    posiciona_navio_vertical(tabuleiro, 2, 5, 4);
    posiciona_navio_diagonal_desc(tabuleiro, 5, 0, 4);
    posiciona_navio_diagonal_asc(tabuleiro, 5, 9, 4);
    
    printf("Tabuleiro com navios:\n");
    exibir_tabuleiro(tabuleiro);
    
    // Matrizes de habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];
    
    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octaedro);
    
    // Aplicar habilidades
    aplicar_habilidade(tabuleiro, cone, 2, 2);       // Origem do cone
    aplicar_habilidade(tabuleiro, cruz, 7, 7);       // Origem da cruz
    aplicar_habilidade(tabuleiro, octaedro, 5, 5);   // Origem do octaedro
    
    printf("Tabuleiro com habilidades:\n");
    exibir_tabuleiro(tabuleiro);
    
    return 0;
}
