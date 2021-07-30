#include<stdio.h>
#include<stdlib.h>

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A estrutura graph representa um grafo. O campo adj é um ponteiro para o vetor de listas de adjacência, o campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */

typedef struct graph *Graph;
typedef struct vertex *Vertex;
typedef struct node *link;


struct vertex{
    int numVertice;
    int cor;
    link primeiroVizinho;
};

struct graph {
   int V; 
   int A; 
   Vertex *vertices;//vetor de ponteiros para vértices 
};

/* Um Graph é um ponteiro para um graph. */


/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node. */

struct node { 
   Vertex w; 
   link next; 
};

Graph criaGrafo( int V) { 
   Graph G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->vertices = malloc( V * sizeof (Vertex));
   for (int i=0; i<V; i++) 
      G->vertices[i] = NULL;
   return G;
}

void criaVertice(int pos, int color, Graph G){
    Vertex newVertice = (Vertex) malloc(sizeof(Vertex));
    newVertice->cor = color;
    newVertice->primeiroVizinho = NULL;
    G->vertices[pos] = newVertice;

    newVertice->numVertice = pos;

}


void criaAresta(int pos1, int pos2, Graph G){
    if(pos1 >= G->V || pos2 >= G->V || pos1 < 0 || pos2 < 0)//posicao nao existe
        return;
    
    
    link vizinhoDo1 = (link) malloc(sizeof(link));
    vizinhoDo1->w = G->vertices[pos2];
    link vizinhoDo2 = (link) malloc(sizeof(link));
    vizinhoDo2->w = G->vertices[pos1];

    link aux = G->vertices[pos1]->primeiroVizinho;
    G->vertices[pos1]->primeiroVizinho = vizinhoDo1;
    vizinhoDo1->next = aux; 

    aux = G->vertices[pos2]->primeiroVizinho;
    G->vertices[pos2]->primeiroVizinho = vizinhoDo2;
    vizinhoDo2->next = aux;  

    G->A++;
}

void printGrafo(Graph G){
    for(int i=0; i<G->V; i++){
        printf("vertice %d de cor %d: ", i, G->vertices[i]->cor);
        if(G->vertices[i] == NULL)//temporario
            break;
        for(link aux = G->vertices[i]->primeiroVizinho; aux!=NULL; aux = aux->next)
            printf("vizinho %d, ", aux->w->numVertice);
    printf("\n");
    }
}

void copiaVizinhos(int origem, int destino, Graph G){
    link listaVizinhos = G->vertices[origem]->primeiroVizinho;
    if(listaVizinhos == NULL) return;//nada a copiar
    
    link aux = G->vertices[destino]->primeiroVizinho;
    while(aux->next != NULL) aux=aux->next;//pegando a ultima posição
    aux->next = listaVizinhos;
    // listaVizinhos->next = NULL;

}

int main(){
    // Graph G;
    // G = criaGrafo(4);
    // criaVertice(0, 2, G);
    // criaVertice(1, 3, G);
    // criaVertice(2, 4, G);
    // criaVertice(3, 5, G);
    // criaAresta(0, 1, G);
    // criaAresta(0, 2, G);
    // criaAresta(0, 3, G);
    // criaAresta(1, 2, G);

    int numL, numC, numColor;
    scanf("%d %d %d", &numL, &numC, &numColor);
    Graph G = criaGrafo(numL*numC);
    int matrix[numL][numC];
    for(int i=0; i<numL; i++)
        for(int j=0; j<numC; j++)
            scanf("%d", &matrix[i][j]);

    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++)
            criaVertice(i*numC + j, matrix[i][j], G);
    }

    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++){
            criaAresta(i*numC + j, i*numC + j + 1, G);//vizinho da direita
            criaAresta(i*numC + j, (i-1)*numC + j, G);//vizinho de cima
        }
    }

    for(int i=0; i<numL; i++){
        for(int j=0; j<numC; j++){
            if(i+1<numL && matrix[i][j] == matrix[i+1][j])//vizinho de cima
                copiaVizinhos((i+1)*numC + j,i*numC + j, G);
            if(j-1>=0 && matrix[i][j] == matrix[i][j-1])//vizinho da esquerda
                copiaVizinhos(i*numC + j - 1,i*numC + j, G);
        }
    }

    printGrafo(G);

    return 0;
}