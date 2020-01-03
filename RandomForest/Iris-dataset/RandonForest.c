#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "RandonForest.h"

struct nodo
{
    double SepalLength;
    double SepalWidth;
    double PetalLength;
    double PetalWidth;
    char Class[50];
    double SepalArea;
    double PetalArea;
    bool SepalLengthAboveMean;
    bool SepalWidthAboveMean;
    bool PetalLengthAboveMean;
    bool PetalLengthAboveMean;
    int index;
};

int main()
{
    const int data_size = 150;
    const int trein_size = 105;
    const int test_size = data_size - trein_size;

    Nodo No[trein_size];
    input(No, trein_size);

    // criar area Sepal e Petal
    // criar media sobre SepalLength SepalWidth PetalLength PetalWidth
    // e encontra valores acima da media

    /*
    # Iris-setosa
    sample1 = [1.0, 2.0, 3.5, 1.0, 10.0, 3.5, False, False, False, False]
    # Iris-versicolor
    sample2 = [5.0, 3.5, 1.3, 0.2, 17.8, 0.2, False, True, False, False]
    # Iris-virginica
    sample3 = [7.9, 5.0, 2.0, 1.8, 19.7, 9.1, True, False, True, True]
    */

    features(No, trein_size);
    
}

void features(Nodo No[], int size)
{

}

void input(Nodo No[], int size)
{
    FILE *file;
    file = fopen("Iris-dataset.txt", "r");
    int i;
    if (file != NULL)
    {
        for ( i = 0; i < size; i++)
        {
            fscanf(file, "%lf %lf %lf %lf %s", &No[i].SepalLength, &No[i].SepalWidth, &No[i].PetalLength, &No[i].PetalWidth, No[i].Class);
            if (strcmp(No[i].Class, "Iris-setosa") == 0)No[i].index = 0;
            else if (strcmp(No[i].Class, "Iris-versicolor") == 0)No[i].index = 1;
            else if (strcmp(No[i].Class, "Iris-virginica") == 0)No[i].index = 2;
        }
        fclose(file);
    }
}

