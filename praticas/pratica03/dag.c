#include <stdio.h>
#include <stdlib.h>

#include "dag.h"

GrafoLista *criar_grafo_lista(int n) {
    GrafoLista *grafo = malloc(sizeof(GrafoLista));
    if (grafo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar grafo.\n");
        exit(EXIT_FAILURE);
    }

    grafo->n = n;
    grafo->adj = calloc((size_t)n, sizeof(No *));
    if (grafo->adj == NULL) {
        fprintf(stderr, "Erro: falha ao alocar lista de adjacencia.\n");
        free(grafo);
        exit(EXIT_FAILURE);
    }

    return grafo;
}

void liberar_grafo_lista(GrafoLista *grafo) {
    if (grafo == NULL) {
        return;
    }

    for (int i = 0; i < grafo->n; i++) {
        No *atual = grafo->adj[i];
        while (atual != NULL) {
            No *proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }

    free(grafo->adj);
    free(grafo);
}

void inserir_arco(GrafoLista *grafo, int u, int v) {
    No *no = malloc(sizeof(No));
    if (no == NULL) {
        fprintf(stderr, "Erro: falha ao alocar no de adjacencia.\n");
        exit(EXIT_FAILURE);
    }

    no->destino = v;
    no->prox = grafo->adj[u];
    grafo->adj[u] = no;
}

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int n = g->n;

    int *grauEntrada = calloc((size_t)n, sizeof(int));
    int *fila = malloc((size_t)n * sizeof(int));
    int *ordem = malloc((size_t)n * sizeof(int));
    if (grauEntrada == NULL || fila == NULL || ordem == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para Kahn.\n");
        exit(EXIT_FAILURE);
    }

    for (int u = 0; u < n; u++) {
        for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
            grauEntrada[atual->destino]++;
        }
    }

    int inicio = 0, fim = 0;
    for (int v = 0; v < n; v++) {
        if (grauEntrada[v] == 0) {
            fila[fim++] = v;
        }
    }

    int total = 0;
    while (inicio < fim) {
        int u = fila[inicio++];
        ordem[total++] = u;

        for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
            int v = atual->destino;
            grauEntrada[v]--;
            if (grauEntrada[v] == 0) {
                fila[fim++] = v;
            }
        }
    }

    free(grauEntrada);
    free(fila);

    if (total != n) {
        free(ordem);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = total;
    return ordem;
}

static int dfs_topologica(GrafoLista *g, int u, int *cor, int *pilha, int *topo) {
    cor[u] = 1; /* cinza: em processamento */

    for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
        int v = atual->destino;
        if (cor[v] == 1) {
            return 1; /* aresta de retorno -> ciclo */
        }
        if (cor[v] == 0 && dfs_topologica(g, v, cor, pilha, topo)) {
            return 1;
        }
    }

    cor[u] = 2; /* preto: finalizado */
    pilha[(*topo)++] = u;
    return 0;
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int n = g->n;

    int *cor = calloc((size_t)n, sizeof(int));
    int *pilha = malloc((size_t)n * sizeof(int));
    if (cor == NULL || pilha == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para DFS.\n");
        exit(EXIT_FAILURE);
    }

    int topo = 0;
    int ciclo = 0;

    for (int i = 0; i < n && !ciclo; i++) {
        if (cor[i] == 0) {
            if (dfs_topologica(g, i, cor, pilha, &topo)) {
                ciclo = 1;
            }
        }
    }

    free(cor);

    if (ciclo) {
        free(pilha);
        *tamanho = 0;
        return NULL;
    }

    int *ordem = malloc((size_t)n * sizeof(int));
    if (ordem == NULL) {
        fprintf(stderr, "Erro: falha ao alocar vetor de ordem.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        ordem[i] = pilha[n - 1 - i];
    }

    free(pilha);
    *tamanho = n;
    return ordem;
}

int eh_dag(GrafoLista *g) {
    int tamanho;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);

    if (ordem == NULL) {
        return 0;
    }

    free(ordem);
    return 1;
}
