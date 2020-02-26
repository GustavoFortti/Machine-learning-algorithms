#ifndef _SEARCH_X_H_
#define _SEARCH_X_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define size_pop       10
#define size_gen       10
#define generation     10000
#define tournament     1000
#define prob_mutation  1
#define prob_cross     0.7
#define value          20   // x da expreção

typedef struct pop
{
    long double gen[size_gen];
}Pop;

Pop* startPop();
void inserctionSort(double v[], int size, int index[]);
int selectionByRating(Pop *p, int index);
void cross(Pop *p, int xy, int xx, double son[]);
void shuffle(int v[]);
void swap(int v[], int i, int j);
void mutation(double son[]);
int getBest(Pop *p);
void conversion_StrctForVector(Pop *p, double v[], int i);
double getScore(double v[]);
double howClose(double neares);
void Dominant(Pop *p, double son[], int index);
void viewerPop(Pop *p);

#endif