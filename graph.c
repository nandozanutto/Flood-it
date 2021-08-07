#include "graph.h"
#include<stdio.h>
#include<stdlib.h>

static int **MATRIXint( int r, int c, int val) { 
   int **m = malloc( r * sizeof (int *));
   for (int i = 0; i < r; ++i) 
      m[i] = malloc( c * sizeof (int));
   for (int i = 0; i < r; ++i)
      for (int j = 0; j < c; ++j)
         m[i][j] = val;
   return m;
}



Graph GRAPHinit( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->raiz = 0;
   G->adj = MATRIXint( V, V+4, 0);
   G->numExcluidos = 0;
   return G;
}



void GRAPHinsertArc( Graph G, int v, int w) { 
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1; 
        G->A++;
    }
   
}

void GRAPHremoveArc( Graph G, int v, int w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

void GRAPHshow( Graph G) { 
    // for(int i=0; i<G->V; i++){
    //     for(int j=0; j<G->V; j++){
    //         printf("%d", G->adj[i][j]);
    //     }
    //     printf("\n");
    // }

   for (int v = 0; v < G->V; ++v) {
      printf( "%2d(color %d excluido %d): ", v, G->adj[v][G->V], G->adj[v][G->V+1]);
      for (int w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1) 
            printf( " %2d", w);
      printf( "\n");
   }
}


void GRAPHshow2( Graph G) { 
//esta variação checa se o vértice está morto antes de imprimir
   for (int v = 0; v < G->V; ++v) {
      printf( "%2d(color %d excluido %d): ", v, G->adj[v][G->V], G->adj[v][G->V+1]);
      if(G->adj[v][G->V+1]){ 
        printf( "\n");
        continue;//v foi excluido
      }
      for (int w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1 && !G->adj[w][G->V+1])//se é vizinho E tá vivo 
            printf( " %2d", w);
      printf( "\n");
   }
}

void lerArestas(Graph G, int numL, int numC){
//loops separados para evitar dependência (otimização) 
    for(int i=1; i<numL-1; i++){
        for(int j=1; j<numC-1; j++){

            GRAPHinsertArc(G, i*numC + j, i*numC + j + 1);//vizinho da direita
            GRAPHinsertArc(G, i*numC + j, i*numC + j - 1);//vizinho da esquerda
            GRAPHinsertArc(G, i*numC + j, (i-1)*numC + j);//vizinho de cima
            GRAPHinsertArc(G, i*numC + j, (i+1)*numC + j);//vizinho de baixo
        }
    }
    for(int j=1; j<numC-1; j++){//linha 0
        GRAPHinsertArc(G, j, j + 1);//vizinho da direita
        GRAPHinsertArc(G, j, j - 1);//vizinho da esquerda
        GRAPHinsertArc(G, j, numC + j);//vizinho de baixo
        //nao tem vizinho de cima
        int i=numL-1;
        GRAPHinsertArc(G, i*numC + j, i*numC + j + 1);//vizinho da direita
        GRAPHinsertArc(G, i*numC + j, i*numC + j - 1);//vizinho da esquerda
        GRAPHinsertArc(G, i*numC + j, (i-1)*numC + j);//vizinho de cima
        //nao tem vizinho de baixo
    }

    for(int i=1; i<numL-1; i++){//coluna 0
        GRAPHinsertArc(G, i*numC, i*numC + 1);//vizinho da direita
        GRAPHinsertArc(G, i*numC, (i-1)*numC);//vizinho de cima
        GRAPHinsertArc(G, i*numC, (i+1)*numC);//vizinho de baixo
        //nao tem vizinho da esquerda
        int j=numC-1;
        GRAPHinsertArc(G, i*numC + j, i*numC + j - 1);//vizinho da esquerda
        GRAPHinsertArc(G, i*numC + j, (i-1)*numC + j);//vizinho de cima
        GRAPHinsertArc(G, i*numC + j, (i+1)*numC + j);//vizinho de baixo
        //nao tem vizinho da direita
    }

    int i=0, j=0;//canto superior esquerdo
    GRAPHinsertArc(G, 0, 1);//vizinho da direita
    GRAPHinsertArc(G, 0, numC);//vizinho de baixo
    //nao tem vizinho da esquerda nem de cima

    i=0; j=numC-1;//canto superior direito
    GRAPHinsertArc(G,  j, j - 1);//vizinho da esquerda
    GRAPHinsertArc(G, j, numC + j);//vizinho de baixo
    //nao tem vizinho de cima nem da direita

    i=numL-1; j=0;//canto inferior esquerdo
    GRAPHinsertArc(G, i*numC + j, i*numC + j + 1);//vizinho da direita
    GRAPHinsertArc(G, i*numC + j, (i-1)*numC + j);//vizinho de cima
    //nao tem vizinho de baixo nem da esquerda

    i=numL-1; j=numC-1;//canto inferior direito
    GRAPHinsertArc(G, i*numC + j, i*numC + j - 1);//vizinho da esquerda
    GRAPHinsertArc(G, i*numC + j, (i-1)*numC + j);//vizinho de cima
    //nao tem vizinho de baixo nem da direita

}