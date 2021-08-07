#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct graph *Graph;
typedef struct vertex *ApontaVertex;

struct graph {
   int V; 
   int A; 
   int **adj;
   int raiz;
   int numExcluidos; 
};

struct vertex{
    int numVertice;
    int cor;
};

static int **MATRIXint( int r, int c, int val);
Graph GRAPHinit( int V);
void GRAPHinsertArc( Graph G, int v, int w);
void GRAPHremoveArc( Graph G, int v, int w);
void GRAPHshow( Graph G);
void GRAPHshow2( Graph G);
void lerArestas(Graph G, int numL, int numC);




#endif