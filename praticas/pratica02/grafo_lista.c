#include <stdio.h>
#include <stdlib.h>

#include "grafo_lista.h"

GrafoLista *grafo_criar(int numVertices) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    if (g == NULL) {
        fprintf(stderr, "Erro: falha ao alocar grafo.\n");
        exit(EXIT_FAILURE);
    }

    g->numVertices = numVertices;
    g->adj = malloc((size_t)numVertices * sizeof(NoAdj *));
    if (g->adj == NULL) {
        fprintf(stderr, "Erro: falha ao alocar lista de adjacencia.\n");
        free(g);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numVertices; i++) {
        g->adj[i] = NULL;
    }

    return g;
}

void grafo_destruir(GrafoLista *g) {
    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->numVertices; i++) {
        NoAdj *atual = g->adj[i];
        while (atual != NULL) {
            NoAdj *proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }

    free(g->adj);
    free(g);
}

static void inserir_no_inicio(GrafoLista *g, int origem, int destino) {
    NoAdj *novo = malloc(sizeof(NoAdj));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar no de adjacencia.\n");
        exit(EXIT_FAILURE);
    }

    novo->vertice = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
}

/* Grafo nao-direcionado: a aresta e adicionada nos dois sentidos. */
void grafo_add_aresta(GrafoLista *g, int u, int v) {
    if (g == NULL || u < 0 || v < 0 || u >= g->numVertices || v >= g->numVertices) {
        return;
    }

    inserir_no_inicio(g, u, v);
    inserir_no_inicio(g, v, u);
}

void grafo_imprimir(const GrafoLista *g) {
    if (g == NULL) {
        return;
    }

    for (int i = 0; i < g->numVertices; i++) {
        printf("%d:", i);
        for (NoAdj *atual = g->adj[i]; atual != NULL; atual = atual->prox) {
            printf(" -> %d", atual->vertice);
        }
        printf("\n");
    }
}
