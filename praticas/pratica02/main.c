#include <stdio.h>
#include <stdlib.h>

#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

static void imprimir_vetor(const char *rotulo, const int *v, int n) {
    printf("%s:", rotulo);
    for (int i = 0; i < n; i++) {
        printf(" %d", v[i]);
    }
    printf("\n");
}

int main(void) {
    /*
     * Grafo de exemplo com 8 vertices e duas componentes conexas:
     *   Componente A (0-4): ciclo impar 0-1-2-3-4-0 -> tem ciclo, nao bipartido.
     *   Componente B (5-7): caminho 5-6-7            -> sem ciclo, bipartido.
     */
    int numVertices = 8;
    GrafoLista *g = grafo_criar(numVertices);

    grafo_add_aresta(g, 0, 1);
    grafo_add_aresta(g, 1, 2);
    grafo_add_aresta(g, 2, 3);
    grafo_add_aresta(g, 3, 4);
    grafo_add_aresta(g, 4, 0);

    grafo_add_aresta(g, 5, 6);
    grafo_add_aresta(g, 6, 7);

    printf("=== Lista de adjacencia ===\n");
    grafo_imprimir(g);
    printf("\n");

    printf("=== Busca em largura (BFS) a partir do vertice 0 ===\n");
    int *dist = malloc((size_t)numVertices * sizeof(int));
    int *predBfs = malloc((size_t)numVertices * sizeof(int));
    bfs(g, 0, dist, predBfs);
    imprimir_vetor("dist", dist, numVertices);
    imprimir_vetor("pred", predBfs, numVertices);
    printf("\n");
    free(dist);
    free(predBfs);

    printf("=== Busca em profundidade (DFS) recursiva ===\n");
    int *visitado = malloc((size_t)numVertices * sizeof(int));
    int *predDfs = malloc((size_t)numVertices * sizeof(int));
    int *ordem = malloc((size_t)numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        visitado[i] = 0;
        predDfs[i] = -1;
        ordem[i] = -1;
    }
    int contador = 0;
    for (int i = 0; i < numVertices; i++) {
        if (!visitado[i]) {
            dfs_recursiva(g, i, visitado, predDfs, ordem, &contador);
        }
    }
    imprimir_vetor("ordem", ordem, numVertices);
    imprimir_vetor("pred ", predDfs, numVertices);
    printf("\n");
    free(visitado);
    free(predDfs);
    free(ordem);

    printf("=== Propriedades do grafo ===\n");
    printf("E bipartido? %s\n", eh_bipartido(g) ? "sim" : "nao");
    printf("Numero de componentes conexas: %d\n", contar_componentes(g));
    printf("Possui ciclo? %s\n", tem_ciclo(g) ? "sim" : "nao");

    grafo_destruir(g);

    return 0;
}
