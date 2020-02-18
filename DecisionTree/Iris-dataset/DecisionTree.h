#ifndef _DECISIONTREE_
#define _DECISIONTREE_ 

#define size_pop     150
#define size_ind     30   
#define size_vet     4   
#define size_group   5    
#define size_plant   3    

typedef struct plants Plants;
typedef struct group Group;
typedef struct pop Pop;
typedef struct InformationGain IG;


void D3(Pop *p, int i);
void SelectionSort( double v[], int size, int index[]);
void swap(  double v[], int i, int j, int index[]);
void CalcIG(Pop *p, int plant, int group_block);
void CrossValidation(Pop *p, int group_block);
void CalcFeatures(Pop *p, int group_block);
void CalcMean(Pop *p, double mean[size_vet], int group_block, int index);
Pop* input();

#endif