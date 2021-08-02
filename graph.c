#include<stdio.h>
#include<stdlib.h>

typedef struct graph *Graph;
typedef struct vertex *ApontaVertex;
typedef struct mudanca *ApontaMudanca;
typedef struct nodo *ApontaNodo;

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa um grafo. O campo adj é um ponteiro para a matriz de adjacências do grafo. O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */

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

struct mudanca{
    int raizAntiga;
    int corDaRaizAntiga;
    ApontaNodo listaMudanca;

};

struct nodo{
    int *mudou;
    ApontaNodo proximo;
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
   G->raiz = 0;
   G->adj = MATRIXint( V, V+2, 0);
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

ApontaMudanca criaMudanca(){
    ApontaMudanca mudanca = (ApontaMudanca) malloc(sizeof(struct mudanca));
    mudanca->listaMudanca = NULL;
    return mudanca;
}

void adicionaMudanca(ApontaMudanca mudanca, int * mudou){
    if(mudanca->listaMudanca == NULL){
        mudanca->listaMudanca = (ApontaNodo) malloc(sizeof(struct nodo));
        mudanca->listaMudanca->proximo = NULL;
        mudanca->listaMudanca->mudou = mudou;
    }
    else{
        ApontaNodo aux = mudanca->listaMudanca;
        ApontaNodo newNodo = (ApontaNodo) malloc(sizeof(struct nodo));
        newNodo->proximo = aux;
        newNodo->mudou = mudou;
        mudanca->listaMudanca = newNodo;//novo nodo passa ser cabeça
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
    if(G->adj[o][G->V+1]) return;//o já foi removido!!!!
    if(o == G->raiz)//raiz foi removida por d
        G->raiz = d;
    for(int i=0; i<G->V; i++){
        G->adj[d][i] = G->adj[d][i] || G->adj[o][i];//copiando a vizinhança o para d
        G->adj[i][d] = G->adj[i][d] || G->adj[i][o];//faz os vizinhos de o apontarem pra d 
        G->adj[i][o] = 0;//zera os arcos para o
        G->adj[o][i] = 0;//zero os arcos de o
        G->adj[i][i] = 0;//exclui possível aresta pro mesmo nodo
    }
    G->adj[o][G->V+1] = 1;//mata vertice
    G->numExcluidos++;

}

void copiaVizinhos2(int o, int d, Graph G, ApontaMudanca mudanca){
    if(G->adj[o][G->V+1]) return;//o já foi removido!!!!
    if(o == G->raiz)//raiz foi removida por d
        G->raiz = d;
    for(int i=0; i<G->V; i++){
        int valorAntigo = G->adj[d][i];
        G->adj[d][i] = G->adj[d][i] || G->adj[o][i];//copiando a vizinhança o para d
        if(G->adj[d][i] != valorAntigo)//este valor mudou
            adicionaMudanca(mudanca, G->adj[d] + i);

        valorAntigo = G->adj[i][d];
        G->adj[i][d] = G->adj[i][d] || G->adj[i][o];//faz os vizinhos de o apontarem pra d 
        if(G->adj[i][d] != valorAntigo)//este valor mudou
            adicionaMudanca(mudanca, G->adj[i] + d);

        // G->adj[i][o] = 0;//zera os arcos para o
        // G->adj[o][i] = 0;//zero os arcos de o
        G->adj[i][i] = 0;//exclui possível aresta pro mesmo nodo
    }
    G->adj[o][G->V+1] = 1;//mata vertice
    adicionaMudanca(mudanca, G->adj[o] + G->V+1);//este valor mudou

    G->numExcluidos++;

}

void GRAPHshow2( Graph G) { 
    // for(int i=0; i<G->V; i++){
    //     for(int j=0; j<G->V; j++){
    //         printf("%d", G->adj[i][j]);
    //     }
    //     printf("\n");
    // }

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

void pintaVertice(Graph G, int v, int cor, ApontaMudanca mudanca){ 
    mudanca->raizAntiga = G->raiz;//salvando raiz
    if(v != G->raiz)//só pode pintar a raiz
        return;
    mudanca->corDaRaizAntiga = G->adj[v][G->V];//salvando a cor da raiz
    G->adj[v][G->V] = cor;
    //necessário checar se ao mudar de cor o vértice junta com algum vizinho
    for(int i=0; i<G->V; i++){
        if(i != v && G->adj[v][i] && G->adj[i][G->V] == cor){//se é vizinho de v e tem a mesma cor
            copiaVizinhos2(i, v, G, mudanca);//mato vizinho
        }
    }
}

void despinta(Graph G, ApontaMudanca mudanca){
    //revertendo mudanças feitas
    G->raiz = mudanca->raizAntiga;
    G->adj[G->raiz][G->V] = mudanca->corDaRaizAntiga;
    for(ApontaNodo aux=mudanca->listaMudanca; aux!=NULL; aux=aux->proximo){
        *aux->mudou = (*aux->mudou + 1)%2;//inverte valor 0 -> 1 1 -> 0 
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

    // for(int i=0; i<numL; i++){
    //     for(int j=0; j<numC; j++)
    //         printf("%d ", matrix[i][j]);
    //     printf("\n");
    // }

    G = GRAPHinit(numL*numC);
    lerArestas(G, numL, numC);
    // GRAPHshow(G);


    printf("tam do grafo %d\n", G->V);
    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++){
            G->adj[i*numC+j][G->V] = matrix[i][j];//salvando cor do vertice
            G->adj[i*numC+j][G->V+1] = 0;//ainda nao foi excluido
            // if(j>0 && matrix[i][j] == matrix[i][j-1])//vizinho da esquerda
            //     copiaVizinhos(i*numC + j -1, i*numC+j, G);
            // if(i>0 && matrix[i][j] == matrix[i-1][j])//vizinho de cima
            //     copiaVizinhos((i-1)*numC + j, i*numC+j, G);
        
        }
    }

    for(int i=0; i<G->V; i++){
        for(int vizinho=0; vizinho<i; vizinho++){//checa aqueles que vieram antes
            if(G->adj[i][vizinho] && G->adj[i][G->V] == G->adj[vizinho][G->V]){//se é vizinho e tem mesma cor
                copiaVizinhos(vizinho, i, G);
            }
        }
    }


    // GRAPHshow(G);
    printf("raiz eh %d\n", G->raiz);
    // pintaVertice(G, G->raiz, 3);
    // pintaVertice(G, G->raiz, 1);
    // pintaVertice(G, G->raiz, 3);
    // pintaVertice(G, G->raiz, 2);
    // pintaVertice(G, G->raiz, 1);
    // printf("raiz eh %d\n", G->raiz);
    // pintaVertice(G, G->raiz, 3);
    // pintaVertice(G, G->raiz, 2);
    // pintaVertice(G, G->raiz, 1);
    // pintaVertice(G, G->raiz, 3);
    // pintaVertice(G, G->raiz, 2);
    // pintaVertice(G, G->raiz, 1);
    // printf("raiz eh %d\n", G->raiz);

    ApontaMudanca mudanca = criaMudanca();
    int numPaint=0;
    int corPaint;
    GRAPHshow(G);
    scanf("%d", &numPaint);
    for(int i=0; i<numPaint; i++){
        GRAPHshow2(G);
        scanf("%d", &corPaint);
        pintaVertice(G, G->raiz, corPaint, mudanca);
        // printf("raiz eh %d\n", G->raiz);
        printf("******************\n");
    }


    // printf("**********antes de pintar\n");
    // GRAPHshow2(G);
    // pintaVertice(G, G->raiz, 3, mudanca);
    // printf("**********depois de pintar\n");
    // GRAPHshow2(G);
    // despinta(G, mudanca);
    // printf("**********depois de DESpintar\n");
    // GRAPHshow2(G);

    // G->adj[G->V-1][G->V] = 4;
    // int * teste = G->adj[G->V-1] + G->V;
    // *teste = 6;

    GRAPHshow2(G);
    printf("excluidos %d raiz %d\n", G->numExcluidos, G->raiz);



    return 0;
}