#include<stdio.h>
#include<stdlib.h>

typedef struct graph *Graph;
typedef struct vertex *ApontaVertex;

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa um grafo. O campo adj é um ponteiro para a matriz de adjacências do grafo. O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */

struct graph {
   int V; 
   int A; 
   int **adj; 
};


struct vertex{
    int numVertice;
    int cor;
};

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
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
   G->adj = MATRIXint( V, V, 0);
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
    for(int i=0; i<G->V; i++){
        for(int j=0; j<G->V; j++){
            printf("%d", G->adj[i][j]);
        }
        printf("\n");
    }

   for (int v = 0; v < G->V; ++v) {
      printf( "%2d:", v);
      for (int w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1) 
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

void copiaVizinhos(int o, int d, Graph G){

    for(int i=0; i<G->V; i++){
        G->adj[d][i] = G->adj[d][i] || G->adj[o][i];//copiando a vizinhança o para d
        G->adj[i][d] = G->adj[i][d] || G->adj[i][o];//faz os vizinhos de o apontarem pra d 
        G->adj[i][o] = 0;//zera os arcos para o
        G->adj[o][i] = 0;//zero os arcos de o
        G->adj[i][i] = 0;//exclui possível aresta pro mesmo nodo
    }

}

int main(){
    Graph G;

    int numL, numC, numColor;
    scanf("%d %d %d", &numL, &numC, &numColor);
    int matrix[numL][numC];
    for(int i=0; i<numL; i++)
        for(int j=0; j<numC; j++)
            scanf("%d", &matrix[i][j]);

    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    G = GRAPHinit(numL*numC);
    lerArestas(G, numL, numC);

    printf("tam do grafo %d\n", G->V);
    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++){
            if(j>0 && matrix[i][j] == matrix[i][j-1])//vizinho da esquerda
                copiaVizinhos(i*numC + j -1, i*numC+j, G);
            if(i>0 && matrix[i][j] == matrix[i-1][j])//vizinho de cima
                copiaVizinhos((i-1)*numC + j, i*numC+j, G);
        
        }
    }


    GRAPHshow(G);
    return 0;
}