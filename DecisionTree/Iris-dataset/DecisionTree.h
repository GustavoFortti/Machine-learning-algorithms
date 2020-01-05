#ifndef _DECISIONTREE_
#define _DECISIONTREE_ 

#define size_pop     150
#define size_ind     6
#define size_var     4
#define size_group   25

typedef struct features Features;
typedef struct nodo Nodo;
typedef struct subset SubSet;
typedef struct InformationGain InfoGain;

void input(SubSet set[]);
void CalcFeatures(SubSet set[]);
void CalcMean(SubSet set[], double mean[size_var][size_group]);
void CalcIG(SubSet set[], int i, int index);

#endif