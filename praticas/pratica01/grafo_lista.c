#include <stdlib.h>
#include "grafo_lista.h"

static No *criar_no(int destino) {
    No *no = malloc(sizeof(No));
    no->destino = destino;
    no->prox = NULL;
    return no;
}

static void inserir_no(No **lista, int destino) {
    No *no = criar_no(destino);
    no->prox = *lista;
    *lista = no;
}

static void remover_no(No **lista, int destino) {
    No *atual = *lista;
    No *anterior = NULL;
    while (atual != NULL) {
        if (atual->destino == destino) {
            if (anterior == NULL) {
                *lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

GrafoLista *criar_grafo_lista(int n) {
    GrafoLista *grafo = malloc(sizeof(GrafoLista));
    grafo->n = n;
    grafo->adj = calloc((size_t)n, sizeof(No *));
    return grafo;
}

void inserir_aresta_lista(GrafoLista *grafo, int u, int v) {
    inserir_no(&grafo->adj[u], v);
    inserir_no(&grafo->adj[v], u);
}

void remover_aresta_lista(GrafoLista *grafo, int u, int v) {
    remover_no(&grafo->adj[u], v);
    remover_no(&grafo->adj[v], u);
}

int grau_lista(GrafoLista *grafo, int v) {
    int grau = 0;
    No *atual = grafo->adj[v];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

int sao_adjacentes_lista(GrafoLista *grafo, int u, int v) {
    No *atual = grafo->adj[u];
    while (atual != NULL) {
        if (atual->destino == v) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *grafo) {
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
