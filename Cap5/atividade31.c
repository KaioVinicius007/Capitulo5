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

int busca_linear(int *vetor, int tamanho, int alvo, int *operacoes) {
    *operacoes = 0;
    for (int i = 0; i < tamanho; i++) {
        (*operacoes)++; 
        if (vetor[i] == alvo) return i;
    }
    return -1;
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

int fibonacci_recursivo(int n, int *chamadas) {
    (*chamadas)++;
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci_recursivo(n - 1, chamadas) + fibonacci_recursivo(n - 2, chamadas);
}

int busca_binaria_recursiva(int *vetor, int inicio, int fim, int alvo, int *chamadas) {
    (*chamadas)++;
    if (inicio > fim) return -1;
    
    int meio = inicio + (fim - inicio) / 2;
    if (vetor[meio] == alvo) return meio;
    
    if (vetor[meio] < alvo) {
        return busca_binaria_recursiva(vetor, meio + 1, fim, alvo, chamadas);
    } else {
        return busca_binaria_recursiva(vetor, inicio, meio - 1, alvo, chamadas);
    }
}

void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int opcao = -1;
    srand(time(NULL));

    while (opcao != 0) {
        printf("\n=======================================================\n");
        printf("    LABORATORIO DE ESTRUTURAS DE DADOS 1 - MENU\n");
        printf("=======================================================\n");
        printf("1. [Atv 26] Acesso Direto O(1) vs Busca Maior O(n)\n");
        printf("2. [Atv 27] Busca de Pares O(n^2)\n");
        printf("3. [Atv 29] Busca Linear O(n) vs Busca Binaria O(log n)\n");
        printf("4. [Atv 30] Soma: Iteracao vs Recursao Linear O(n)\n");
        printf("5. [Atv 31] Recursao: Ramificada O(2^n) vs Divisao O(log n)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            limpa_buffer();
            continue;
        }
        printf("\n");

        switch(opcao) {
            case 1: {
                int n = 5000, ops_acesso, ops_maior;
                int *vet = malloc(n * sizeof(int));
                for(int i=0; i<n; i++) vet[i] = rand() % 1000;
                
                acesso_direto(vet, n, n/2, &ops_acesso);
                busca_maior(vet, n, &ops_maior);
                
                printf("Tamanho (N): %d\n", n);
                printf("Ops Acesso Direto O(1): %d\n", ops_acesso);
                printf("Ops Busca Maior O(n): %d\n", ops_maior);
                free(vet);
                break;
            }
            case 2: {
                int n = 2000, ops_pares;
                int *vet = malloc(n * sizeof(int));
                for(int i=0; i<n; i++) vet[i] = rand() % 500;
                
                busca_pares_soma(vet, n, 400, &ops_pares);
                
                printf("Tamanho (N): %d\n", n);
                printf("Ops Busca Pares O(n^2): %d\n", ops_pares);
                free(vet);
                break;
            }
            case 3: {
                int n = 1000, ops_lin, ops_bin;
                int *vet_ord = malloc(n * sizeof(int));
                for(int i=0; i<n; i++) vet_ord[i] = i * 2;
                
                int alvo = -1; 
                busca_linear(vet_ord, n, alvo, &ops_lin);
                busca_binaria(vet_ord, n, alvo, &ops_bin);
                
                printf("Tamanho (N): %d | Alvo: %d (Ausente)\n", n, alvo);
                printf("Ops Busca Linear O(n): %d\n", ops_lin);
                printf("Ops Busca Binaria O(log n): %d\n", ops_bin);
                free(vet_ord);
                break;
            }
            case 4: {
                int n = 500, ops_iter, ops_rec = 0;
                int *vet = malloc(n * sizeof(int));
                for(int i=0; i<n; i++) vet[i] = rand() % 10;
                
                soma_iterativa(vet, n, &ops_iter);
                soma_recursiva(vet, n, &ops_rec);
                
                printf("Tamanho (N): %d\n", n);
                printf("Custo Iterativo (Laco): %d iteracoes\n", ops_iter);
                printf("Custo Recursivo (Pilha): %d chamadas\n", ops_rec);
                free(vet);
                break;
            }
            case 5: {
                int num_fib = 25, chamadas_fib = 0;
                printf("Calculando Fibonacci de %d...\n", num_fib);
                int result_fib = fibonacci_recursivo(num_fib, &chamadas_fib);
                printf("Resultado: %d | Chamadas na Pilha: %d\n\n", result_fib, chamadas_fib);
                
                int n_vet = 10000, chamadas_bin = 0, alvo = -1;
                int *vet_ord = malloc(n_vet * sizeof(int));
                for(int i = 0; i < n_vet; i++) vet_ord[i] = i * 2;
                
                printf("Buscando alvo %d em vetor de %d elementos...\n", alvo, n_vet);
                busca_binaria_recursiva(vet_ord, 0, n_vet - 1, alvo, &chamadas_bin);
                printf("Chamadas na Pilha: %d\n", chamadas_bin);
                
                free(vet_ord);
                break;
            }
            case 0:
                printf("Saindo do laboratorio...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }
    return 0;
}