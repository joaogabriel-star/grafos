#include <stdio.h>
#include <stdlib.h>

#include "busca_profundidade.h"

Pilha *pilha_criar(int capacidade) {
    Pilha *p = malloc(sizeof(Pilha));
    if (p == NULL) {
        fprintf(stderr, "Erro: falha ao alocar pilha.\n");
        exit(EXIT_FAILURE);
    }

    p->dados = malloc((size_t)capacidade * sizeof(int));
    if (p->dados == NULL) {
        fprintf(stderr, "Erro: falha ao alocar dados da pilha.\n");
        free(p);
        exit(EXIT_FAILURE);
    }

    p->capacidade = capacidade;
    p->topo = -1;

    return p;
}

void pilha_destruir(Pilha *p) {
    if (p == NULL) {
        return;
    }
    free(p->dados);
    free(p);
}

int pilha_vazia(const Pilha *p) {
    return p->topo == -1;
}

void pilha_empilhar(Pilha *p, int valor) {
    if (p->topo + 1 == p->capacidade) {
        fprintf(stderr, "Erro: pilha cheia.\n");
        exit(EXIT_FAILURE);
    }

    p->topo++;
    p->dados[p->topo] = valor;
}

int pilha_desempilhar(Pilha *p) {
    if (pilha_vazia(p)) {
        fprintf(stderr, "Erro: pilha vazia.\n");
        exit(EXIT_FAILURE);
    }

    int valor = p->dados[p->topo];
    p->topo--;

    return valor;
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred, int *ordem, int *contador) {
    visitado[u] = 1;
    ordem[u] = *contador;
    (*contador)++;

    for (NoAdj *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
        int v = atual->vertice;
        if (!visitado[v]) {
            pred[v] = u;
            dfs_recursiva(g, v, visitado, pred, ordem, contador);
        }
    }
}

static int dfs_tem_ciclo(GrafoLista *g, int u, int pai, int *visitado) {
    visitado[u] = 1;

    for (NoAdj *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
        int v = atual->vertice;
        if (!visitado[v]) {
            if (dfs_tem_ciclo(g, v, u, visitado)) {
                return 1;
            }
        } else if (v != pai) {
            /* Vizinho ja visitado que nao e o pai: aresta de retorno -> ciclo. */
            return 1;
        }
    }

    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = malloc((size_t)g->numVertices * sizeof(int));
    if (visitado == NULL) {
        fprintf(stderr, "Erro: falha ao alocar vetor de visitados.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < g->numVertices; i++) {
        visitado[i] = 0;
    }

    int ciclo = 0;
    for (int inicio = 0; inicio < g->numVertices && !ciclo; inicio++) {
        if (!visitado[inicio]) {
            if (dfs_tem_ciclo(g, inicio, -1, visitado)) {
                ciclo = 1;
            }
        }
    }

    free(visitado);

    return ciclo;
}
