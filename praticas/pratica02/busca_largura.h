#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "grafo_lista.h"

/* Fila circular usada pela BFS. */
typedef struct {
    int *dados;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
} Fila;

Fila *fila_criar(int capacidade);
void fila_destruir(Fila *f);
int fila_vazia(const Fila *f);
void fila_enfileirar(Fila *f, int valor);
int fila_desenfileirar(Fila *f);

/*
 * Busca em largura a partir de "origem".
 * dist[i] recebe a distancia (em numero de arestas) de origem ate i,
 * ou -1 se i nao for alcancavel. pred[i] recebe o predecessor de i na
 * arvore de busca, ou -1 se i for a origem ou nao for alcancavel.
 */
void bfs(GrafoLista *g, int origem, int *dist, int *pred);

/* Retorna 1 se o grafo for bipartido, 0 caso contrario. */
int eh_bipartido(GrafoLista *g);

/* Retorna o numero de componentes conexas do grafo. */
int contar_componentes(GrafoLista *g);

#endif /* BUSCA_LARGURA_H */
