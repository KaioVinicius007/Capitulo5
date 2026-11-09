#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* --- Funções Anteriores --- */

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
    int pares_encontrados = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            (*operacoes)++; 
            if (vetor[i] + vetor[j] == alvo) pares_encontrados++;
        }
    }
    return pares_encontrados;
}

/* --- Novas Funções --- */

/* Verifica se o vetor está ordenado crescentemente */
int verifica_ordenacao(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        if (vetor[i] > vetor[i + 1]) {
            return 0; // Falso (não está ordenado)
        }
    }
    return 1; // Verdadeiro (está ordenado)
}

/* 
 * Função 4: Busca Binária Iterativa.
 * Complexidade: O(log n) (Logarítmica).
 */
int busca_binaria(int *vetor, int tamanho, int alvo, int *operacoes, int mostrar_passos) {
    *operacoes = 0;
    int inicio = 0;
    int fim = tamanho - 1;
    
    // Termina quando o intervalo fica vazio
    while (inicio <= fim) {
        (*operacoes)++;
        
        // Cálculo do meio evitando overflow: inicio + (fim - inicio) / 2
        int meio = inicio + (fim - inicio) / 2; 
        
        if (mostrar_passos) {
            printf("    [Passo %2d] Inicio: %-4d | Meio: %-4d | Fim: %-4d (Valores: %d a %d)\n", 
                   *operacoes, inicio, meio, fim, vetor[inicio], vetor[fim]);
        }
        
        if (vetor[meio] == alvo) {
            return meio; // Encontrou
        } else if (vetor[meio] < alvo) {
            inicio = meio + 1; // Descarta a metade inferior
        } else {
            fim = meio - 1; // Descarta a metade superior
        }
    }
    
    return -1; // Não encontrou
}

int main() {
    int tamanhos[] = {1000, 2000, 4000};
    int qtd_testes = 3;
    
    srand(time(NULL));

    printf("=== ANALISE DE COMPLEXIDADE: O(1), O(log n), O(n), O(n^2) ===\n\n");

    for (int i = 0; i < qtd_testes; i++) {
        int tamanho_atual = tamanhos[i];
        
        int *vetor_aleatorio = (int *)malloc(tamanho_atual * sizeof(int));
        int *vetor_ordenado = (int *)malloc(tamanho_atual * sizeof(int));
        
        if (!vetor_aleatorio || !vetor_ordenado) {
            printf("Erro de alocacao de memoria.\n");
            return 1;
        }

        // Preenche o vetor aleatório e o vetor ordenado (pares sequenciais)
        for (int j = 0; j < tamanho_atual; j++) {
            vetor_aleatorio[j] = rand() % 500;
            vetor_ordenado[j] = j * 2; 
        }

        int ops_acesso = 0, ops_busca_maior = 0, ops_pares = 0;
        int ops_bin_presente = 0, ops_bin_ausente = 0;

        acesso_direto(vetor_aleatorio, tamanho_atual, tamanho_atual / 2, &ops_acesso);
        busca_maior(vetor_aleatorio, tamanho_atual, &ops_busca_maior);
        busca_pares_soma(vetor_aleatorio, tamanho_atual, 450, &ops_pares);

        printf("Tamanho do vetor (N): %d\n", tamanho_atual);
        printf(" -> O(1)   [Acesso Direto] : %d\n", ops_acesso);
        
        // Verifica ordenação antes de rodar a busca binária
        if (verifica_ordenacao(vetor_ordenado, tamanho_atual)) {
            
            // Valor presente (ex: penúltimo elemento)
            int alvo_presente = (tamanho_atual - 2) * 2;
            // Valor ausente (ímpar, já que o vetor só tem pares)
            int alvo_ausente = -1; 
            
            // Mostra o passo a passo apenas no primeiro teste para o valor ausente
            int mostrar = (i == 0); 
            
            if (mostrar) printf(" -> O(log n) [Busca Binaria - Rastreio do Alvo %d]:\n", alvo_ausente);
            
            busca_binaria(vetor_ordenado, tamanho_atual, alvo_ausente, &ops_bin_ausente, mostrar);
            busca_binaria(vetor_ordenado, tamanho_atual, alvo_presente, &ops_bin_presente, 0);

            printf(" -> O(log n) [Busca Bin. Presente] : %d comparacoes\n", ops_bin_presente);
            printf(" -> O(log n) [Busca Bin. Ausente]  : %d comparacoes\n", ops_bin_ausente);
        }

        printf(" -> O(n)   [Busca do Maior]: %d\n", ops_busca_maior);
        printf(" -> O(n^2) [Busca de Pares]: %d\n", ops_pares);
        printf("---------------------------------------------------\n");

        free(vetor_aleatorio);
        free(vetor_ordenado);
    }

    printf("=== CONCLUSAO O(log n) ===\n");
    printf("- O(log n) cresce de forma extremamente lenta.\n");
    printf("- Note o rastreio (passo a passo): a cada iteracao, o espaco de busca\n");
    printf("  cai pela metade (de 1000 para 500, depois 250, 125, etc).\n");
    printf("- Para N = 4000, o pior caso exige apenas cerca de 12 comparacoes\n");
    printf("  (pois 2^12 = 4096). O O(n) precisou de 4000 e O(n^2) de quase 8 milhoes.\n");

    return 0;
}