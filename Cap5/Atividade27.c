#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 
 * Função 1: Acesso direto a uma posição válida do vetor.
 * Complexidade: O(1) (Constante).
 */
int acesso_direto(int *vetor, int tamanho, int indice, int *operacoes) {
    *operacoes = 0;
    if (indice < 0 || indice >= tamanho) {
        return -1; 
    }
    (*operacoes)++; 
    return vetor[indice];
}

/* 
 * Função 2: Busca o maior valor percorrendo todo o vetor.
 * Complexidade: O(n) (Linear).
 */
int busca_maior(int *vetor, int tamanho, int *operacoes) {
    *operacoes = 0;
    if (tamanho <= 0) return -1;

    int maior = vetor[0];
    (*operacoes)++; 

    for (int i = 1; i < tamanho; i++) {
        (*operacoes)++; 
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }
    return maior;
}

/* 
 * Função 3 (NOVA): Busca pares que somam um valor alvo.
 * Complexidade: O(n²) (Quadrática).
 */
int busca_pares_soma(int *vetor, int tamanho, int alvo, int *operacoes) {
    *operacoes = 0;
    int pares_encontrados = 0;

    // O primeiro laço vai até o penúltimo elemento
    for (int i = 0; i < tamanho - 1; i++) {
        // O segundo laço começa SEMPRE um passo à frente de 'i'
        // Isso impede pares duplicados (i,j e j,i) e impede i == j
        for (int j = i + 1; j < tamanho; j++) {
            (*operacoes)++; // Contabiliza cada vez que o núcleo (a comparação) é executado
            
            if (vetor[i] + vetor[j] == alvo) {
                pares_encontrados++;
            }
        }
    }
    
    return pares_encontrados;
}

int main() {
    // Reduzi levemente o último tamanho para a execução O(n²) não demorar muito em máquinas antigas, 
    // mas a proporção continua clara.
    int tamanhos[] = {1000, 2000, 4000};
    int qtd_testes = 3;
    
    srand(time(NULL));

    printf("=== ANALISE DE COMPLEXIDADE: O(1) vs O(n) vs O(n^2) ===\n\n");

    for (int i = 0; i < qtd_testes; i++) {
        int tamanho_atual = tamanhos[i];
        
        int *vetor = (int *)malloc(tamanho_atual * sizeof(int));
        if (vetor == NULL) {
            printf("Erro de alocacao de memoria.\n");
            return 1;
        }

        // Preenche o vetor com valores aleatórios entre 0 e 500
        for (int j = 0; j < tamanho_atual; j++) {
            vetor[j] = rand() % 500;
        }

        int ops_acesso = 0;
        int ops_busca = 0;
        int ops_pares = 0;

        int indice_teste = tamanho_atual / 2;
        int alvo_teste = 450; // Valor arbitrário para buscar soma

        // Executa as funções instrumentadas
        acesso_direto(vetor, tamanho_atual, indice_teste, &ops_acesso);
        busca_maior(vetor, tamanho_atual, &ops_busca);
        busca_pares_soma(vetor, tamanho_atual, alvo_teste, &ops_pares);

        // Exibe os resultados
        printf("Tamanho do vetor (N): %d\n", tamanho_atual);
        printf(" -> Operacoes O(1)   [Acesso Direto]: %d\n", ops_acesso);
        printf(" -> Operacoes O(n)   [Busca do Maior]: %d\n", ops_busca);
        printf(" -> Operacoes O(n^2) [Busca de Pares]: %d\n\n", ops_pares);

        free(vetor);
    }

    printf("=== CONCLUSAO O(n^2) ===\n");
    printf("- Enquanto O(n) dobra quando N dobra (ex: de 2000 para 4000),\n");
    printf("  O(n^2) quadruplica (aumenta exponencialmente ao quadrado).\n");
    printf("- A formula exata de operacoes O(n^2) neste algoritmo e (N * (N - 1)) / 2.\n");

    return 0;
}