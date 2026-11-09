#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int acesso_direto(int *vetor, int tamanho, int indice, int *operacoes) {
    *operacoes = 0; // Inicializa o contador independente
    
    // Validação do índice solicitada nos requisitos
    if (indice < 0 || indice >= tamanho) {
        printf("Indice %d invalido!\n", indice);
        return -1; 
    }
    
    // Contabiliza o acesso direto
    (*operacoes)++; 
    
    return vetor[indice];
}


int busca_maior(int *vetor, int tamanho, int *operacoes) {
    *operacoes = 0; // Inicializa o contador independente
    
    if (tamanho <= 0) return -1;

    int maior = vetor[0];
    (*operacoes)++; // Contabiliza o acesso ao primeiro elemento

    // Percorre todos os elementos restantes
    for (int i = 1; i < tamanho; i++) {
        (*operacoes)++; // Contabiliza cada comparação feita no loop
        if (vetor[i] > maior) {
            maior = vetor[i];
        }
    }
    
    return maior;
}

int main() {
    // Requisito: testar ao menos três tamanhos de entrada
    int tamanhos[] = {1000, 5000, 10000};
    int qtd_testes = 3;
    
    // Semente para geração de números aleatórios
    srand(time(NULL));

    printf("=== ANALISE DE COMPLEXIDADE: O(1) vs O(n) ===\n\n");

    for (int i = 0; i < qtd_testes; i++) {
        int tamanho_atual = tamanhos[i];
        
        // Aloca o vetor dinamicamente de acordo com o tamanho atual
        int *vetor = (int *)malloc(tamanho_atual * sizeof(int));
        if (vetor == NULL) {
            printf("Erro de alocacao de memoria.\n");
            return 1;
        }

        // Preenche o vetor com valores aleatórios
        for (int j = 0; j < tamanho_atual; j++) {
            vetor[j] = rand() % 10000;
        }

        int ops_acesso = 0;
        int ops_busca = 0;

        // Posição válida arbitrária para testar o acesso direto (ex: o elemento no meio do vetor)
        int indice_teste = tamanho_atual / 2;

        // Executa as funções instrumentadas
        acesso_direto(vetor, tamanho_atual, indice_teste, &ops_acesso);
        busca_maior(vetor, tamanho_atual, &ops_busca);

        // Exibe os resultados do tamanho atual
        printf("Tamanho do vetor (N): %d\n", tamanho_atual);
        printf(" -> Operacoes no acesso direto (O(1)): %d\n", ops_acesso);
        printf(" -> Operacoes na busca do maior (O(n)): %d\n\n", ops_busca);

        // Libera a memória antes da próxima iteração
        free(vetor);
    }

    printf("=== CONCLUSAO ===\n");
    printf("- O(1) (Acesso Direto): O numero de operacoes (%d) permanece constante,\n", 1);
    printf("  independentemente de N crescer para 1000, 5000 ou 10000.\n");
    printf("- O(n) (Busca do Maior): O numero de operacoes cresce proporcionalmente ao\n");
    printf("  tamanho de N, pois todos os N elementos precisam ser visitados e comparados.\n");

    return 0;
}