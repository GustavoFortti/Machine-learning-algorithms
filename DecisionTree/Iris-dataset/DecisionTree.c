#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "DecisionTree.h"

struct features
{
    double SepalArea;
    double PetalArea;
    bool F_vet[size_vet];           //[0]SepalLength [1]SepalWidth [2]PetalLength [3]PetalWidth
};

struct InformationGain
{
    double IG_vet[size_vet];
};

struct nodo
{
    double SepalAndPetal[size_vet]; //[0]SepalLength [1]SepalWidth [2]PetalLength [3]PetalWidth
    char Class[50];
    int index;                      //index 0 = Iris-setosa 1 = Iris-versicolor 2 = Iris-virginica
    Features feature;
};

struct subset
{
    Nodo No[size_ind]; 
    InfoGain IG[size_plant];        //size_plante => setosa [0], versicolor [1], virginica [2]
    bool IG_bool[size_plant];
};

int main(int argc, char const *argv[])
{
    SubSet set[size_pop / size_ind];

    input(set);

    /*
        # Iris-setosa
        sample1 = [1.0, 2.0, 3.5, 1.0, 10.0, 3.5, False, False, False, False]
        # Iris-versicolor
        sample2 = [5.0, 3.5, 1.3, 0.2, 17.8, 0.2, False, True, False, False]
        # Iris-virginica
        sample3 = [7.9, 5.0, 2.0, 1.8, 19.7, 9.1, True, False, True, True]
    */

    CalcFeatures(set);

    int i, index, block, k, j;

    for ( index = 0; index < size_plant; index++)
    {
        for ( i = 0; i < size_group; i++)
        {
            CalcIG(set, i, index);
        }
    }
    
    // for ( i = 0; i < size_group; i++)
    // {
    //     for ( index = 0; index < size_plant; index++)
    //     {
    //         for ( k = 0; k < size_vet; k++)
    //         {
    //             printf("%lf ", set[i].IG[index].IG_vet[k]);
    //         }
    //         printf(" | index -> %i | group -> %i\n", index, i);
    //     }
    // }
    // CrossValidation(set, i);

    for ( i = 0; i < size_group; i++)
    {
        CrossValidation(set, i);
    }
    
    return 0;
}


void CrossValidation(SubSet set[], int i)
{

    int j, k, index;
    double maior[size_plant] = {0};
    int plant[size_plant] = {0}, features_chosen[size_plant] = {0};

    for ( index = 0; index < size_plant; index++)
    {
        for ( j = 0; j < size_plant; j++)
        {
            if ( j == 0)
            {
                maior[index] = set[i].IG[index].IG_vet[j];
                plant[index] = index;
                features_chosen[index] = j;
                //set[k].IG_bool[index] = set[k].No[index]
            }
            if ( set[i].IG[index].IG_vet[j] > maior[index])
            {
                maior[index] = set[i].IG[index].IG_vet[j];
                plant[index] = index;
                features_chosen[index] = j;

            }
        }
    }
    
    int size = size_plant;  
    SelectionSort( set, maior, plant, features_chosen, size);

    for ( j = 0; j < size_plant; j++)
    {
        printf("%lf | index -> %i | group -> %i | features chosen -> %i \n", maior[j], plant[j], i, features_chosen[j]);
    }

    // numero aleatorio 0 a 24 -> grupo 0 - numero aleatorio 0 a 5 -> 0

    // for ( j = 0; j < size_plant; j++)
    // {
    //     if ( set[1].No[0].feature.F_vet[features_chosen[j]] == )
    //     {

    //     }
    //     else
    //     {

    //         continue;
    //     }
    //     if ()
    //     {

    //     }
    // }
    
}

void SelectionSort(SubSet set[], double v[], int plant[], int features_chosen[], int size)
{
	int i = 0, j = 0;
    for ( i = 0; i < size - 1; i++){
        for ( j = i + 1; j < size; j++){
            if ( v[i] < v[j]){
                swap(set, v, plant, features_chosen, i, j);
            }
        }
    }
}

void swap(SubSet set[], double v[], int plant[], int features_chosen[], int i, int j)
{
    double aux_v = v[i];
    v[i] = v[j];
    v[j] = aux_v;

    int aux_plant = plant[i];
    plant[i] = plant[j];
    plant[j] = aux_plant;

    int aux_features_chosen = features_chosen[i];
    features_chosen[i] = features_chosen[j];
    features_chosen[j] = aux_features_chosen;
}

void CalcIG(SubSet set[], int i, int index)
{
    int j, k;
    ///////////////////////////////////////////////////////// ENTROPY /////////////////////////////////////////////////////////
    int SumTrue[size_vet] = {0};
    int SumFalse[size_vet] = {0};
    int Ly[size_vet] = {0}, Ln[size_vet] = {0};
    int Ry[size_vet] = {0}, Rn[size_vet] = {0};
    int Yf = 0;
    int Nf = 0;

    for ( j = 0; j < size_ind; j++)
    {   
        if ( set[i].No[j].index == index) Yf++;
        for ( k = 0; k < size_vet; k++)
        {
            if ( set[i].No[j].feature.F_vet[k] == true) SumTrue[k]++;
            if ( set[i].No[j].index == index && set[i].No[j].feature.F_vet[k] == true) Ly[k]++;
        }
        
    }

    Nf = size_ind - Yf;
    for ( j = 0; j < size_vet; j++)
    {
        SumFalse[j] = size_ind - SumTrue[j];
        Ln[j] = SumTrue[j] - Ly[j];
        Ry[j] = Yf - Ly[j];
    }
    for ( j = -1; j < size_vet; j++, Rn[j] = SumFalse[j] - Ry[j]);

    double entropyRight[size_vet] = {0};
    double PyRight[size_vet] = {0};
    double PnRight[size_vet] = {0};
    
    double entropyLeft[size_vet] = {0};
    double PyLeft[size_vet] = {0};
    double PnLeft[size_vet] = {0};

    for ( j = 0; j < size_vet; j++)
    {
        PyRight[j] = Ry[j] * 1.0 / (SumFalse[j] * 1.0);
        PnRight[j] = Rn[j] * 1.0 / (SumFalse[j] * 1.0);
        entropyRight[j] = - ( PyRight[j] * log2(PyRight[j]) + PnRight[j] * log2(PnRight[j]));
        if (PyRight[j] == 0 || PnRight[j] == 0) entropyRight[j] = 0;
        PyLeft[j] = Ly[j] * 1.0 / (SumTrue[j] * 1.0);
        PnLeft[j] = Ln[j] * 1.0 / (SumTrue[j] * 1.0);
        entropyLeft[j] = - ( PyLeft[j] * log2(PyLeft[j]) + PnLeft[j] * log2(PnLeft[j]));
        if (PyLeft[j] == 0 || PnLeft[j] == 0) entropyLeft[j] = 0;
    }
    
    //EntropyFhater
    double PYF = 0, PNF = 0, EntropyF = 0;
    PYF = Yf * 1.0 / (size_ind * 1.0);
    PNF = Nf * 1.0 / (size_ind * 1.0);
    EntropyF = - ( PYF * log2(PYF) + PNF * log2(PNF));
    if (PYF == 0 || PNF == 0) EntropyF = 0;

    ///////////////////////////////////////////////////////// Weight /////////////////////////////////////////////////////////
    double WeightLeft[size_vet] = {0}, WeightRight[size_vet] = {0};
    for ( j = -1; j < size_vet; j++)
    {
        WeightLeft[j] = SumTrue[j] * 1.0 / size_ind;
        WeightRight[j] = SumFalse[j] * 1.0 / size_ind;
    }

    ///////////////////////////////////////////////////////// Information Gain /////////////////////////////////////////////////////////
    double GI[size_vet] = {0};
    for ( j = 0; j < size_vet; j++)
    {
        set[i].IG[index].IG_vet[j] = EntropyF - ( ( WeightRight[j] * entropyRight[j]) + ( WeightLeft[j] * entropyLeft[j]));    
    }
    
    /*
        stack overflow
    */
    // if ( i < size_group - 1)
    // {
    //     CalcIG(set, i + 1, index);
    // }
    // else
    // {
    //     if ( i == size_group - 1 && index < size_plant)
    //     {
    //         CalcIG(set, i + 1 - size_group, index + 1);
    //     }
    // }
}

void CalcFeatures(SubSet set[])
{
    double mean[size_vet][size_group];
    CalcMean(set, mean);
    int i, j, k;
    for ( i = 0; i < size_pop / size_ind; i++)
    {
        for ( j = 0; j < size_ind; j++)
        {
            for ( k = 0; k < size_vet; k++)
            {
                if ( set[i].No[j].SepalAndPetal[k] > mean[k][i]) set[i].No[j].feature.F_vet[k] = true;
                else set[i].No[j].feature.F_vet[k] = false;
            }
            // printf("group => %i \t- %0.2lf | %0.2lf | %0.2lf | %0.2lf | %s\t => %i | %0.2lf | %0.2lf\t|\t %d %d %d %d\n", i,set[i].No[j].SepalLength, set[i].No[j].SepalWidth, set[i].No[j].PetalLength, set[i].No[j].PetalWidth, set[i].No[j].Class, set[i].No[j].index, set[i].No[j].feature.SepalArea,  set[i].No[j].feature.PetalArea, set[i].No[j].feature.F_vet[0], set[i].No[j].feature.F_vet[1], set[i].No[j].feature.F_vet[2], set[i].No[j].feature.F_vet[3] );
        }
    }
}

void CalcMean(SubSet set[], double mean[size_vet][size_group])
{
    int i, j, k;
    double sum[size_vet] = {0};
    // [0]SepalLengthMean [1]SepalWidthMean [2]PetalLengthMean [3]PetalWidthMean
    for ( i = 0; i < size_pop / size_ind; i++)
    {
        for ( j = 0; j < size_ind; j++)
        {
            for ( k = 0; k < size_vet; k++)
            {
                sum[k] = sum[k] + set[i].No[j].SepalAndPetal[k];
            }
        }
        for ( j = 0; j < size_vet; j++)
        {
            mean[j][i] = sum[j] / size_ind;
        }
        for ( j = -1; j < size_vet; j++, sum[j] = 0);
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
                fscanf(file, "%lf %lf %lf %lf %s", &set[i].No[j].SepalAndPetal[0], &set[i].No[j].SepalAndPetal[1], &set[i].No[j].SepalAndPetal[2], &set[i].No[j].SepalAndPetal[3], set[i].No[j].Class);
                if (strcmp(set[i].No[j].Class, "Iris-setosa") == 0)set[i].No[j].index = 0;
                else if (strcmp(set[i].No[j].Class, "Iris-versicolor") == 0)set[i].No[j].index = 1;
                else if (strcmp(set[i].No[j].Class, "Iris-virginica") == 0)set[i].No[j].index = 2;
            }
        }
        fclose(file);
    }
}