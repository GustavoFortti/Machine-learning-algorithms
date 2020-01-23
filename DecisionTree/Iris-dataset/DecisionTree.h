#ifndef _DECISIONTREE_
#define _DECISIONTREE_ 

#define size_pop     150
#define size_ind     6
#define size_vet     4
#define size_group   25
#define size_plant   3

typedef struct features Features;
typedef struct nodo Nodo;
typedef struct subset SubSet;
typedef struct InformationGain InfoGain;

void input(SubSet set[]);
void CalcFeatures(SubSet set[], int i, int index);
void CalcMean(SubSet set[], double mean[size_vet], int i, int index);
void CalcIG(SubSet set[], int i, int index, int block_index);
void CrossValidation(SubSet set[], int i, int index);

#endif