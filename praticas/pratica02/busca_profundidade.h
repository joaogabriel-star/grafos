#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "grafo_lista.h"

/* Pilha usada como estrutura auxiliar de apoio a busca em profundidade. */
typedef struct {
    int *dados;
    int topo;
    int capacidade;
} Pilha;

Pilha *pilha_criar(int capacidade);
void pilha_destruir(Pilha *p);
int pilha_vazia(const Pilha *p);
void pilha_empilhar(Pilha *p, int valor);
int pilha_desempilhar(Pilha *p);

/*
 * Busca em profundidade recursiva a partir de "u".
 * visitado[i] marca se o vertice i ja foi visitado.
 * pred[i] recebe o predecessor de i na arvore/floresta de busca.
 * ordem[i] recebe a ordem (tempo) de descoberta de i.
 * contador e um "tempo global" incrementado a cada descoberta.
 */
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred, int *ordem, int *contador);

/* Retorna 1 se o grafo (nao-direcionado) possuir algum ciclo, 0 caso contrario. */
int tem_ciclo(GrafoLista *g);

#endif /* BUSCA_PROFUNDIDADE_H */
