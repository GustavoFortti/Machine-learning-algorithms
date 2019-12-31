#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define T_size 150

typedef struct node
{
    double x;
    double y;
    double w;
    double z;
    char classe;
    int index;
}Node;

typedef struct element{
    int index;
    double dist;
}Element;

int main(int argc, char const *argv[])
{
    const int data_size = 150;
    const int trein_size = 105;
    const int test_size = data_size - trein_size;
    const int k = 3; 
    char classe;
    int i;
    Node No_main[trein_size];

    for ( i = 0; i < trein_size; i++)
    {
        scanf("%lf %lf %lf %lf %s", &No_main[i].x, &No_main[i].y, &No_main[i].w, &No_main[i].z, &No_main[i].classe);
        if (strcmp(classe, "Iris-setosa") != 0)No_main[i].index = 0;
        else if (strcmp(classe, "Iris-versicolor") != 0)No_main[i].index = 1;
        else if (strcmp(classe, "Iris-virginica") != 0)No_main[i].index = 2;
    }

    Node No_sub;

    for ( i = 0; i < test_size; i++)
    {
        scanf("%lf %lf %lf %lf %s", &No_sub.x, &No_sub.y, &No_sub.w, &No_sub.z, &No_sub.classe);
        char GotClass = classificationClass(No_main, No_sub, k, trein_size);
    }

    return 0;
}

char classificationClass(Node No_main[], Node No_sub, int k, int trein_size)
{
    if ( k % 2 == 0)
    {
        k--;
        if ( k <= 0)
        {
            k = 1;
        }
    }

    int i;
    char classe[100];

    Element el[trein_size];

    for ( i = 0; i < trein_size; i++)
    {
        el[i].dist = EuclideanDistance(No_main, No_sub, i);
        el[i].index = No_main[i].index;
    }

    InserctionSort(el, trein_size);
    
    int cont_setosa = 0;
    int cont_versicolor = 0;
    int cont_virginica = 0;

    for ( i = 0; i < k; i++)
    {
        if (No_main[i].index == 0) cont_setosa++;
        else if (No_main[i].index == 1) cont_versicolor++;
        else if (No_main[i].index == 2) cont_virginica++;
    }

    cont_setosa > cont_versicolor && cont_setosa > cont_virginica ? strcpy(classe,"Iris-setosa") :
    cont_setosa > cont_versicolor && cont_setosa > cont_virginica ? strcpy(classe,"Iris-setosa") : strcpy(classe,"Iris-setosa");

    return classe;
}

double EuclideanDistance( Node main[], Node sub, int i)
{
    double dist = pow(main[i].x - sub.x, 2) + pow(main[i].x - sub.x, 2) + pow(main[i].x - sub.x, 2) + pow(main[i].x - sub.x, 2);
    return sqrt(dist);
}

void InserctionSort( Element v[], int size){
	long escolhido = 0, j, i;
    for ( i = 1; i < size; i++){
        escolhido = v[i].dist;
        escolhido = v[i].index;
        j = i - 1;
        while ((j >= 0) && ( v[j].dist > escolhido)){
            v[j + 1].dist = v[j].dist;
            v[j + 1].index = v[j].index;
            j--;
        }
        v[j + 1].dist = escolhido;
        v[j + 1].index = escolhido;
    }
}