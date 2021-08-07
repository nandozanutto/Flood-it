#include<stdlib.h>
#include<stdio.h>
#include"graph.h"
#include"painting.h"
#include"guloso.h"



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


int guloso(Graph G, int numColor, ApontaLista lista){
    int numPint = 0;
    // GRAPHshow(G);
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
    return numPint;

}