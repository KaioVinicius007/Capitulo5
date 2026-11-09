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
    int inicio = 0, fim = tamanho - 1;
    
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

int soma_iterativa(int *vetor, int tamanho, int *operacoes) {
    *operacoes = 0;
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        (*operacoes)++; 
        soma += vetor[i];
    }
    return soma;
}

int soma_recursiva(int *vetor, int tamanho, int *chamadas) {
    (*chamadas)++;
    
    if (tamanho <= 0) return 0;
    
    return vetor[tamanho - 1] + soma_recursiva(vetor, tamanho - 1, chamadas);
}

int main() {
    int tamanho = 500; 
    srand(time(NULL));

    int *vetor = (int *)malloc(tamanho * sizeof(int));
    if (!vetor) return 1;

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 10; 
    }

    printf("=== ATIVIDADE 30: ITERACAO vs RECURSAO (N = %d) ===\n\n", tamanho);

    int ops_iterativa = 0;
    int resultado_iterativo = soma_iterativa(vetor, tamanho, &ops_iterativa);

    int chamadas_recursivas = 0;
    int resultado_recursivo = soma_recursiva(vetor, tamanho, &chamadas_recursivas);

    printf("--- RESULTADOS ---\n");
    printf("Soma Iterativa: %d\n", resultado_iterativo);
    printf("Soma Recursiva: %d\n\n", resultado_recursivo);
    
    printf("--- CONTADORES DE CUSTO ---\n");
    printf("Custo Iterativo (Iteracoes do Laco): %d\n", ops_iterativa);
    printf("Custo Recursivo (Chamadas na Pilha): %d\n\n", chamadas_recursivas);

    printf("--- CONCLUSOES ---\n");
    printf("1. Ambas as funcoes possuem complexidade O(n).\n");
    printf("2. O caso-base foi atingido apos %d chamadas (tamanho = 0).\n", chamadas_recursivas);
    printf("3. A versao iterativa gasta espaco O(1), enquanto a recursiva gasta O(n) devido a pilha.\n");

    free(vetor);
    return 0;
}