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
    bool SepalLengthAboveMean;
    bool SepalWidthAboveMean;
    bool PetalLengthAboveMean;
    bool PetalWidthAboveMean;
};

struct InformationGain
{
    double IIG[size_vet]; // , IG_SepalLength , IG_SepalWidth , IG_PetalLength , IG_PetalWidth 
    double IG_SepalLength;
    double IG_SepalWidth;
    double IG_PetalLength;
    double IG_PetalWidth;
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
    double Length_Width[size_vet];
    bool Ffeature[size_vet] //SepalLengthAboveMean ,SepalWidthAboveMean ,PetalLengthAboveMean ,PetalWidthAboveMean
};

struct subset
{
    Nodo No[size_ind]; 
    InfoGain IG[size_plant];    // size_plante => setosa [0], versicolor [1], virginica [2]
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

    int i, index;
    for ( index = 0; index < 3; index++)
    {
        for (  i = 0; i < 25; i++)
        {
            CalcIG(set, i, index);
        }
    }
    

    return 0;
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
        if (set[i].No[j].index == index) Yf++;
        if ( set[i].No[j].feature.SepalLengthAboveMean == true) SumTrue[0]++;
        if ( set[i].No[j].index == index && set[i].No[j].feature.SepalLengthAboveMean == true) Ly[0]++;
        if ( set[i].No[j].feature.SepalWidthAboveMean  == true) SumTrue[1]++;
        if ( set[i].No[j].index == index && set[i].No[j].feature.SepalWidthAboveMean  == true) Ly[1]++;
        if ( set[i].No[j].feature.PetalLengthAboveMean == true) SumTrue[2]++;
        if ( set[i].No[j].index == index && set[i].No[j].feature.PetalLengthAboveMean == true) Ly[2]++;
        if ( set[i].No[j].feature.PetalWidthAboveMean  == true) SumTrue[3]++;
        if ( set[i].No[j].index == index && set[i].No[j].feature.PetalWidthAboveMean  == true) Ly[3]++;
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

    set[i].IG[index].IG_SepalLength = EntropyF - ( ( WeightRight[0] * entropyRight[0]) + ( WeightLeft[0] * entropyLeft[0]));
    set[i].IG[index].IG_SepalWidth = EntropyF - ( ( WeightRight[1] * entropyRight[1]) + ( WeightLeft[1] * entropyLeft[1]));
    set[i].IG[index].IG_PetalLength = EntropyF - ( ( WeightRight[2] * entropyRight[2]) + ( WeightLeft[2] * entropyLeft[2]));
    set[i].IG[index].IG_PetalWidth = EntropyF - ( ( WeightRight[3] * entropyRight[3]) + ( WeightLeft[3] * entropyLeft[3]));
    
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
            set[i].No[j].feature.SepalArea = set[i].No[j].SepalLength * set[i].No[j].SepalWidth;
            set[i].No[j].feature.PetalArea = set[i].No[j].PetalLength * set[i].No[j].PetalWidth;
            if ( set[i].No[j].Ffeature[k])
            {
                /* code */
            }
            
            if ( set[i].No[j].SepalLength > mean[0][i]) set[i].No[j].feature.SepalLengthAboveMean = true;
            else set[i].No[j].feature.SepalLengthAboveMean = false;
            if ( set[i].No[j].SepalWidth > mean[1][i]) set[i].No[j].feature.SepalWidthAboveMean = true;
            else set[i].No[j].feature.SepalWidthAboveMean = false;
            if ( set[i].No[j].PetalLength > mean[2][i]) set[i].No[j].feature.PetalLengthAboveMean = true;
            else set[i].No[j].feature.PetalLengthAboveMean = false;
            if ( set[i].No[j].PetalWidth > mean[3][i]) set[i].No[j].feature.PetalWidthAboveMean = true;
            else set[i].No[j].feature.PetalWidthAboveMean = false;
            //printf("group => %i \t- %0.2lf | %0.2lf | %0.2lf | %0.2lf | %s\t => %i | %0.2lf | %0.2lf\t|\t %d %d %d %d\n", i,set[i].No[j].SepalLength, set[i].No[j].SepalWidth, set[i].No[j].PetalLength, set[i].No[j].PetalWidth, set[i].No[j].Class, set[i].No[j].index, set[i].No[j].feature.SepalArea,  set[i].No[j].feature.PetalArea, set[i].No[j].feature.SepalLengthAboveMean, set[i].No[j].feature.SepalWidthAboveMean, set[i].No[j].feature.PetalLengthAboveMean, set[i].No[j].feature.PetalWidthAboveMean );
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
            }
            sum[i] = sum[i] + set[i].No[j].Length_Width[k];
            
            // sum[0] = sum[0] + set[i].No[j].SepalLength;
            // sum[1] = sum[1] + set[i].No[j].SepalWidth;
            // sum[2] = sum[2] + set[i].No[j].PetalLength;
            // sum[3] = sum[3] + set[i].No[j].PetalWidth;
            //printf("%lf %lf %lf %lf\n", set[i].No[j].SepalLength, set[i].No[j].SepalWidth, set[i].No[j].PetalLength, set[i].No[j].PetalWidth);
        }
        mean[0][i] = sum[0] / size_ind;
        mean[1][i] = sum[1] / size_ind;
        mean[2][i] = sum[2] / size_ind;
        mean[3][i] = sum[3] / size_ind;

        for ( j = -1; j < size_vet; j++, sum[j] = 0);
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
                fscanf(file, "%lf %lf %lf %lf %s", &set[i].No[j].Length_Width[0], &set[i].No[j].Length_Width[1], &set[i].No[j].Length_Width[2], &set[i].No[j].Length_Width[3], set[i].No[j].Class);
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