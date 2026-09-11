#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

/* Reaproveitado de praticas/pratica01/grafo_lista.h e praticas/pratica02 (grafo nao-dirigido). */
typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **adj;
} GrafoLista;

GrafoLista *criar_grafo_lista(int n);
void inserir_aresta_lista(GrafoLista *grafo, int u, int v);
void liberar_grafo_lista(GrafoLista *grafo);

/*
 * Algoritmo de Tarjan com os arrays descoberta[] e low[].
 * Preenche artic[] (deve ter tamanho g->n; artic[i] = 1 se i for vertice de
 * articulacao, 0 caso contrario) e retorna a quantidade de vertices de
 * articulacao encontrados.
 */
int dfs_articulacoes(GrafoLista *g, int *artic);

/*
 * Deteccao de pontes usando a condicao low[v] > descoberta[u].
 * Preenche pontesU[] e pontesV[] (arrays pre-alocados com capacidade >= g->n,
 * ja que uma arvore/floresta com n vertices tem no maximo n - 1 pontes) com os
 * extremos de cada ponte encontrada e retorna a quantidade de pontes.
 */
int detectar_pontes(GrafoLista *g, int *pontesU, int *pontesV);

#endif /* CONECTIVIDADE_H */
