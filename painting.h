#ifndef __PAINTING_H__
#define __PAINTING_H__
#include "graph.h"

typedef struct mudanca *ApontaMudanca;
typedef struct nodo *ApontaNodo;

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

ApontaMudanca criaMudanca();
void adicionaMudanca(ApontaMudanca mudanca, int * mudou);
void copiaVizinhos(int o, int d, Graph G);
void copiaVizinhos2(int o, int d, Graph G, ApontaMudanca mudanca);
void pintaVertice(Graph G, int v, int cor, ApontaMudanca mudanca);
void despinta(Graph G, ApontaMudanca mudanca);


#endif