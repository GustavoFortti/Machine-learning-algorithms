#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "DecisionTree.h"

struct InformationGain
{
    double IG_vet[size_vet]; 
    bool ig_bool[size_vet];      
};

struct plants 
{
    double SepalAndPetal[size_vet]; 
    char Class[50];
    int index;  

    // double SepalArea;
    // double PetalArea;
    bool cross_mean[size_vet];
};

struct group
{
    Plants pl[size_ind];
    IG ig[size_plant]; 
    
};

struct pop
{
    Group gr[size_group];      
};

int a = 0, e = 0;
int main()
{
    Pop *p;
    p = input();
    int i = 0, j, k;

    for ( i = 0; i < size_group; i++)
    {
        CrossValidation(p, i);
    }

    // for ( i = 0; i < 5; i++)
    // {
    //     for ( j = 0; j < 3; j++)
    //     {
    //         for ( k = 0; k < 4; k++)
    //         {
    //             printf("%0.3lf \t", p->gr[i].ig[j].IG_vet[k]);
    //         }
    //         for ( k = 0; k < 4; k++)
    //         {
    //             printf(" %i ",  p->gr[i].ig[j].ig_bool[k]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n\n");
    // }
    for ( i = 0; i < size_group; i++)
    {
        D3(p, i);
        printf("\n\n");
    }
    // printf("\n%i %i\n", a, e);

}

void D3(Pop *p, int i)
{
    int j, k, l;
    double ig[size_plant] = {0};
    int index[size_plant] = {0};
    for ( j = 0; j < size_plant; j++)
    {
        index[j] = j;
    }
    
    for ( j = 0; j < size_plant; j++)
    {
        for ( k = 0; k < size_vet; k++)
        {
            ig[j] = ig[j] + p->gr[i].ig[j].IG_vet[k];
        }
    }

    int size = size_plant;
    SelectionSort(ig, size, index);

    bool ig_cross[size_plant][size_vet];
    for ( j = 0; j < 3; j++)
    {
        for ( k = 0; k < 4; k++)
        {
            printf("%0.3lf \t", p->gr[i].ig[index[j]].IG_vet[k]);
        }
        for ( k = 0; k < 4; k++)
        {
            printf(" %i ",  p->gr[i].ig[index[j]].ig_bool[k]);
            ig_cross[j][k] = p->gr[i].ig[index[j]].ig_bool[k];
        }
        printf("  %i %lf", index[j], ig[j]);
        printf("\n");
    }

    double aux[size_plant] = {0};

    for ( j = 0; j < size_ind; j++)
    {
        for ( k = 0; k < size_plant; k++)
        {
            for ( l = 0; l < size_vet; l++)
            {
                if ( p->gr[i].pl[j].cross_mean[l] == ig_cross[k][l])
                {
                    aux[k] = aux[k] + p->gr[i].ig[index[k]].IG_vet[l];
                    printf(" %i",  p->gr[i].pl[j].cross_mean[l]);
                }
                else
                {
                    printf(" x");
                }
            }

            printf("\t");
            printf("ig = %lf \t", aux[k]);
            for ( l = 0; l < size_vet; l++)
            {
                printf(" %i",  p->gr[i].pl[j].cross_mean[l]);
            }
            printf("\n");
        }
        double maior = -1;
        int iris = 0;
        for ( k = 0; k < size_plant; k++)
        {
            if ( aux[k] > maior)
            {
                maior = aux[k];
                iris = index[k];
            }
        }
        printf("\t\t\t%i %i \n\n", iris, p->gr[i].pl[j].index);
        if ( iris ==  p->gr[i].pl[j].index) a++;
        else e++;

        for ( k = 0; k < size_plant; k++)
        {
            aux[k] = 0;
        }
    }
    printf("\n%i %i\n", a, e);
}

void SelectionSort( double v[], int size, int index[])
{
	long i=0, j=0;
    for ( i = 0; i < size-1; i++){
        for ( j = i; j < size; j++){
            if ( v[i] < v[j]){
                swap( v, i, j, index);
            }
        }
    }
}

void swap( double v[], int i, int j, int index[])
{
    double aux = v[i];
    v[i] = v[j];
    v[j] = aux;

    int aux2 = index[i];
    index[i] = index[j];
    index[j] = aux2;
}


void CrossValidation(Pop *p, int group_block)
{
    CalcFeatures(p, group_block);
    int i;
    for ( i = 0; i < size_plant; i++)
    {
        CalcIG(p, i, group_block);
    }
    printf("\n");

    
}


void CalcIG(Pop *p, int plant, int group_block)
{
    int i, j, k;
    ///////////////////////////////////////////////////////// ENTROPY /////////////////////////////////////////////////////////
    int SumTrue[size_vet] = {0};
    int SumFalse[size_vet] = {0};
    int Ly[size_vet] = {0}, Ln[size_vet] = {0};
    int Ry[size_vet] = {0}, Rn[size_vet] = {0};
    int Yf = 0;
    int Nf = 0;

    for ( i = 0; i < size_group; i++)
    {
        if ( group_block != i)
        {
            for ( j = 0; j < size_ind; j++)
            {   
                if ( p->gr[i].pl[j].index == plant) Yf++;
                for ( k = 0; k < size_vet; k++)
                {
                    if ( p->gr[i].pl[j].cross_mean[k]  == true) SumTrue[k]++;
                    if ( p->gr[i].pl[j].index == plant && p->gr[i].pl[j].cross_mean[k]  == true) Ly[k]++;
                }
                
            }
        }
    }

    // printf("Yf =  %i\n", Yf);

    int size_ind_aux = size_ind * (size_group - 1);
    Nf = size_ind_aux - Yf;

    for ( j = 0; j < size_vet; j++)
    {
        SumFalse[j] = size_ind_aux - SumTrue[j];
        Ln[j] = SumTrue[j] - Ly[j];
        Ry[j] = Yf - Ly[j];
    }
    for ( j = 0; j < size_vet; j++)
    {
        Rn[j] = SumFalse[j] - Ry[j];
    }
    // printf("\n\n");
    // for ( i = 0; i < size_vet; i++)
    // {
    //     printf(" %i %i\n", SumTrue[i], Ly[i]);
    // }
    

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
        if (SumFalse[j] == 0) PyRight[j] = 0, PnRight[j] = 0;
        entropyRight[j] = - ( PyRight[j] * log2(PyRight[j]) + PnRight[j] * log2(PnRight[j]));
        if (PyRight[j] == 0 || PnRight[j] == 0) entropyRight[j] = 0;
        PyLeft[j] = Ly[j] * 1.0 / (SumTrue[j] * 1.0);
        PnLeft[j] = Ln[j] * 1.0 / (SumTrue[j] * 1.0);
        if (SumTrue[j] == 0) PyLeft[j] = 0, PnLeft[j] = 0;
        entropyLeft[j] = - ( PyLeft[j] * log2(PyLeft[j]) + PnLeft[j] * log2(PnLeft[j]));
        if (PyLeft[j] == 0 || PnLeft[j] == 0) entropyLeft[j] = 0;
    }
    
    //EntropyFhater
    double PYF = 0, PNF = 0, EntropyF = 0;
    PYF = Yf * 1.0 / (size_ind_aux * 1.0);
    PNF = Nf * 1.0 / (size_ind_aux * 1.0);
    EntropyF = - ( PYF * log2(PYF) + PNF * log2(PNF));
    if (PYF == 0 || PNF == 0) EntropyF = 0;

    ///////////////////////////////////////////////////////// Weight /////////////////////////////////////////////////////////
    double WeightLeft[size_vet] = {0}, WeightRight[size_vet] = {0};
    for ( j = 0; j < size_vet; j++)
    {
        WeightLeft[j] = SumTrue[j] * 1.0 / size_ind_aux;
        WeightRight[j] = SumFalse[j] * 1.0 / size_ind_aux;
    }
    ///////////////////////////////////////////////////////// Information Gain /////////////////////////////////////////////////////////
    double GI[size_vet] = {0};
    for ( j = 0; j < size_vet; j++)
    {
        p->gr[group_block].ig[plant].IG_vet[j] = EntropyF - ( ( WeightRight[j] * entropyRight[j]) + ( WeightLeft[j] * entropyLeft[j]));
        if ( Ly[j] > SumTrue[j] - Ly[j]) p->gr[group_block].ig[plant].ig_bool[j] = 1;
        else p->gr[group_block].ig[plant].ig_bool[j] = 0;
        // printf("%0.3lf ", p->gr[group_block].ig[plant].IG_vet[j]);
    }
    // printf("\n");
}

void CalcFeatures(Pop *p, int group_block)
{
    double mean[size_vet];
    int i, j ,k;
    for ( i = 0; i < size_vet; i++)
    {
        CalcMean(p, mean, group_block, i);
        // printf("%.2f ", mean[i]);
    }
    // printf("\n");
    for ( i = 0; i < size_group; i++)
    {
        for ( j = 0; j < size_ind; j++)
        {
            for ( k = 0; k < size_vet; k++)
            {
                if ( p->gr[i].pl[j].SepalAndPetal[k] > mean[k]) p->gr[i].pl[j].cross_mean[k] = true;
                else p->gr[i].pl[j].cross_mean[k] = false;
            }
            // printf("group => %i - group block = %i \t- %0.2lf | %0.2lf | %0.2lf | %0.2lf | %s\t => %i  \t|\t %i %i %i %i \n", i, group_block == i, p->gr[i].pl[j].SepalAndPetal[0], p->gr[i].pl[j].SepalAndPetal[1], p->gr[i].pl[j].SepalAndPetal[2], p->gr[i].pl[j].SepalAndPetal[3], p->gr[i].pl[j].Class, p->gr[i].pl[j].index, p->gr[i].pl[j].cross_mean[0],p->gr[i].pl[j].cross_mean[1] ,p->gr[i].pl[j].cross_mean[2] ,p->gr[i].pl[j].cross_mean[3]);
        }
    }

}

void CalcMean(Pop *p, double mean[size_vet], int group_block, int index)
{
    int i, j;
    double sum = 0;
    for ( i = 0; i < size_group; i++)
    {
        if ( i != group_block)
        {
            for ( j = 0; j < size_ind; j++)
            {
                sum = sum + p->gr[i].pl[j].SepalAndPetal[index];
            }
        }
    }
    for ( j = 0; j < size_vet; j++)
    {
        mean[index] = sum / (size_pop - size_ind);
    }
}

Pop* input()
{
    Pop *p = (Pop*) malloc(sizeof(Pop));
    FILE *file;
    file = fopen("Iris-dataset.txt", "r");
    int i, j;
    if (file != NULL)
    {
        for ( i = 0; i < size_group; i++)
        {
            for ( j = 0; j < size_ind; j++)
            {
                fscanf(file, "%lf %lf %lf %lf %s", &p->gr[i].pl[j].SepalAndPetal[0] , &p->gr[i].pl[j].SepalAndPetal[1], &p->gr[i].pl[j].SepalAndPetal[2], &p->gr[i].pl[j].SepalAndPetal[3], p->gr[i].pl[j].Class);
                if (strcmp(p->gr[i].pl[j].Class, "Iris-setosa") == 0)p->gr[i].pl[j].index = 0;
                else if (strcmp(p->gr[i].pl[j].Class, "Iris-versicolor") == 0)p->gr[i].pl[j].index = 1;
                else if (strcmp(p->gr[i].pl[j].Class, "Iris-virginica") == 0)p->gr[i].pl[j].index = 2;
            }
        }
        fclose(file);
    }
    return p;
}