#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int acesso_direto(int *vetor, int tamanho, int indice, int *operacoes) {
    *operacoes = 0;
    if (indice < 0 || indice >= tamanho) return -1; 
    (*operacoes)++; 
    return vetor[indice];
}

int busca_maior(int *vetor, int tamanho, int *operacoes) {
    *operacoes = 0;
    if (tamanho <= 0) return -1;
    int maior = vetor[0];
    (*operacoes)++; 
    for (int i = 1; i < tamanho; i++) {
        (*operacoes)++; 
        if (vetor[i] > maior) maior = vetor[i];
    }
    return maior;
}

int busca_pares_soma(int *vetor, int tamanho, int alvo, int *operacoes) {
    *operacoes = 0;
    int pares = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            (*operacoes)++; 
            if (vetor[i] + vetor[j] == alvo) pares++;
        }
    }
    return pares;
}

int verifica_ordenacao(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (vetor[i] > vetor[i + 1]) return 0;
    }
    return 1;
}

int busca_binaria(int *vetor, int tamanho, int alvo, int *operacoes) {
    *operacoes = 0;
    int inicio = 0;
    int fim = tamanho - 1;
    
    while (inicio <= fim) {
        (*operacoes)++;
        int meio = inicio + (fim - inicio) / 2; 
        
        if (vetor[meio] == alvo) return meio;
        else if (vetor[meio] < alvo) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int busca_linear(int *vetor, int tamanho, int alvo, int *operacoes) {
    *operacoes = 0;
    for (int i = 0; i < tamanho; i++) {
        (*operacoes)++; 
        if (vetor[i] == alvo) return i;
    }
    return -1;
}

int main() {
    int tamanho = 1000; 
    srand(time(NULL));

    int *vetor_aleatorio = (int *)malloc(tamanho * sizeof(int));
    int *vetor_ordenado = (int *)malloc(tamanho * sizeof(int));
    
    if (!vetor_aleatorio || !vetor_ordenado) return 1;

    for (int i = 0; i < tamanho; i++) {
        vetor_aleatorio[i] = rand() % 5000;
        vetor_ordenado[i] = i * 2; 
    }

    printf("=== ATIVIDADE 29: BUSCA LINEAR vs BUSCA BINARIA (N = %d) ===\n\n", tamanho);

    if (verifica_ordenacao(vetor_ordenado, tamanho)) {
        printf("--- TESTES NO VETOR ORDENADO ---\n");
        
        int alvos[] = {vetor_ordenado[0], vetor_ordenado[tamanho / 2], vetor_ordenado[tamanho - 1], -1};
        char *descricoes[] = {"INICIO", "MEIO", "FIM", "AUSENTE"};
        
        printf("%-10s | %-10s | %-15s | %-15s\n", "POSICAO", "ALVO", "OPS. LINEAR", "OPS. BINARIA");
        printf("-----------------------------------------------------------------\n");
        
        for (int i = 0; i < 4; i++) {
            int ops_linear = 0, ops_binaria = 0;
            
            busca_linear(vetor_ordenado, tamanho, alvos[i], &ops_linear);
            busca_binaria(vetor_ordenado, tamanho, alvos[i], &ops_binaria);
            
            printf("%-10s | %-10d | %-15d | %-15d\n", descricoes[i], alvos[i], ops_linear, ops_binaria);
        }
    }

    printf("\n--- TESTE NO VETOR DESORDENADO (ALEATORIO) ---\n");
    int alvo_aleatorio = vetor_aleatorio[tamanho - 1]; 
    int ops_linear_desordenado = 0;
    
    int pos_encontrada = busca_linear(vetor_aleatorio, tamanho, alvo_aleatorio, &ops_linear_desordenado);
    
    printf("Alvo buscado: %d\n", alvo_aleatorio);
    printf("Posicao encontrada via Busca Linear: %d\n", pos_encontrada);
    printf("Operacoes realizadas (Busca Linear): %d\n", ops_linear_desordenado);
    printf("Operacoes realizadas (Busca Binaria): [NAO EXECUTADA]\n");
    printf(" -> Motivo: O vetor nao esta ordenado.\n\n");

    free(vetor_aleatorio);
    free(vetor_ordenado);

    return 0;
}