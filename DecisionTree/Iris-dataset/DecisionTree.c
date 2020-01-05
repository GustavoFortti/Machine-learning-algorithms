#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "DecisionTree.h"

//#define size_ind 6           // groups number -> 1 with 15 plants
//#define size_var 4             // numero de variaveis booleanas em features

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

// struct means
// {
//     double MeanSepalLength;
//     double MeanSepalWidth;
//     double MeanPetalLength;
//     double MeanPetalWidth;
// };

struct InformationGain
{
    double IG_MeanSepalLength;
    double IG_MeanSepalWidth;
    double IG_MeanPetalLength;
    double IG_MeanPetalWidth;
};

struct subset
{
    Nodo No[size_ind]; 
    InfoGain IG;
    //Means Mean;
};

int main(int argc, char const *argv[])
{
    //const int size_pop = 150;
    SubSet set[size_pop / size_ind];
    //Nodo No[size_pop];
    input(set);

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
    //CalcMean(set, size_pop);

    CalcFeatures(set);

    //calcular entropia
    
    int i = 24, index = 0;
    CalcIG(set, i, index);

}

void CalcIG(SubSet set[], int i, int index)
{
    //CalcEntropy(set, size_pop, i, index);

    ///////////////////////////////////////////////////////// ENTROPY /////////////////////////////////////////////////////////
    int j;
    //EntropyFhater
    int Yf = 0, Nf = 0;
    
    for ( j = 0; j < size_ind; j++)
    {
        if (set[i].No[j].index == index) Yf++;
    }
    Nf = size_ind - Yf;

    double PYF, PNF, EntropyF;
    PYF = Yf / (size_ind * 1.0);
    PNF = Nf / (size_ind * 1.0);
    EntropyF = - ( PYF * log2(PYF) + PNF * log2(PNF));
    //printf("%lf\n", EntropyF);

    // EntropySon Left
    int y[size_var] = {0}, n[size_var] = {0};

    for ( j = 0; j < size_ind; j++)
    {
        if ( set[i].No[j].index == index && set[i].No[j].feature.SepalLengthAboveMean == true) y[0]++;
        if ( set[i].No[j].index == index && set[i].No[j].feature.SepalWidthAboveMean  == true) y[1]++;
        if ( set[i].No[j].index == index && set[i].No[j].feature.PetalLengthAboveMean == true) y[2]++;
        if ( set[i].No[j].index == index && set[i].No[j].feature.PetalWidthAboveMean  == true) y[3]++;
    }
    for ( j = -1; j < size_var; j++, n[j] = Yf - y[j]);

    double entropyLeft[size_var] = {0};
    double PyLeft[size_var] = {0};
    double PnLeft[size_var] = {0};
    
    for ( j = 0; j < size_var; j++)
    {
        PyLeft[j] = y[j] / (size_ind * 1.0);
        PnLeft[j] = n[j] / (size_ind * 1.0);
        entropyLeft[j] = - ( PyLeft[j] * log2(PyLeft[j]) + PnLeft[j] * log2(PnLeft[j]));
        if (PyLeft[j] == 0 || PnLeft[j] == 0) entropyLeft[j] = 0;
        y[j] = 0;
        n[j] = 0;
        //printf("%lf\n", entropyLeft[j]);
    }

    // EntropySon Right

    for ( j = 0; j < size_ind; j++)
    {
        if ( set[i].No[j].index != index && set[i].No[j].feature.SepalLengthAboveMean == true) y[0]++;
        if ( set[i].No[j].index != index && set[i].No[j].feature.SepalWidthAboveMean  == true) y[1]++;
        if ( set[i].No[j].index != index && set[i].No[j].feature.PetalLengthAboveMean == true) y[2]++;
        if ( set[i].No[j].index != index && set[i].No[j].feature.PetalWidthAboveMean  == true) y[3]++;
    }
    for ( j = -1; j < size_var; j++, n[j] = Nf - y[j]);
    
    double entropyRight[size_var] = {0};
    double PyRight[size_var] = {0};
    double PnRight[size_var] = {0};
    
    for ( j = 0; j < size_var; j++)
    {
        PyRight[j] = y[j] / (size_ind * 1.0);
        PnRight[j] = n[j] / (size_ind * 1.0);
        entropyRight[j] = - ( PyRight[j] * log2(PyRight[j]) + PnRight[j] * log2(PnRight[j]));
        if (PyRight[j] == 0 || PnRight[j] == 0) entropyRight[j] = 0;
        //printf("%lf\n", entropyRight[j]);
    }

    ///////////////////////////////////////////////////////// Weight /////////////////////////////////////////////////////////

    
}

void CalcEntropy(SubSet set[], int i, int index)
{

}

void CalcFeatures(SubSet set[])
{

    double mean[size_var][25];
    CalcMean(set, mean);
    int i, j;
    for ( i = 0; i < size_pop / size_ind; i++)
    {
        for ( j = 0; j < size_ind; j++)
        {
            set[i].No[j].feature.SepalArea = set[i].No[j].SepalLength * set[i].No[j].SepalWidth;
            set[i].No[j].feature.PetalArea = set[i].No[j].PetalLength * set[i].No[j].PetalWidth;
            //if ( set[i].No[j].SepalLength > set[i].Mean.MeanSepalLength) set[i].No[j].feature.SepalLengthAboveMean = true;
            if ( set[i].No[j].SepalLength > mean[0][i]) set[i].No[j].feature.SepalLengthAboveMean = true;
            else set[i].No[j].feature.SepalLengthAboveMean = false;
            //if ( set[i].No[j].SepalWidth > set[i].Mean.MeanSepalWidth) set[i].No[j].feature.SepalWidthAboveMean = true;
            if ( set[i].No[j].SepalWidth > mean[1][i]) set[i].No[j].feature.SepalWidthAboveMean = true;
            else set[i].No[j].feature.SepalWidthAboveMean = false;
            //if ( set[i].No[j].PetalLength > set[i].Mean.MeanPetalLength) set[i].No[j].feature.PetalLengthAboveMean = true;
            if ( set[i].No[j].PetalLength > mean[2][i]) set[i].No[j].feature.PetalLengthAboveMean = true;
            else set[i].No[j].feature.PetalLengthAboveMean = false;
            //if ( set[i].No[j].PetalWidth > set[i].Mean.MeanPetalWidth) set[i].No[j].feature.PetalWidthAboveMean = true;
            if ( set[i].No[j].PetalWidth > mean[3][i]) set[i].No[j].feature.PetalWidthAboveMean = true;
            else set[i].No[j].feature.PetalWidthAboveMean = false;
            printf("group => %i \t- %0.2lf | %0.2lf | %0.2lf | %0.2lf | %s\t => %i | %0.2lf | %0.2lf\t|\t %d %d %d %d\n", i+1,set[i].No[j].SepalLength, set[i].No[j].SepalWidth, set[i].No[j].PetalLength, set[i].No[j].PetalWidth, set[i].No[j].Class, set[i].No[j].index, set[i].No[j].feature.SepalArea,  set[i].No[j].feature.PetalArea, set[i].No[j].feature.SepalLengthAboveMean, set[i].No[j].feature.SepalWidthAboveMean, set[i].No[j].feature.PetalLengthAboveMean, set[i].No[j].feature.PetalWidthAboveMean );
        }
    }
}

void CalcMean(SubSet set[], double mean[size_var][size_group])
{
    int i, j;
    double sum[size_var];
    // [0]SepalLengthMean [1]SepalWidthMean [2]PetalLengthMean [3]PetalWidthMean
    for ( i = 0; i < size_pop / size_ind; i++)
    {
        for ( j = 0; j < size_ind; j++)
        {
            sum[0] = sum[0] + set[i].No[j].SepalLength;
            sum[1] = sum[1] + set[i].No[j].SepalWidth;
            sum[2] = sum[2] + set[i].No[j].PetalLength;
            sum[3] = sum[3] + set[i].No[j].PetalWidth;
            //printf("%lf %lf %lf %lf\n", set[i].No[j].SepalLength, set[i].No[j].SepalWidth, set[i].No[j].PetalLength, set[i].No[j].PetalWidth);
        }
        // set[i].Mean.MeanSepalLength = sum[0] / size_ind;
        // set[i].Mean.MeanSepalWidth = sum[1] / size_ind;
        // set[i].Mean.MeanPetalLength = sum[2] / size_ind;
        // set[i].Mean.MeanPetalWidth = sum[3] / size_ind;
        mean[0][i] = sum[0] / size_ind;
        mean[1][i] = sum[1] / size_ind;
        mean[2][i] = sum[2] / size_ind;
        mean[3][i] = sum[3] / size_ind;

        for ( j = -1; j < size_var; j++, sum[j] = 0);
        //printf("%lf %lf %lf %lf\n", set[i].Mean.MeanSepalLength , set[i].Mean.MeanSepalWidth , set[i].Mean.MeanPetalLength , set[i].Mean.MeanPetalWidth );
        //printf("%lf %lf %lf %lf\n", mean[0][i] , mean[1][i] , mean[2][i] , mean[3][i] );
    }
}

void input(SubSet set[])
{
    FILE *file;
    file = fopen("Iris-dataset.txt", "r");
    int i, j;
    if (file != NULL)
    {
        for ( i = 0; i < size_pop / size_ind; i++)
        {
            for ( j = 0; j < size_ind; j++)
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
