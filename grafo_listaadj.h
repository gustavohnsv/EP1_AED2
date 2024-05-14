#include <stdbool.h>

#define MAXNUMVERTICES 100
#define AN NULL

typedef int Peso;
typedef struct str_aresta
{
    int vdest;
    Peso peso;
    struct str_aresta* prox;
} Aresta;

typedef struct 
{
    Aresta** listaAdj;
    int numVertices;
    int numArestas;
} Grafo;

typedef Aresta* Apontador;
int obtemNumVertices(Grafo *g);
Apontador primeiroListaAdj(int v, Grafo* g);
Apontador proxListaAdj(int v, Grafo* g, Apontador atual);
int obtemVerticeDestino(Apontador p, Grafo* g);
bool verificaVertice(Grafo *g, int num);
bool inicializaGrafo(Grafo *g, int nv);
bool insereAresta(Grafo *g, int v1, int v2, Peso peso);
bool removeAresta(Grafo *g, int v1, int v2);
void exibeGrafo(Grafo *g);