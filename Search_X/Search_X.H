#ifndef _AG_
#define _AG_

#define size_pop       10
#define size_gen       10
#define generation     10000
#define tournament     100
#define prob_mutation  0.1
#define prob_cross     0.7
#define value          20   // x da expreção

typedef struct pop
{
    long double gen[size_gen];
}Pop;

Pop* startPop();
int getBest(Pop *p);
void viewerPop(Pop *p);
void conversion_StrctForVector(Pop *p, double v[], int i);
double getScore(double v[]);
double howClose(double neares);
void cross(Pop *p, int xy, int xx, double son[]);
void shuffle(int v[]);
void swap(int v[], int i, int j);
void mutation(double son[]);
void Dominant(Pop *p, double son[], int index);

#endif