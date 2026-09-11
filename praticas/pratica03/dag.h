#ifndef DAG_H
#define DAG_H

/* Reaproveitado de praticas/pratica01/grafo_lista.h, adaptado para grafo dirigido. */
typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **adj;
} GrafoLista;

GrafoLista *criar_grafo_lista(int n);
void liberar_grafo_lista(GrafoLista *grafo);

/* Insere um arco dirigido u -> v (diferente da versao nao-dirigida da pratica 01). */
void inserir_arco(GrafoLista *grafo, int u, int v);

/*
 * Ordenacao topologica pelo algoritmo de Kahn (fila + grau de entrada).
 * Retorna um vetor alocado dinamicamente com a ordem topologica e escreve
 * o numero de elementos em *tamanho, ou retorna NULL (e *tamanho = 0) se
 * o grafo possuir ciclo.
 */
int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);

/*
 * Ordenacao topologica por DFS, empilhando os vertices na saida (pos-ordem)
 * e invertendo a pilha ao final. Retorna NULL (e *tamanho = 0) se o grafo
 * possuir ciclo.
 */
int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);

/* Retorna 1 se o grafo dirigido for aciclico (DAG), 0 caso contrario. */
int eh_dag(GrafoLista *g);

#endif /* DAG_H */
