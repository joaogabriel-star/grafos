#ifndef PLANARIDADE_H
#define PLANARIDADE_H

#include "conectividade.h"

/*
 * Verifica a condicao necessaria de Euler para grafos planares conexos:
 * m <= 3n - 6, para n >= 3 (grafos com n < 3 vertices sao sempre planares).
 * Retorna 1 se a condicao for satisfeita (o grafo PODE ser planar - a condicao
 * e necessaria, mas nao suficiente) e 0 se ela for violada (o grafo certamente
 * NAO e planar).
 */
int eh_planar_euler(GrafoLista *g);

/*
 * HEURISTICA de forca bruta (recomendada apenas para n <= 10, pelo custo
 * combinatorio de C(n,5) e C(n,6) subconjuntos): procura, entre os
 * subconjuntos de vertices do grafo, 5 vertices mutuamente adjacentes (um K5)
 * ou 6 vertices que possam ser divididos em dois grupos de 3 com todas as 9
 * arestas cruzadas presentes (um K3,3).
 *
 * IMPORTANTE: esta funcao busca K5/K3,3 como SUBGRAFOS diretos (usando apenas
 * arestas ja existentes entre os vertices escolhidos), e NAO subdivisoes
 * topologicas completas (que permitiriam caminhos com vertices de grau 2 no
 * lugar de arestas diretas, como exige o Teorema de Kuratowski). Por isso,
 * esta funcao e uma HEURISTICA: se ela retornar 1, o grafo certamente NAO e
 * planar; mas se retornar 0, isso NAO prova que o grafo e planar (pode haver
 * uma subdivisao de K5/K3,3 que esta funcao nao detecta). Nao substitui um
 * algoritmo completo de teste de planaridade (ex.: Boyer-Myrvold).
 */
int contem_k5_ou_k33_forca_bruta(GrafoLista *g);

#endif /* PLANARIDADE_H */
