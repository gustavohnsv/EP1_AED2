#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo_matrizadj.h"

int obtemNumVertices(Grafo *g) {
    return g->numVertices;
}

Apontador primeiroListaAdj(int v, Grafo* g) {
    if (!(verificaVertice(g, v))) {
        return AN;
    }
    for (int i = 0; i < obtemNumVertices(g); i++) {
        if (g->mat[v][i] != AN) {
            return i;
        }
    }
    return AN;
}

Apontador proxListaAdj(int v, Grafo* g, Apontador atual) {
    if (!(verificaVertice(g, v)) || !(verificaVertice(g, atual))) {
        return AN;
    }
    for (int i = atual+1; i < obtemNumVertices(g); i++) {
        if (g->mat[v][i] != AN) {
            return i;
        }
    }
    return AN;
}

int obtemVerticeDestino(Apontador p, Grafo* g) {
    if (!(verificaVertice(g, p))) {
        return AN;
    }
    for (int i = p; i < obtemNumVertices(g); i++) {
        if (g->mat[p][i]) {
            return i;
        }
    }
    return AN;
}

bool verificaVertice(Grafo *g, int num) {
    if (num > g->numVertices)
    {
        fprintf(stderr, "ERRO: O vértice ultrapassa o limite de vértices.");
        return false;
    }
    if (num < 0)
    {
        fprintf(stderr, "ERRO: O vértice não pode ser negativo.");
        return false;
    }
    return true;
}

bool inicializaGrafo(Grafo *g, int nv) {
    int i, j;
    if (nv > MAXNUMVERTICES)
    {
        fprintf(stderr, "ERRO: Número de vértices maior que o permitido de %d.", MAXNUMVERTICES);
        exit(-1);
    }

    if (nv <= 0)
    {
        fprintf(stderr, "ERRO: O número de vértices deve ser maior que 0.");
        exit(-1);
    }

    g->numVertices = nv;
    g->numArestas = 0;

    for (i = 0; i < g->numVertices; i++)
    {
        for (j = 0; j < g->numVertices; j++)
        {
            g->mat[i][j] = AN;
        }
    }
    return true;
}

bool insereAresta(Grafo *g, int v1, int v2, Peso peso) {
    if ((!verificaVertice(g, v1)) && (!verificaVertice(g, v2)))
        return false;
    g->numArestas = g->numArestas + 2;
    g->mat[v1][v2] = peso;
    g->mat[v2][v1] = peso;
    return true;
}

bool removerAresta(Grafo *g, int v1, int v2) {
    if ((!verificaVertice(g, v1)) && (!verificaVertice(g, v2)))
        return false;
    g->mat[v1][v2] = AN;
    g->mat[v2][v1] = AN;
    g->numArestas = g->numArestas - 2;
    return true;
}

void exibeGrafo(Grafo *g) {
    int i, j;

    for (i = 0; i < g->numVertices; i++)
    {
        for (j = 0; j < g->numVertices; j++)
        {
            printf("%d ", g->mat[i][j]);
        }
        printf("\n");
    }
}