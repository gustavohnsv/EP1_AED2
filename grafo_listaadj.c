#include <stdio.h>
#include <stdlib.h>
#include "grafo_listaadj.h"

int obtemNumVertices(Grafo *g) {
    return (g->numVertices);
}

Apontador primeiroListaAdj(int v, Grafo* g) {
    return g->listaAdj[v];
}

Apontador proxListaAdj(int v, Grafo* g, Apontador atual) {
    if (atual == NULL) {
        fprintf(stderr, "ERRO: atual = NULL");
        return NULL;
    }
    return(atual->prox);
}

int obtemVerticeDestino(Apontador p, Grafo* g) {
    return p->vdest;
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
    if (nv <= 0)
    {
        fprintf(stderr, "ERRO: O número de vértices deve ser maior que 0.");
        exit(-1);
    }
    g->numVertices = nv;
    if (!(g->listaAdj = (Apontador *)calloc(nv, sizeof(Apontador))))
    {
        fprintf(stderr, "ERRO: Não foi possível alocar espaço na memória para o grafo.");
        return false;
    }
    g->numArestas = 0;
    return true;
}

bool insereAresta(Grafo *g, int v1, int v2, Peso peso) {
    Apontador p, q;
    if (!(verificaVertice(g, v1) && verificaVertice(g, v2))) // VERIFICA SE OS VERTICES EXISTEM NO GRAFO
        return false;
    if (!(p = (Apontador)calloc(1, sizeof(Aresta)))) // ALOCA DINAMICAMENTE UMA ARESTA E, SE A OPERAÇÃO DER ERRO, RETORNA AO USUÁRIO O ERRO
    {
        fprintf(stderr, "ERRO: Não foi possível alocar espaço na memória para a aresta.");
        return false;
    }
    if (!(q = (Apontador)calloc(1, sizeof(Aresta)))) // ALOCA DINAMICAMENTE UMA ARESTA E, SE A OPERAÇÃO DER ERRO, RETORNA AO USUÁRIO O ERRO
    {
        fprintf(stderr, "ERRO: Não foi possível alocar espaço na memória para a aresta.");
        return false;
    }
    p->vdest = v2;             
    p->peso = peso;            
    p->prox = g->listaAdj[v1]; 
    g->listaAdj[v1] = p; 

    q->vdest = v1;             
    q->peso = peso;            
    q->prox = g->listaAdj[v2]; 
    g->listaAdj[v2] = q;       

    g->numArestas = g->numArestas + 2;           
    return true;
}

bool removeAresta(Grafo *g, int v1, int v2) {
    Apontador p, q, antV1, antV2;
    if (!(verificaVertice(g, v1) && verificaVertice(g, v2))) // VERIFICA SE OS VERTICES EXISTEM NO GRAFO
        return false;
    q = g->listaAdj[v1];
    p = g->listaAdj[v2];
    while (q && (q->vdest != v2)) // PROCURA PELA ARESTA QUE ESTÁ APONTANDO PARA O MEU VÉRTICE DESTINO (v2)
    {
        antV1 = q;     // ajusta o anterior para ser q
        q = q->prox; // ajusta q para a próxima aresta da lista
    }
    while (p && (p->vdest != v1)) // PROCURA PELA ARESTA QUE ESTÁ APONTANDO PARA O MEU VÉRTICE DESTINO (v1)
    {
        antV2 = p;     // ajusta o anterior para ser p
        p = p->prox; // ajusta p para a próxima aresta da lista
    }

    if (q) // se existir q, faça:
    {
        if (g->listaAdj[v1] == q) g->listaAdj[v1] = q->prox; 
        else antV1->prox = q->prox;       
        if (g->listaAdj[v2] == p) g->listaAdj[v2] = p->prox; 
        else antV2->prox = p->prox;       
        q->prox = NULL;                
        p->prox = NULL;                
        free(q);                       
        free(p);                       
        q = NULL;                      
        p = NULL;                      
        g->numArestas = g->numArestas - 2;
        return true;                  
    }
    return false; 
}

void exibeGrafo(Grafo *g) {
    int v;
    Apontador p;
    for (v = 0; v < g->numVertices; v++)
    {
        printf("v%d: ", v);
        p = g->listaAdj[v];
        while (p)
        {
            printf("Destino -> %d Peso -> %d / ", p->vdest, p->peso);
            p = p->prox;
        }
        printf("\n");
    }
}