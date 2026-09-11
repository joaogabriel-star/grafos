#include <stdio.h>

#include "planaridade.h"

int eh_planar_euler(GrafoLista *g) {
    int n = g->n;

    if (n < 3) {
        return 1;
    }

    int somaGraus = 0;
    for (int u = 0; u < n; u++) {
        for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
            somaGraus++;
        }
    }
    int m = somaGraus / 2; /* cada aresta e contada duas vezes na lista de adjacencia */

    return m <= 3 * n - 6;
}

static int adjacente(const GrafoLista *g, int u, int v) {
    for (No *atual = g->adj[u]; atual != NULL; atual = atual->prox) {
        if (atual->destino == v) {
            return 1;
        }
    }
    return 0;
}

static int contar_bits(int x) {
    int contagem = 0;
    while (x != 0) {
        contagem += x & 1;
        x >>= 1;
    }
    return contagem;
}

/* Verifica se os 5 vertices em verts[] sao mutuamente adjacentes (formam um K5). */
static int eh_k5(const GrafoLista *g, const int *verts) {
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (!adjacente(g, verts[i], verts[j])) {
                return 0;
            }
        }
    }
    return 1;
}

/*
 * Verifica se os 6 vertices em verts[] admitem uma biparticao 3x3 (K3,3):
 * testa todas as formas de separar os 6 vertices em dois grupos de 3,
 * fixando verts[0] no grupo A para nao repetir biparticoes equivalentes.
 */
static int eh_k33(const GrafoLista *g, const int *verts) {
    for (int mascara = 1; mascara < 64; mascara++) {
        if (!(mascara & 1) || contar_bits(mascara) != 3) {
            continue;
        }

        int ok = 1;
        for (int i = 0; i < 6 && ok; i++) {
            int iNoGrupoA = (mascara >> i) & 1;
            if (!iNoGrupoA) {
                continue;
            }
            for (int j = 0; j < 6 && ok; j++) {
                int jNoGrupoA = (mascara >> j) & 1;
                if (!jNoGrupoA && !adjacente(g, verts[i], verts[j])) {
                    ok = 0;
                }
            }
        }

        if (ok) {
            return 1;
        }
    }

    return 0;
}

static int buscar_k5(const GrafoLista *g, int *escolha, int nivel, int inicio) {
    if (nivel == 5) {
        return eh_k5(g, escolha);
    }

    for (int v = inicio; v < g->n; v++) {
        escolha[nivel] = v;
        if (buscar_k5(g, escolha, nivel + 1, v + 1)) {
            return 1;
        }
    }

    return 0;
}

static int buscar_k33(const GrafoLista *g, int *escolha, int nivel, int inicio) {
    if (nivel == 6) {
        return eh_k33(g, escolha);
    }

    for (int v = inicio; v < g->n; v++) {
        escolha[nivel] = v;
        if (buscar_k33(g, escolha, nivel + 1, v + 1)) {
            return 1;
        }
    }

    return 0;
}

int contem_k5_ou_k33_forca_bruta(GrafoLista *g) {
    if (g->n > 10) {
        fprintf(stderr,
                "Aviso: contem_k5_ou_k33_forca_bruta e uma heuristica de forca bruta "
                "pensada para n <= 10; o custo combinatorio cresce rapidamente acima disso.\n");
    }

    if (g->n >= 5) {
        int escolha5[5];
        if (buscar_k5(g, escolha5, 0, 0)) {
            return 1;
        }
    }

    if (g->n >= 6) {
        int escolha6[6];
        if (buscar_k33(g, escolha6, 0, 0)) {
            return 1;
        }
    }

    return 0;
}
