#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "painting.h"
#include "guloso.h"



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

    ApontaLista lista = criaLista();
    int numPint = guloso(G, numColor, lista);
    printf("%d\n", numPint);
    imprimeCores(lista);


    return 0;
}