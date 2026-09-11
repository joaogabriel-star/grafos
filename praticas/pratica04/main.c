#include <stdio.h>
#include <stdlib.h>

#include "conectividade.h"
#include "planaridade.h"

static void imprimir_articulacoes(const int *artic, int n) {
    printf("Vertices de articulacao:");
    for (int i = 0; i < n; i++) {
        if (artic[i]) {
            printf(" %d", i);
        }
    }
    printf("\n");
}

static void imprimir_pontes(const int *pontesU, const int *pontesV, int numPontes) {
    printf("Pontes:");
    for (int i = 0; i < numPontes; i++) {
        printf(" (%d-%d)", pontesU[i], pontesV[i]);
    }
    printf("\n");
}

int main(void) {
    printf("=== Grafo 1: triangulo (0,1,2) + ponte 2-3 + ponte 3-4 ===\n");
    /*
     * Triangulo 0-1-2 (ciclo, sem pontes/articulacoes internas) ligado por uma
     * ponte ao vertice 3, que por sua vez tem uma ponte para o vertice 4 (folha).
     * Articulacoes esperadas: {2, 3}. Pontes esperadas: {(2,3), (3,4)}.
     */
    GrafoLista *g1 = criar_grafo_lista(5);
    inserir_aresta_lista(g1, 0, 1);
    inserir_aresta_lista(g1, 1, 2);
    inserir_aresta_lista(g1, 2, 0);
    inserir_aresta_lista(g1, 2, 3);
    inserir_aresta_lista(g1, 3, 4);

    int artic1[5];
    int numArtic1 = dfs_articulacoes(g1, artic1);
    printf("Total de articulacoes: %d\n", numArtic1);
    imprimir_articulacoes(artic1, g1->n);

    int pontesU1[5], pontesV1[5];
    int numPontes1 = detectar_pontes(g1, pontesU1, pontesV1);
    printf("Total de pontes: %d\n", numPontes1);
    imprimir_pontes(pontesU1, pontesV1, numPontes1);

    printf("Satisfaz Euler (m <= 3n-6)? %s\n", eh_planar_euler(g1) ? "sim" : "nao");
    printf("Contem K5/K3,3 (forca bruta)? %s\n", contem_k5_ou_k33_forca_bruta(g1) ? "sim" : "nao");

    liberar_grafo_lista(g1);

    printf("\n=== Grafo 2: K5 (5 vertices, todos ligados dois a dois) ===\n");
    GrafoLista *g2 = criar_grafo_lista(5);
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            inserir_aresta_lista(g2, i, j);
        }
    }

    printf("Satisfaz Euler (m <= 3n-6)? %s (esperado: nao)\n", eh_planar_euler(g2) ? "sim" : "nao");
    printf("Contem K5/K3,3 (forca bruta)? %s (esperado: sim)\n",
           contem_k5_ou_k33_forca_bruta(g2) ? "sim" : "nao");

    liberar_grafo_lista(g2);

    printf("\n=== Grafo 3: K3,3 (bipartido completo, 6 vertices) ===\n");
    /* Lado A = {0,1,2}, lado B = {3,4,5}, todas as 9 arestas cruzadas presentes. */
    GrafoLista *g3 = criar_grafo_lista(6);
    for (int a = 0; a < 3; a++) {
        for (int b = 3; b < 6; b++) {
            inserir_aresta_lista(g3, a, b);
        }
    }

    printf("Satisfaz Euler (m <= 3n-6)? %s (esperado: sim, mas grafo NAO e planar)\n",
           eh_planar_euler(g3) ? "sim" : "nao");
    printf("Contem K5/K3,3 (forca bruta)? %s (esperado: sim - deteta o que Euler nao detetou)\n",
           contem_k5_ou_k33_forca_bruta(g3) ? "sim" : "nao");

    liberar_grafo_lista(g3);

    return 0;
}
