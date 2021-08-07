#ifndef __GULOSO_H__
#define __GULOSO_H__


typedef struct reg *ApontaLista;


struct reg { 
   int         cor; 
   ApontaLista prox;
};

ApontaLista criaLista();
void adicionaCor(ApontaLista lista, int cor);
void imprimeCores(ApontaLista lista);
int guloso(Graph G, int numColor, ApontaLista lista);



#endif