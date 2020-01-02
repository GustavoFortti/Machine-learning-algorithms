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

    input(No_main, trein_size);

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

        GotClass = classificationClass(No_main, No_sub, k, trein_size, i);
        if ( strcmp(GotClass, No_sub->classe) == 0)
        {
            success++;
        }
        else
        {
            //printf("\n%s >> %s >> indice = %i", No_sub->classe, GotClass, i);
        }
        
    }
    printf("\nCorrect classes %i -> %i percent data \n", success, (success*100)/45);

    return 0;
}

char *classificationClass(Node No_main[], Node *No_sub, int k, int trein_size, int indice)
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

    SelectionSort(el, trein_size);
    if ( indice == 2 || indice == 4  )
    {
        printf("\n%i\n", indice);
        for ( i = 0; i < trein_size; i++)
        {
            printf("%Lf -> %i\n", el[i].dist, el[i].index);
        }
        printf("\n");
    }
    

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

void InserctionSort( Element v[], int size)
{
	long double escolhido = 0.0;
    int j, i;
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

void QuickSort(Element v[], int began, int end)
{
    int i, j;
    long double pivo, aux;

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

void SelectionSort( Element v[], int size)
{
	int i=0, j=0;
    for ( i = 0; i < size-1; i++){
        for ( j = i; j < size; j++){
            if ( v[i].dist > v[j].dist){
                swap( v, i, j);
            }
        }
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

void input( Node No[], int size)
{
    FILE *file;
    file = fopen("dataset.txt", "r");
    int i;
    if (file != NULL)
    {
        for ( i = 0; i < size; i++)
        {
            fscanf(file, "%Lf %Lf %Lf %Lf %s", &No[i].x, &No[i].y, &No[i].w, &No[i].z, No[i].classe);
            if (strcmp(No[i].classe, "Iris-setosa") == 0)No[i].index = 0;
            else if (strcmp(No[i].classe, "Iris-versicolor") == 0)No[i].index = 1;
            else if (strcmp(No[i].classe, "Iris-virginica") == 0)No[i].index = 2;
        }
        fclose(file);
    }
}