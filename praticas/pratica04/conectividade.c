#include <stdio.h>
#include <stdlib.h>

#include "conectividade.h"

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

static void inserir_no(No **lista, int destino) {
    No *no = malloc(sizeof(No));
    if (no == NULL) {
        fprintf(stderr, "Erro: falha ao alocar no de adjacencia.\n");
        exit(EXIT_FAILURE);
    }

    no->destino = destino;
    no->prox = *lista;
    *lista = no;
}

void inserir_aresta_lista(GrafoLista *grafo, int u, int v) {
    inserir_no(&grafo->adj[u], v);
    inserir_no(&grafo->adj[v], u);
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

static int menor(int a, int b) {
    return a < b ? a : b;
}

/*
 * Nucleo comum da DFS de Tarjan: calcula descoberta[] e low[] e, durante o
 * percurso, marca os vertices de articulacao em artic[] (se nao for NULL) e
 * registra as pontes em pontesU[]/pontesV[] (se nao forem NULL), usando a
 * condicao classica low[v] > descoberta[u] para pontes e low[v] >= descoberta[u]
 * (para filhos de vertices nao-raiz) ou mais de um filho na raiz para articulacoes.
 */
static void dfs_tarjan(GrafoLista *g, int u, int *descoberta, int *low, int *pai,
                        int *visitado, int *tempo, int *artic,
                        int *pontesU, int *pontesV, int *numPontes) {
    visitado[u] = 1;
    descoberta[u] = low[u] = (*tempo)++;
    int filhos = 0;

    for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
        int v = atual->destino;

        if (!visitado[v]) {
            filhos++;
            pai[v] = u;

            dfs_tarjan(g, v, descoberta, low, pai, visitado, tempo, artic, pontesU, pontesV, numPontes);

            low[u] = menor(low[u], low[v]);

            if (artic != NULL) {
                if (pai[u] == -1 && filhos > 1) {
                    artic[u] = 1;
                }
                if (pai[u] != -1 && low[v] >= descoberta[u]) {
                    artic[u] = 1;
                }
            }

            if (pontesU != NULL && pontesV != NULL && low[v] > descoberta[u]) {
                pontesU[*numPontes] = u;
                pontesV[*numPontes] = v;
                (*numPontes)++;
            }
        } else if (v != pai[u]) {
            low[u] = menor(low[u], descoberta[v]);
        }
    }
}

static void executar_tarjan(GrafoLista *g, int *artic, int *pontesU, int *pontesV, int *numPontes) {
    int n = g->n;

    int *descoberta = malloc((size_t)n * sizeof(int));
    int *low = malloc((size_t)n * sizeof(int));
    int *pai = malloc((size_t)n * sizeof(int));
    int *visitado = calloc((size_t)n, sizeof(int));
    if (descoberta == NULL || low == NULL || pai == NULL || visitado == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para Tarjan.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        pai[i] = -1;
    }

    int tempo = 0;
    *numPontes = 0;

    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            dfs_tarjan(g, i, descoberta, low, pai, visitado, &tempo, artic, pontesU, pontesV, numPontes);
        }
    }

    free(descoberta);
    free(low);
    free(pai);
    free(visitado);
}

int dfs_articulacoes(GrafoLista *g, int *artic) {
    for (int i = 0; i < g->n; i++) {
        artic[i] = 0;
    }

    int numPontes = 0;
    executar_tarjan(g, artic, NULL, NULL, &numPontes);

    int total = 0;
    for (int i = 0; i < g->n; i++) {
        if (artic[i]) {
            total++;
        }
    }

    return total;
}

int detectar_pontes(GrafoLista *g, int *pontesU, int *pontesV) {
    int numPontes = 0;
    executar_tarjan(g, NULL, pontesU, pontesV, &numPontes);
    return numPontes;
}
