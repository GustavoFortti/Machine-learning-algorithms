#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "DecisionTree.h"

#define size_group 6           // groups number -> 1 with 15 plants
#define size_var 4             // numero de variaveis booleanas em features

struct features
{
    double SepalArea;
    double PetalArea;
    bool SepalLengthAboveMean;
    bool SepalWidthAboveMean;
    bool PetalLengthAboveMean;
    bool PetalWidthAboveMean;
};

struct nodo
{
    double SepalLength;
    double SepalWidth;
    double PetalLength;
    double PetalWidth;
    char Class[50];
    int index;                  // index 0 = Iris-setosa 1 = Iris-versicolor 2 = Iris-virginica
    Features feature;
};

struct means
{
    double MeanSepalLength;
    double MeanSepalWidth;
    double MeanPetalLength;
    double MeanPetalWidth;
};

struct InformationGain
{
    double IG_MeanSepalLength;
    double IG_MeanSepalWidth;
    double IG_MeanPetalLength;
    double IG_MeanPetalWidth;
};

struct subset
{
    Nodo No[size_group]; 
    Means Mean;
};

int main()
{
    const int data_size = 150;
    const int trein_size = 105;
    const int test_size = data_size - trein_size;
    SubSet set[data_size / size_group];
    //Nodo No[data_size];
    input(set, data_size);

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
    CalcMean(set, data_size);

    CalcFeatures(set, data_size);

    //calcular entropia
    

}

void CalcGI(SubSet set[], int size, int i)
{
    CalcEntropy(set, size, i);
}

void CalcEntropy(SubSet set[],int size, int i)
{
    int j;
    int y[size_var], n[size_var];

    for ( j = 0; j < size / size_group; j++)
    {
        y[0] = set[i].No[j].feature.SepalLengthAboveMean;
        y[1] = set[i].No[j].feature.SepalWidthAboveMean;
        y[2] = set[i].No[j].feature.PetalLengthAboveMean;
        y[3] = set[i].No[j].feature.PetalWidthAboveMean;
    }
    for ( j = -1; j < size_var; j++, n[i] = size_group - y[i]);
    
    double entropy[size_var];
    double Py[size_var];
    double Pn[size_var];

    for ( j = 0; j < size_var; j++)
    {
        Py[j] = y[j] / (size_group * 1.0);
        Pn[j] = n[j] / (size_group * 1.0);
        entropy[j] = - ( Py[j] * log2(Py[j]) + Pn[j] * log2(Pn[j]));
    }

}

void CalcFeatures(SubSet set[], int size)
{
    int i, j;
    for ( i = 0; i < size / size_group; i++)
    {
        for ( j = 0; j < size_group; j++)
        {
            set[i].No[j].feature.SepalArea = set[i].No[j].SepalLength * set[i].No[j].SepalWidth;
            set[i].No[j].feature.PetalArea = set[i].No[j].PetalLength * set[i].No[j].PetalWidth;
            if ( set[i].No[j].SepalLength > set[i].Mean.MeanSepalLength) set[i].No[j].feature.SepalLengthAboveMean = true;
            else set[i].No[j].feature.SepalLengthAboveMean = false;
            if ( set[i].No[j].SepalWidth > set[i].Mean.MeanSepalWidth) set[i].No[j].feature.SepalWidthAboveMean = true;
            else set[i].No[j].feature.SepalWidthAboveMean = false;
            if ( set[i].No[j].PetalLength > set[i].Mean.MeanPetalLength) set[i].No[j].feature.PetalLengthAboveMean = true;
            else set[i].No[j].feature.PetalLengthAboveMean = false;
            if ( set[i].No[j].PetalWidth > set[i].Mean.MeanPetalWidth) set[i].No[j].feature.PetalWidthAboveMean = true;
            else set[i].No[j].feature.PetalWidthAboveMean = false;
            printf("group => %i \t- %0.2lf | %0.2lf | %0.2lf | %0.2lf | %s\t => %i | %0.2lf | %0.2lf\t|\t %d %d %d %d\n", i+1,set[i].No[j].SepalLength, set[i].No[j].SepalWidth, set[i].No[j].PetalLength, set[i].No[j].PetalWidth, set[i].No[j].Class, set[i].No[j].index, set[i].No[j].feature.SepalArea,  set[i].No[j].feature.PetalArea, set[i].No[j].feature.SepalLengthAboveMean, set[i].No[j].feature.SepalWidthAboveMean, set[i].No[j].feature.PetalLengthAboveMean, set[i].No[j].feature.PetalWidthAboveMean );
            //else printf("group-=>-%i-\t--%0.2lf-|-%0.2lf-|-%0.2lf-|-%0.2lf-|-%s\t-=>-%i-|-%0.2lf-|-%0.2lf\t|\t-%d-%d-%d-%d\n", i+1,set[i].No[j].SepalLength, set[i].No[j].SepalWidth, set[i].No[j].PetalLength, set[i].No[j].PetalWidth, set[i].No[j].Class, set[i].No[j].index, set[i].No[j].feature.SepalArea,  set[i].No[j].feature.PetalArea, set[i].No[j].feature.SepalLengthAboveMean, set[i].No[j].feature.SepalWidthAboveMean, set[i].No[j].feature.PetalLengthAboveMean, set[i].No[j].feature.PetalWidthAboveMean );
        }
    }
}

void CalcMean(SubSet set[], int size)
{
    int i, j;
    double sum[size_var];
    // [0]SepalLengthMean [1]SepalWidthMean [2]PetalLengthMean [3]PetalWidthMean
    for ( i = 0; i < size / size_group; i++)
    {
        for ( j = 0; j < size_group; j++)
        {
            sum[0] = sum[0] + set[i].No[j].SepalLength;
            sum[1] = sum[1] + set[i].No[j].SepalWidth;
            sum[2] = sum[2] + set[i].No[j].PetalLength;
            sum[3] = sum[3] + set[i].No[j].PetalWidth;
            //printf("%lf %lf %lf %lf\n", set[i].No[j].SepalLength, set[i].No[j].SepalWidth, set[i].No[j].PetalLength, set[i].No[j].PetalWidth);
        }
        set[i].Mean.MeanSepalLength = sum[0] / size_group;
        set[i].Mean.MeanSepalWidth = sum[1] / size_group;
        set[i].Mean.MeanPetalLength = sum[2] / size_group;
        set[i].Mean.MeanPetalWidth = sum[3] / size_group;
        for ( j = -1; j < size_var; j++, sum[j] = 0);
        //printf("%lf %lf %lf %lf\n", set[i].Mean.MeanSepalLength , set[i].Mean.MeanSepalWidth , set[i].Mean.MeanPetalLength , set[i].Mean.MeanPetalWidth );
    }
}

void input(SubSet set[], int size)
{
    FILE *file;
    file = fopen("Iris-dataset.txt", "r");
    int i, j;
    if (file != NULL)
    {
        for ( i = 0; i < size / size_group; i++)
        {
            for ( j = 0; j < size_group; j++)
            {
                fscanf(file, "%lf %lf %lf %lf %s", &set[i].No[j].SepalLength, &set[i].No[j].SepalWidth, &set[i].No[j].PetalLength, &set[i].No[j].PetalWidth, set[i].No[j].Class);
                if (strcmp(set[i].No[j].Class, "Iris-setosa") == 0)set[i].No[j].index = 0;
                else if (strcmp(set[i].No[j].Class, "Iris-versicolor") == 0)set[i].No[j].index = 1;
                else if (strcmp(set[i].No[j].Class, "Iris-virginica") == 0)set[i].No[j].index = 2;
                //printf("%lf %lf %lf %lf %s\n", set[i].No[j].SepalLength , set[i].No[j].SepalWidth , set[i].No[j].PetalLength , set[i].No[j].PetalWidth , set[i].No[j].Class);
            }
        }
        fclose(file);
    }
}
