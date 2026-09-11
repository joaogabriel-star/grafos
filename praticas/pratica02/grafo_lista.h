#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

/* Nó da lista de adjacência (reaproveitado da Prática 01). */
typedef struct NoAdj {
    int vertice;
    struct NoAdj *prox;
} NoAdj;

/* Grafo representado por lista de adjacência (reaproveitado da Prática 01). */
typedef struct {
    int numVertices;
    NoAdj **adj;
} GrafoLista;

GrafoLista *grafo_criar(int numVertices);
void grafo_destruir(GrafoLista *g);
void grafo_add_aresta(GrafoLista *g, int u, int v);
void grafo_imprimir(const GrafoLista *g);

#endif /* GRAFO_LISTA_H */
