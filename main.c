#include<stdio.h>
#include<stdlib.h>

typedef struct graph *Graph;
typedef struct vertex *ApontaVertex;
typedef struct mudanca *ApontaMudanca;
typedef struct nodo *ApontaNodo;
typedef struct reg *ApontaLista;

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
    int excluidos;
    int raizAntiga;
    int corDaRaizAntiga;
    ApontaNodo listaMudanca;

};

struct nodo{
    int *mudou;
    ApontaNodo proximo;
};

struct reg { 
   int         cor; 
   ApontaLista prox;
};

ApontaLista criaLista(){
    ApontaLista new = (ApontaLista)malloc(sizeof(struct reg));
    new->prox = NULL;
    return new;
}

void adicionaCor(ApontaLista lista, int cor){
    ApontaLista aux = lista;
    while(aux->prox!=NULL)
        aux=aux->prox;
    ApontaLista new = (ApontaLista)malloc(sizeof(struct reg));
    new->cor = cor;
    new->prox = NULL;
    aux->prox = new;

}

void imprimeCores(ApontaLista lista){
    for(ApontaLista aux = lista->prox; aux!=NULL; aux=aux->prox)
        printf("%d ", aux->cor);
}

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
        if(d == i) continue;
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
    if(v != G->raiz)//só pode pintar a raiz
        return;
    mudanca->raizAntiga = G->raiz;//salvando raiz
    mudanca->excluidos = G->numExcluidos;
    mudanca->corDaRaizAntiga = G->adj[G->raiz][G->V];//salvando a cor da raiz
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
    G->numExcluidos = mudanca->excluidos;//caso algum vertice tenha 'revivido'
}

// A structure to represent a queue
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};


struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
  
    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
        queue->capacity * sizeof(int));
    return queue;
}
  
// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}
  
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
  
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    // printf("%d enqueued to queue\n", item);
}
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
  
// G->adj[G->raiz][G->V+2]: distancia
// G->adj[G->raiz][G->V+3]: estado
int caminhosMinimos(Graph G){
    for(int i=0; i<G->V; i++){
        G->adj[i][G->V+2] = 0;
        G->adj[i][G->V+3] = 0;
    }

    int biggestDistance = 0;
    struct Queue * fila = createQueue(100);
    G->adj[G->raiz][G->V+2] = 0;//distancia pra raiz igual a zero
    enqueue(fila, G->raiz);
    G->adj[G->raiz][G->V+3] = 1;//estado da raiz = 1

    while(!isEmpty(fila)){//enquanto a fila não está vazia
        int v = dequeue(fila);
        for (int w = 0; w < G->V; ++w){
            if(w==v) continue;
            if (G->adj[v][w] == 1 && !G->adj[w][G->V+1]){//se é vizinho E w tá vivo 
                if(!G->adj[w][G->V+3]){
                    G->adj[w][G->V+2] = G->adj[v][G->V+2] + 1;
                    if(G->adj[w][G->V+2]>biggestDistance)biggestDistance = G->adj[w][G->V+2];
                    enqueue(fila, w);
                    G->adj[w][G->V+3] = 1;
                }
            }
        }
        G->adj[v][G->V+3] = 2;
    }

    return biggestDistance;
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


    // printf("tam do grafo %d\n", G->V);
    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++){
            G->adj[i*numC+j][G->V] = matrix[i][j];//salvando cor do vertice
            G->adj[i*numC+j][G->V+1] = 0;//ainda nao foi excluido

        
        }
    }

    for(int i=0; i<G->V; i++){
        for(int vizinho=0; vizinho<i; vizinho++){//checa aqueles que vieram antes
            if(G->adj[i][vizinho] && G->adj[i][G->V] == G->adj[vizinho][G->V]){//se é vizinho e tem mesma cor
                copiaVizinhos(vizinho, i, G);
            }
        }
    }

    int numPint = 0;
    // GRAPHshow(G);
    ApontaLista lista = criaLista();
    ApontaMudanca aux = criaMudanca();
    while(G->numExcluidos != G->V-1){
        // printf("excluidos original %d\n", G->numExcluidos);

        int corOriginal = G->adj[G->raiz][G->V];
        int corOtima = 0;
        int biggestExcluidos = 0;
        for(int i=1; i<numColor+1; i++){
            if(i==corOriginal) continue;
            ApontaMudanca mudanca = criaMudanca();
            pintaVertice(G, G->raiz, i, mudanca);
            // printf("cor %d excluidos %d\n", i, G->numExcluidos);
            if(G->numExcluidos>biggestExcluidos){
                biggestExcluidos=G->numExcluidos;
                corOtima = i;
            }
            despinta(G, mudanca);
        }
        // printf("corotima %d maior excluidos %d\n",corOtima, biggestExcluidos);
        pintaVertice(G, G->raiz, corOtima, aux);
        adicionaCor(lista, corOtima);
        // printf("%d ", corOtima);
        numPint++;
    }
    printf("%d\n", numPint);
    imprimeCores(lista);


    // printf("raiz eh %d\n", G->raiz);
    // printf("raiz eh %d\n", G->raiz);





    return 0;
}