#include <stdio.h>
#include <stdlib.h>

#include "dag.h"

static void imprimir_ordem(const char *rotulo, const int *ordem, int tamanho) {
    if (ordem == NULL) {
        printf("%s: NULL (grafo possui ciclo, ordenacao topologica impossivel)\n", rotulo);
        return;
    }

    printf("%s:", rotulo);
    for (int i = 0; i < tamanho; i++) {
        printf(" %d", ordem[i]);
    }
    printf("\n");
}

int main(void) {
    printf("=== DAG valido ===\n");
    /*
     * Vertices 0..5.
     *   5 -> 2, 5 -> 0
     *   4 -> 0, 4 -> 1
     *   2 -> 3
     *   3 -> 1
     * Grafo aciclico com multiplas ordenacoes topologicas validas.
     */
    GrafoLista *dag = criar_grafo_lista(6);
    inserir_arco(dag, 5, 2);
    inserir_arco(dag, 5, 0);
    inserir_arco(dag, 4, 0);
    inserir_arco(dag, 4, 1);
    inserir_arco(dag, 2, 3);
    inserir_arco(dag, 3, 1);

    printf("E DAG (aciclico)? %s\n", eh_dag(dag) ? "sim" : "nao");

    int tamanhoKahn = 0;
    int *ordemKahn = ordenacao_topologica_kahn(dag, &tamanhoKahn);
    imprimir_ordem("Kahn", ordemKahn, tamanhoKahn);
    free(ordemKahn);

    int tamanhoDfs = 0;
    int *ordemDfs = ordenacao_topologica_dfs(dag, &tamanhoDfs);
    imprimir_ordem("DFS ", ordemDfs, tamanhoDfs);
    free(ordemDfs);

    liberar_grafo_lista(dag);

    printf("\n=== Grafo com ciclo ===\n");
    /*
     * Vertices 0..3 formando um ciclo: 0 -> 1 -> 2 -> 3 -> 0.
     */
    GrafoLista *ciclico = criar_grafo_lista(4);
    inserir_arco(ciclico, 0, 1);
    inserir_arco(ciclico, 1, 2);
    inserir_arco(ciclico, 2, 3);
    inserir_arco(ciclico, 3, 0);

    printf("E DAG (aciclico)? %s\n", eh_dag(ciclico) ? "sim" : "nao");

    int tamanhoKahnCiclo = 0;
    int *ordemKahnCiclo = ordenacao_topologica_kahn(ciclico, &tamanhoKahnCiclo);
    imprimir_ordem("Kahn", ordemKahnCiclo, tamanhoKahnCiclo);
    free(ordemKahnCiclo);

    int tamanhoDfsCiclo = 0;
    int *ordemDfsCiclo = ordenacao_topologica_dfs(ciclico, &tamanhoDfsCiclo);
    imprimir_ordem("DFS ", ordemDfsCiclo, tamanhoDfsCiclo);
    free(ordemDfsCiclo);

    liberar_grafo_lista(ciclico);

    return 0;
}
