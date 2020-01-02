#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "knn.h"

#define T_size 150

struct node
{
    long double x;
    long double y;
    long double w;
    long double z;
    char classe[100];
    int index;
};

struct element{
    int index;
    long double dist;
};

int main(int argc, char const *argv[])
{
    const int data_size = 150;
    const int trein_size = 105;
    const int test_size = data_size - trein_size;
    const int k = 3; 
    int i;
    Node No_main[trein_size];


    for ( i = 0; i < trein_size; i++)
    {
        scanf("%Lf %Lf %Lf %Lf %s", &No_main[i].x, &No_main[i].y, &No_main[i].w, &No_main[i].z, No_main[i].classe);
        if (strcmp(No_main[i].classe, "Iris-setosa") == 0)No_main[i].index = 0;
        else if (strcmp(No_main[i].classe, "Iris-versicolor") == 0)No_main[i].index = 1;
        else if (strcmp(No_main[i].classe, "Iris-virginica") == 0)No_main[i].index = 2;
    }
    Node *No_sub, No_aux;
    No_sub = &No_aux;
    int success = 0;
    char *GotClass;
    char *classification;

    for ( i = 0; i < test_size; i++)
    {
        scanf("%Lf %Lf %Lf %Lf %s", &No_sub->x, &No_sub->y, &No_sub->w, &No_sub->z, No_sub->classe);
        if (strcmp(No_sub->classe, "Iris-setosa") == 0)No_sub->index = 0;
        else if (strcmp(No_sub->classe, "Iris-versicolor") == 0)No_sub->index = 1;
        else if (strcmp(No_sub->classe, "Iris-virginica") == 0)No_sub->index = 2;

        GotClass = classificationClass(No_main, No_sub, k, trein_size);
        if ( strcmp(GotClass, No_sub->classe) == 0)
        {
            success++;
        }
        else
        {
            //printf("\n%s >>> %s", No_sub->classe, GotClass);
        }
        
    }
    printf("\nCorrect classes %i -> %i percent data \n", success, (success*100)/45);

    return 0;
}

char *classificationClass(Node No_main[], Node *No_sub, int k, int trein_size)
{
    if ( k % 2 == 0)
    {
        k--;
        if ( k <= 0)
        {
            k = 1;
        }
    }
    k = 3;
    int i = 0;
    char *classe_aux, classe_main[16];
    classe_aux = classe_main;

    Element el[trein_size];

    for ( i = 0; i < trein_size; i++)
    {
        el[i].dist = EuclideanDistance(No_main, No_sub, i);
        el[i].index = No_main[i].index;
    }

    QuickSort(el, 0, trein_size);

    int cont_setosa = 0;
    int cont_versicolor = 0;
    int cont_virginica = 0;

    for (i = 0; i < k; i++)
    {
        if (el[i].index == 0)
        {
            cont_setosa++;
        }
        else
        {
            if (el[i].index == 1)
            {
                cont_versicolor++;
            }
            else
            {
                if ( el[i].index == 2)
                {
                    cont_virginica++;
                }
            }
        }
    }

    if ( cont_setosa > cont_versicolor && cont_setosa > cont_virginica)
    {
        strcpy(classe_aux, "Iris-setosa");
    }
    else
    {
        if ( cont_versicolor > cont_setosa && cont_versicolor > cont_virginica)
        {
            strcpy(classe_aux, "Iris-versicolor");
        }
        else
        {
            strcpy(classe_aux,"Iris-virginica");
        }
    } 

    return classe_aux;
}

long double EuclideanDistance( Node main[], Node *sub, int i)
{
    long double dist = pow(main[i].x - sub->x, 2) + pow(main[i].y - sub->y, 2) + pow(main[i].w - sub->w, 2) + pow(main[i].z - sub->z, 2);
    return sqrt(dist);
}

void QuickSort(Element v[], int began, int end)
{
    long i, j, pivo, aux;

    i = began;
    j = end - 1;
    pivo = v[(began + end) / 2].dist;

    for (;i <= j;){
	    for (;v[i].dist < pivo && i < end; ){
	        i++;
	    }
	    for (;v[j].dist > pivo && j > began; ){
	        j--;
	    }
	    if (i <= j){
	        swap( v, i ,j);
	        i++;
	        j--;
	    }
    }
    if (j > began){
        QuickSort(v, began, j + 1);
    }
    if (i < end){
        QuickSort(v, i, end);
    }
}

void swap( Element v[], int i, int j)
{
    long double aux_v = v[i].dist;
    v[i].dist = v[j].dist;
    v[j].dist = aux_v;

    int aux_index = v[i].index;
    v[i].index = v[j].index;
    v[j].index = aux_index;
}

// void input( Node No[], int size)
// {
//     FILE *file;
//     int i;
//     if (file = fopen("dataset.txt", "r") != NULL)
//     {
//         for ( i = 0; i < size; i++)
//         {
//             fscanf(file, "%Lf %Lf %Lf %Lf %s", &No[i].x, &No[i].y, &No[i].w, &No[i].z, No[i].classe);
//             if (strcmp(No[i].classe, "Iris-setosa") == 0)No[i].index = 0;
//             else if (strcmp(No[i].classe, "Iris-versicolor") == 0)No[i].index = 1;
//             else if (strcmp(No[i].classe, "Iris-virginica") == 0)No[i].index = 2;
//         }
//         fclose(file);
//     }
// }