#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#include "painting.h"

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