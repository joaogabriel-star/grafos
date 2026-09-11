#include <stdio.h>
#include <stdlib.h>

#include "busca_largura.h"

Fila *fila_criar(int capacidade) {
    Fila *f = malloc(sizeof(Fila));
    if (f == NULL) {
        fprintf(stderr, "Erro: falha ao alocar fila.\n");
        exit(EXIT_FAILURE);
    }

    f->dados = malloc((size_t)capacidade * sizeof(int));
    if (f->dados == NULL) {
        fprintf(stderr, "Erro: falha ao alocar dados da fila.\n");
        free(f);
        exit(EXIT_FAILURE);
    }

    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;

    return f;
}

void fila_destruir(Fila *f) {
    if (f == NULL) {
        return;
    }
    free(f->dados);
    free(f);
}

int fila_vazia(const Fila *f) {
    return f->tamanho == 0;
}

void fila_enfileirar(Fila *f, int valor) {
    if (f->tamanho == f->capacidade) {
        fprintf(stderr, "Erro: fila cheia.\n");
        exit(EXIT_FAILURE);
    }

    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

int fila_desenfileirar(Fila *f) {
    if (fila_vazia(f)) {
        fprintf(stderr, "Erro: fila vazia.\n");
        exit(EXIT_FAILURE);
    }

    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;

    return valor;
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    for (int i = 0; i < g->numVertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    if (origem < 0 || origem >= g->numVertices) {
        return;
    }

    Fila *f = fila_criar(g->numVertices);

    dist[origem] = 0;
    fila_enfileirar(f, origem);

    while (!fila_vazia(f)) {
        int u = fila_desenfileirar(f);

        for (NoAdj *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
            int v = atual->vertice;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                fila_enfileirar(f, v);
            }
        }
    }

    fila_destruir(f);
}

int eh_bipartido(GrafoLista *g) {
    int *cor = malloc((size_t)g->numVertices * sizeof(int));
    if (cor == NULL) {
        fprintf(stderr, "Erro: falha ao alocar vetor de cores.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < g->numVertices; i++) {
        cor[i] = -1;
    }

    Fila *f = fila_criar(g->numVertices);
    int bipartido = 1;

    for (int inicio = 0; inicio < g->numVertices && bipartido; inicio++) {
        if (cor[inicio] != -1) {
            continue;
        }

        cor[inicio] = 0;
        f->inicio = f->fim = f->tamanho = 0;
        fila_enfileirar(f, inicio);

        while (!fila_vazia(f) && bipartido) {
            int u = fila_desenfileirar(f);

            for (NoAdj *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
                int v = atual->vertice;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila_enfileirar(f, v);
                } else if (cor[v] == cor[u]) {
                    bipartido = 0;
                    break;
                }
            }
        }
    }

    fila_destruir(f);
    free(cor);

    return bipartido;
}

int contar_componentes(GrafoLista *g) {
    int *visitado = malloc((size_t)g->numVertices * sizeof(int));
    if (visitado == NULL) {
        fprintf(stderr, "Erro: falha ao alocar vetor de visitados.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < g->numVertices; i++) {
        visitado[i] = 0;
    }

    Fila *f = fila_criar(g->numVertices);
    int componentes = 0;

    for (int inicio = 0; inicio < g->numVertices; inicio++) {
        if (visitado[inicio]) {
            continue;
        }

        componentes++;
        visitado[inicio] = 1;
        f->inicio = f->fim = f->tamanho = 0;
        fila_enfileirar(f, inicio);

        while (!fila_vazia(f)) {
            int u = fila_desenfileirar(f);

            for (NoAdj *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
                int v = atual->vertice;
                if (!visitado[v]) {
                    visitado[v] = 1;
                    fila_enfileirar(f, v);
                }
            }
        }
    }

    fila_destruir(f);
    free(visitado);

    return componentes;
}
