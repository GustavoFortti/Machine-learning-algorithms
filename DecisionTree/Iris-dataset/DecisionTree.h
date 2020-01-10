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
void CalcFeatures(SubSet set[]);
void CalcMean(SubSet set[], double mean[size_vet][size_group]);
void CalcIG(SubSet set[], int i, int index);
void CrossValidation(SubSet set[], int i);
void SelectionSort(SubSet set[], double v[], int plant[], int features_chosen[], int size);
void swap(SubSet set[], double v[], int plant[], int features_chosen[], int i, int j);

#endif