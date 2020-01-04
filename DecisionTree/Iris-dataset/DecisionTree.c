#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "DecisionTree.h"

struct nodo
{
    double SepalLength;
    double SepalWidth;
    double PetalLength;
    double PetalWidth;
    char Class[50];
    int index;
    Features feature;
};

struct features
{
    double SepalArea;
    double PetalArea;
    bool SepalLengthAboveMean;
    bool SepalWidthAboveMean;
    bool PetalLengthAboveMean;
    bool PetalWidthAboveMean;
};

int main()
{
    const int data_size = 150;
    const int trein_size = 105;
    const int test_size = data_size - trein_size;
    Nodo No[trein_size];
    input(No, trein_size);

    // mean[0] = SepalLengthMean, mean[1] = SepalWidthMean, mean[2] = PetalLengthMean, mean[3] = PetalWidthMean
    double mean[4];

    /*
    criar area Sepal e Petal
    criar media sobre SepalLength SepalWidth PetalLength PetalWidth
    e encontra valores acima da media

    # Iris-setosa
    sample1 = [1.0, 2.0, 3.5, 1.0, 10.0, 3.5, False, False, False, False]
    # Iris-versicolor
    sample2 = [5.0, 3.5, 1.3, 0.2, 17.8, 0.2, False, True, False, False]
    # Iris-virginica
    sample3 = [7.9, 5.0, 2.0, 1.8, 19.7, 9.1, True, False, True, True]
    */
    Mean(No, trein_size, mean);

    CalcFeatures(No, trein_size, mean);

}

void CalcFeatures(Nodo No[], int size, double mean[])
{
    int i;
    for ( i = 0; i < size; i++)
    {
        No[i].feature.SepalArea = No[i].SepalLength * No[i].SepalWidth;
        No[i].feature.PetalArea = No[i].PetalLength * No[i].PetalWidth;
        if ( No[i].SepalLength > mean[0]) No[i].feature.SepalLengthAboveMean = true;
        else No[i].feature.SepalLengthAboveMean = false;
        if ( No[i].SepalWidth > mean[0]) No[i].feature.SepalWidthAboveMean = true;
        else No[i].feature.SepalWidthAboveMean = false;
        if ( No[i].PetalLength > mean[0]) No[i].feature.PetalLengthAboveMean = true;
        else No[i].feature.PetalLengthAboveMean = false;
        if ( No[i].PetalWidth > mean[0]) No[i].feature.PetalWidthAboveMean = true;
        else No[i].feature.PetalWidthAboveMean = false;
    }
}

void Mean(Nodo No[], int size, double mean[])
{
    int i;
    double sum[4];
    // [0]SepalLengthMean [1]SepalWidthMean [2]PetalLengthMean [3]PetalWidthMean
    for ( i = 0; i < size; i++)
    {
        sum[0] = sum[0] + No[i].SepalLength;
        sum[1] = sum[1] + No[i].SepalWidth;
        sum[2] = sum[2] + No[i].PetalLength;
        sum[3] = sum[3] + No[i].PetalWidth;
    }
    mean[0] = sum[0] / size;
    mean[1] = sum[1] / size;
    mean[2] = sum[2] / size;
    mean[3] = sum[3] / size;
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

