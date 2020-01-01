#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "knn.h"

#define T_size 150

/*
    No principal, caracteristicas das plantas que serao analisadas pelo algoritimo, 
    tambem foi adcionado uma variavel index para guardar numeros de 0 a 2 onde:
    0 = Iris-setosa
    1 = Iris-versicolor
    2 = Iris-virginica

    As 4 variaveis double de x a z indicam que o plano esta na 4 dimenção, porem
    o calculo de distancia euclidiana se mantem o mesmo.
*/

struct node
{
    double x;
    double y;
    double w;
    double z;
    char classe;
    int index;
};

    /*
        struct element: estrutura criada com a intenção de facilitar a ordenação do
        vetor de classes das plantas.
        Foi escolhido o metodo de ordenção para caso o numero de vizinhos aumentasse,
        ai nao haveria uma grande modificação no algoritimo.
    */

struct element{
    int index;
    double dist;
};

int main(int argc, char const *argv[])
{
    const int data_size = 150;
    const int trein_size = 105;
    const int test_size = data_size - trein_size;
    const int k = 3; 
    char classe_aux[100];
    int i;
    Node No_main[trein_size];

    /*
        entada de dados para treinamento, serao treinados com 105 classes diferentes de plantas.
    */

    for ( i = 0; i < trein_size; i++)
    {
        scanf("%lf %lf %lf %lf %s", &No_main[i].x, &No_main[i].y, &No_main[i].w, &No_main[i].z, &No_main[i].classe);
        if (strcmp(classe_aux, "Iris-setosa") != 0)No_main[i].index = 0;
        else if (strcmp(classe_aux, "Iris-versicolor") != 0)No_main[i].index = 1;
        else if (strcmp(classe_aux, "Iris-virginica") != 0)No_main[i].index = 2;
    }
    printf("aqui\n");
    Node *No_sub;
    //*No_sub = (Node) malloc( test_size * sizeof())
    int success = 0;
    char *GotClass;
    char *classification;

    for ( i = 0; i < test_size; i++)
    {
        scanf("%lf %lf %lf %lf %s", &No_sub->x, &No_sub->y, &No_sub->w, &No_sub->z, No_sub->classe);
        printf("aqui\n");
        GotClass = classificationClass(No_main, No_sub, k, trein_size);
        classification = &No_sub->classe;

        if ( GotClass == classification)
        {
            success++;
        }
    }
    printf("%i\n", success);

    return 0;
}

char *classificationClass(Node No_main[], Node *No_sub, int k, int trein_size)
{

    /*
        Neste algoritimo foi evitado usar o numero de vizinho par, utilizando 
        numeros impares para nao haver impate.
    */

    if ( k % 2 == 0)
    {
        k--;
        if ( k <= 0)
        {
            k = 1;
        }
    }

    int i;
    char *classe_aux;

    Element el[trein_size];

    for ( i = 0; i < trein_size; i++)
    {
        el[i].dist = EuclideanDistance(No_main, No_sub, i);
        el[i].index = No_main[i].index;
    }

    /*
        Função QuickSort modificada, implementada com a intenção de maximizar o tempo de trocas
        Vantage: ao implementala o tempo seria consequencia de uma massa de dados de 150 
        ( total de dados), 105 ( dados de treinamento) e 45 ( dados de teste), ao multiplicalos
        seriam 4725 e ainda sim o Inserction sorte daria conta porem nao so sera trocado o elemento 
        principal da função com seu index tambem, ou seja o dobro de elementos...
    */

    QuickSort(el, 0, trein_size);
    //InserctionSort(el, trein_size);
    
    int cont_setosa = 0;
    int cont_versicolor = 0;
    int cont_virginica = 0;

    for ( i = 0; i < k; i++)
    {
        if (No_main[i].index == 0) cont_setosa++;
        else if (No_main[i].index == 1) cont_versicolor++;
        else if (No_main[i].index == 2) cont_virginica++;
    }

    cont_setosa > cont_versicolor && cont_setosa > cont_virginica ? strcpy(classe_aux,"Iris-setosa") :
    cont_setosa > cont_versicolor && cont_setosa > cont_virginica ? strcpy(classe_aux,"Iris-setosa") : strcpy(classe_aux,"Iris-setosa");

    return classe_aux;
}

double EuclideanDistance( Node main[], Node *sub, int i)
{
    double dist = pow(main[i].x - sub->x, 2) + pow(main[i].y - sub->y, 2) + pow(main[i].w - sub->w, 2) + pow(main[i].z - sub->z, 2);
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
    double aux_v = v[i].dist;
    v[i].dist = v[j].dist;
    v[j].dist = aux_v;

    int aux_index = v[i].index;
    v[i].index = v[j].index;
    v[j].index = aux_index;
}

// void InserctionSort( Element v[], int size){
// 	long escolhido = 0, j, i;
//     for ( i = 1; i < size; i++){
//         escolhido = v[i].dist;
//         escolhido = v[i].index;
//         j = i - 1;
//         while ((j >= 0) && ( v[j].dist > escolhido)){
//             v[j + 1].dist = v[j].dist;
//             v[j + 1].index = v[j].index;
//             j--;
//         }
//         v[j + 1].dist = escolhido;
//         v[j + 1].index = escolhido;
//     }
// }