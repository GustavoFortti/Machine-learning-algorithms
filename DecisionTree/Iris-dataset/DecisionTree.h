#ifndef _DECISIONTREE_
#define _DECISIONTREE_ 

typedef struct nodo Nodo;
typedef struct features Features;

void input(Nodo No[], int size);
void CalcFeatures(Nodo No[], int size, double mean[]);
void Mean(Nodo No[], int size, double mean[]);

#endif