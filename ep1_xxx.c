/*  

    GERAR EXECUTAVEL PARA MATRIZ: make CFLAGS+="-DMATRIZ" ep1_matriz
    GERAR EXECUTAVEL PARA LISTA: make ep1_lista

*/

#include <stdio.h>
#include <stdlib.h>
#ifdef MATRIZ
#include "grafo_matrizadj.h"
#else
#include "grafo_listaadj.h"
#endif
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct estrutura {
    int chave;
    struct aux* prox;
} NO;

typedef struct {
    NO* inicio;
    NO* fim;
} FILA;

void inicializaFila(FILA* f);
void insereFila(int ch, FILA* f);
int removeFila(FILA* f);
bool leGrafo(char* nomearq, Grafo* g);

void inicializaFila(FILA* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void insereFila(int ch, FILA* f) {
    NO* novo;
    novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = NULL;
    if(f->fim) 
        f->fim->prox = novo; // fila não é vazia
    else 
        f->inicio = novo; // 1a. inserção em fila vazia
    f->fim = novo;
}

int removeFila(FILA* f) {
    NO* aux;
    int ch;
    if(!f->inicio) 
        return(-1); // fila vazia
    ch = f->inicio->chave;
    aux = f->inicio;
    f->inicio = f->inicio->prox;
    free(aux);
    if(!f->inicio)  
        f->fim = NULL; // fila ficou vazia
    return(ch);
}

bool leGrafo(char* nomearq, Grafo* g) {
    FILE *fr;
    int nvertices, narestas;
    int v1, v2;
    Peso peso;

    fr = fopen(nomearq, "r");
    if (!fr) { 
        fprintf(stderr, "ERRO: Arquivo não existe.");
        return false;
    } 
    if (fscanf(fr, "%d %d", &nvertices, &narestas)!=2) {
        fprintf(stderr, "ERRO: Argumentos inválidos");
        return false;
    }
    inicializaGrafo(g, nvertices);
    for (int i = 0; i < narestas; i++) {
        if (fscanf(fr, "%d %d %d", &v1, &v2, &peso)!=3) {
            fprintf(stderr, "ERRO: Leitura inválida");
            return false;
        }
        if (!verificaVertice(g, v1) || !verificaVertice(g, v2)) {
            fprintf(stderr, "ERRO: Vértices inválidos.");
            return false;
        }
        insereAresta(g, v1, v2, peso);
    }
    fclose(fr);
    return true;
}

void imprimeCaminho(int vertice, int* ant) {
    if (vertice == -1) {
        printf("\n");
        return;
    }
    imprimeCaminho(ant[vertice], ant);
    printf("%d ", vertice);
}

void encontraArticulacao(int v, Grafo *g, int *tempo, int *cor, int *tdesc, int *tmenor, int *ant, int *articulacao) {
    int filhos = 0;
    cor[v] = 1;
    tdesc[v] = *tempo;
    tmenor[v] = *tempo;
    (*tempo)++;
    Apontador p = primeiroListaAdj(v, g);
    while (p != AN) {
        int w = obtemVerticeDestino(p, g);
        if (cor[w] == 0) {
            ant[w] = v;
            encontraArticulacao(w, g, tempo, cor, tdesc, tmenor, ant, articulacao);
            filhos++;
            tmenor[v] = min(tmenor[v], tmenor[w]);
            if (tdesc[v] <= tmenor[w] && ant[v] != -1) {
                articulacao[v] = 1;
            }
        } else if (w != ant[v]) {
            tmenor[v] = min(tmenor[v], tdesc[w]);
        }
        p = proxListaAdj(v, g, p);
    }
    if (ant[v] == -1 && filhos > 1) {
        articulacao[v] = 1;
    }
}

void visitaProfundidade(int numAtual, Grafo *g, int *tempo, int *cor, int *tdesc, int *tterm, int *ant) {
    printf("%d ", numAtual);
    cor[numAtual] = 1;
    tdesc[numAtual] = ++(*tempo);
    Apontador p = primeiroListaAdj(numAtual, g); // primeiro da lista de adj
    while(p != AN) {
        int vdest = obtemVerticeDestino(p, g);        
        if (cor[vdest] == 0) {
            ant[vdest] = numAtual;
            visitaProfundidade(vdest, g, tempo, cor, tdesc, tterm, ant);
        }
        p = proxListaAdj(numAtual, g, p);
    }
    tterm[numAtual] = ++(*tempo);
    cor[numAtual] = 2;
}

void buscaProfundidade(Grafo *g) {
    printf("BF: \n");
    int numVertices = obtemNumVertices(g);
    int cor[numVertices];
    int tdesc[numVertices]; // tempo de descoberta
    int tterm[numVertices]; // tempo de término da visita
    int ant[numVertices];
    int tempo = 0;
    for (int i = 0; i < obtemNumVertices(g); i++) { // obtem numero de vertices
        cor[i] = 0;
        tdesc[i] = 0;
        tterm[i] = 0;
        ant[i] = -1;
    }
    for (int i = 0; i < numVertices; i++) { // obtem numero de vertices
        if (cor[i] == 0) visitaProfundidade(i, g, &tempo, cor, tdesc, tterm, ant);
    }
    printf("\n\nCaminhos BF:");
    for (int i = 0; i < numVertices; i++) {
        imprimeCaminho(i, ant);
    }
}

void DFSArticulacao(Grafo *g) {
    int numVertices = obtemNumVertices(g);
    int cor[numVertices];
    int tdesc[numVertices]; // tempo de descoberta
    int tmenor[numVertices]; // menor tempo de descoberta alcançável
    int ant[numVertices];
    int articulacao[numVertices]; // array para armazenar os vértices de articulação
    int tempo = 0;
    for (int i = 0; i < obtemNumVertices(g); i++) {
        cor[i] = 0;
        tdesc[i] = 0;
        tmenor[i] = 0;
        ant[i] = -1;
        articulacao[i] = 0; // Inicialmente nenhum vértice é considerado vértice de articulação
    }
    for (int i = 0; i < numVertices; i++) {
        if (cor[i] == 0) {
            encontraArticulacao(i, g, &tempo, cor, tdesc, tmenor, ant, articulacao); // Chamada para a função que encontra os vértices de articulação
        }
    }
    printf("Vertices de articulacao:\n");
    for (int i = 0; i < numVertices; i++) {
        if (articulacao[i]) {
            printf("%d ", i);
        }
    }
}

void visitaLargura(int numAtual, Grafo *g, int *cor, int *ant, int *distancia, FILA *f) {
    distancia[numAtual] = 0;
    cor[numAtual] = 1;
    Apontador p;
    insereFila(numAtual, f);
    while (f->inicio) {
        int aux = removeFila(f);
        printf("%d ", aux);
        p = primeiroListaAdj(aux, g);
        while (p != AN) { // p == true // p
            int vdest = obtemVerticeDestino(p, g); // obter vertice destino ?
            if (cor[vdest] == 0) {
                cor[vdest] = 1;
                ant[vdest] = aux;
                distancia[vdest] = distancia[aux] + 1;
                insereFila(vdest, f);
            }
            p = proxListaAdj(aux, g, p); // proximo da lista de adjacencia    
        }
    }
}

void buscaEmLargura(Grafo *g) {
    printf("BL: \n");
    int numVertices = obtemNumVertices(g);
    int cor[numVertices];
    int ant[numVertices];
    int distancia[numVertices];

    for (int i = 0; i < obtemNumVertices(g); i++) {
        cor[i] = 0;
        ant[i] = -1;
        distancia[i] = __INT_MAX__;
    }

    FILA* f = (FILA*) malloc(sizeof(FILA));
    inicializaFila(f);

    for (int i = 0; i < numVertices; i++) { // obtem numero de vertices
        if (cor[i] == 0) {
            visitaLargura(i, g, cor, ant, distancia, f);
        }
        /* printf("Vértice -> %d / Antecessor -> %d / Distância -> %d\n", i, ant[i], distancia[i]); */
    }
    printf("\n\nCaminhos BL:");
    for (int i = 0; i < numVertices; i++) {
        imprimeCaminho(i, ant);
    }
    free(f);
}

void visitaComponentes(int numAtual, int* componente, int* cor, Grafo* g, FILA* f) {
    cor[numAtual] = 1;
    Apontador p;
    int tamanhoComponente = numAtual;
    insereFila(numAtual, f);
    while (f->inicio) {
        tamanhoComponente++;
        int aux = removeFila(f);
        p = primeiroListaAdj(aux, g);
        while(p != AN) {
            int vdest = obtemVerticeDestino(p, g);
            if (cor[vdest] == 0) {
                cor[vdest] = 1;
                insereFila(vdest, f);
            }
            p = proxListaAdj(aux, g, p);
        }
    }
    printf("C%d: ", (*componente));
    int k = numAtual;
    do {
        printf("%d ", k);
        k++;
    }
    while(k < tamanhoComponente);
    printf("\n");
}

void componentesConectados(Grafo* g) {
    printf("Componentes Conectados: \n");
    int numVertices = obtemNumVertices(g);
    int cor[numVertices];

    for (int i = 0; i < obtemNumVertices(g); i++) {
        cor[i] = 0;
    }

    FILA* f = (FILA*) malloc(sizeof(FILA));
    inicializaFila(f);
    int j = 1;
    for (int i = 0; i < obtemNumVertices(g); i++) {
        if (cor[i] == 0) {
            visitaComponentes(i, &j, cor, g, f);
            j++;
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    if (argc!=3) {
        fprintf(stderr, "ERRO: Argumentos inválidos");
        return -1;
    }

    Grafo grafo;
    leGrafo(argv[1], &grafo);

    FILE* fw;
    fw = freopen(argv[2], "w", stdout);
    if (fw == NULL) {
        fprintf(stderr, "Erro ao redirecionar a saída para o arquivo.");
        return 1;
    }

    buscaEmLargura(&grafo);
    printf("\n\n");
    buscaProfundidade(&grafo);
    printf("\n\n");
    componentesConectados(&grafo);
    DFSArticulacao(&grafo);
    fclose(fw);
    return 0;
}