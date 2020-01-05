#ifndef _DECISIONTREE_
#define _DECISIONTREE_ 

typedef struct features Features;
typedef struct nodo Nodo;
typedef struct means Means;
typedef struct subset SubSet;
typedef struct InformationGain IG;

void input(SubSet set[], int size);
void CalcFeatures(SubSet set[], int size);
void CalcMean(SubSet set[], int size);
void CalcIG(SubSet set[], int size, int i);
void CalcEntropy(SubSet set[],int size, int i, int index);

#endif