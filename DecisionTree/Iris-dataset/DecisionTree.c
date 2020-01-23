#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "DecisionTree.h"

/*
    CROSS VALIDATION 

        MODIFICAÇÕES NECESSARIAS: utilizar sistema de score 
        baseado em probabilidade para aumentar a chance de 
        acertos sobre os dados.
        Ao inves de puxar apenas uma informação do IG que 
        seria apenas o maior, utilizar tambem as outras 
        para aumentar a margem de acertos...
        apos a utilização desse metodo, ai sim utilizar os 
        algoritimos geneticos!!

    ALGORITIMOS GENETICOS 

        ...

*/

struct features
{
    double SepalArea;
    double PetalArea;
    bool cross[size_vet]; 
    /* 
        População -> cross
       [0]SepalLength [1]SepalWidth [2]PetalLength [3]PetalWidth
    */
};

struct InformationGain
{
    double IG_vet[size_vet];        //[0]SepalLength [1]SepalWidth [2]PetalLength [3]PetalWidth
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
    Nodo No[size_ind];              // poop
    InfoGain IG[size_plant];        //size_plante => setosa [0], versicolor [1], virginica [2]
    bool IG_bool[size_plant];
};

int a2 = 0, e2 = 0;

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

    int i, index, k, j;
    int aux = 0;
    // for ( i = 0; i < size_group; i++)
    // {
    //     for ( index = 0; index < size_ind; index++)
    //     {
    //         CrossValidation(set, i, index);
    //     }
    // }

    // i = rand() % 24;
    // index = rand() % 5;

    i = 24;
    index = 5;
    for ( index = 0; index < 6; index++)
    {
        printf("\t\t  --ENTRADA %i -- \n\n", index);
        CrossValidation(set, i, index);
        printf("\n\n");
    }
    
    
    // printf("Acertos 2 = %i\nErros 2 = %i\n", a2, e2);

    // printf("Setosa %i - Versicolor %i - Virginica %i \n", SE, VER, VIR);
    return 0;
}

void CrossValidation(SubSet set[], int i, int index)
{

    CalcFeatures(set, i, index);
    int k, j;
    int block_index = index;

    for ( index = 0; index < size_plant; index++)
    {
        CalcIG(set, i, index, block_index);
        // for ( k = 0; k < size_vet; k++)
        // {
        //     printf("%lf ", set[i].IG[index].IG_vet[k]);
        // }
        // printf(" \t|\t index -> %i |\t group -> %i\n", index, i);
    }

    double IG_sort[size_plant][size_vet] = {0};
    int CROSS[size_plant][size_vet] = {0};
    int x[size_plant][size_vet] = {0}, y[size_vet][size_vet] = {0};
    int size = size_vet;
    // printf("%i \n", block_index);
    for ( index = 0; index < size_plant; index++)
    {
        for ( j = 0; j < size_vet; j++)
        {
            IG_sort[index][j] = set[i].IG[index].IG_vet[j];
            CROSS[index][j] = set[i].No[index].feature.cross[j]; //modificar para tornar aleatorio, E UTILIZAR MAIS DE UM IG!!!
            y[index][j] = j;
            x[index][j] = index;
        }
    }

    for ( j = 0; j < size_plant; j++)
    {
        printf("Group -> %i \t|", i);
        for ( k = 0; k < size_vet; k++)
        {
            printf("%lf ", IG_sort[j][k]);
        }
        for ( k = 0; k < size_vet; k++)
        {
            printf(" x = %i y = %i -> %i = ", x[j][k], y[j][k], CROSS[j][k]);
            printf("%i |", set[i].No[block_index].feature.cross[y[j][k]]);
        }
        
        printf("\n");
    }

    double percent[size_plant] = {0};
    int sum[size_plant] = {0};
    double val = 0;
    for ( j = 0; j < size_plant; j++)  //modificar para tornar aleatorio, E UTILIZAR MAIS DE UM IG!!!
    {
        for ( k = 0; k < size_vet; k++)
        {
            if ( CROSS[j][k] == set[i].No[block_index].feature.cross[y[j][k]])
            {
                                // j = index
                // double val = IG_sort[j][k] * (100 / size_vet);
                percent[j] = percent[j] + IG_sort[j][k];
                sum[j]++;
            }
        }
    }

    double MAX = percent[0];
    int R = 0;
    printf("Resposta \t\t%s \n", set[i].No[block_index].Class);

    for ( j = 0; j < size_plant - 1; j++)
    {
        // printf("%lf \n", percent[j]);
        if ( percent[j + 1] > MAX )
        {
            R = j + 1;
            MAX = percent[j + 1];
        }
    }
    // printf("%i \n", strcmp(set[i].No[block_index].Class, set[i].No[R2].Class));
    for ( j = 0; j < size_plant; j++)
    {
        // printf("%lf %s \n", percent[j],  set[i].No[j].Class);
    }
    // printf("%s = %s \n", set[i].No[block_index].Class, set[i].No[R2].Class);
    
    if ( strcmp(set[i].No[block_index].Class, set[i].No[R].Class) ==  0)
    {
        // printf("AC\n\n");
        a2++;
    }
    else
    {
        printf("ERRO  -> \t\t%s\n\n", set[i].No[R].Class);
        e2++;
    }

}

void CalcIG(SubSet set[], int i, int index, int block_index)
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
        if ( set[i].No[j].index == index && block_index != j) Yf++;
        if ( block_index != j)
        {
            for ( k = 0; k < size_vet; k++)
            {
                if ( set[i].No[j].feature.cross[k] == true) SumTrue[k]++;
                if ( set[i].No[j].index == index && set[i].No[j].feature.cross[k] == true) Ly[k]++;
            }
        }
    }

    // for ( j = 0; j < size_vet; j++)
    // {
    //     printf("%d ", set[i].No[index].feature.cross[j]);
    // }
    // printf("   ");

    int size_ind_aux = size_ind - 1;

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
        set[i].IG[index].IG_vet[j] = EntropyF - ( ( WeightRight[j] * entropyRight[j]) + ( WeightLeft[j] * entropyLeft[j]));    
    }
}

void CalcFeatures(SubSet set[], int i, int index)
{
    double mean[size_vet];
    CalcMean(set, mean, i, index);
    int j, k;
    for ( j = 0; j < size_ind; j++)
    {
        set[i].No[j].feature.SepalArea = set[i].No[j].SepalAndPetal[0] * set[i].No[j].SepalAndPetal[1];
        set[i].No[j].feature.PetalArea = set[i].No[j].SepalAndPetal[2] * set[i].No[j].SepalAndPetal[3];
        for ( k = 0; k < size_vet; k++)
        {
            if ( set[i].No[j].SepalAndPetal[k] > mean[k]) set[i].No[j].feature.cross[k] = true;
            else set[i].No[j].feature.cross[k] = false;
        }
        printf("group => %i - block = %i \t- %0.2lf | %0.2lf | %0.2lf | %0.2lf | %s\t => %i | %0.2lf | %0.2lf\t|\t %d %d %d %d\n", i, (j == index), set[i].No[j].SepalAndPetal[0], set[i].No[j].SepalAndPetal[1], set[i].No[j].SepalAndPetal[2], set[i].No[j].SepalAndPetal[3], set[i].No[j].Class, set[i].No[j].index, set[i].No[j].feature.SepalArea,  set[i].No[j].feature.PetalArea, set[i].No[j].feature.cross[0], set[i].No[j].feature.cross[1], set[i].No[j].feature.cross[2], set[i].No[j].feature.cross[3] );
    }
}

void CalcMean(SubSet set[], double mean[size_vet], int i, int index)
{
    int j, k;
    double sum[size_vet] = {0};
    // [0]SepalLengthMean [1]SepalWidthMean [2]PetalLengthMean [3]PetalWidthMean
    for ( j = 0; j < size_ind; j++)
    {
        if ( j != index)
        {
            for ( k = 0; k < size_vet; k++)
            {
                sum[k] = sum[k] + set[i].No[j].SepalAndPetal[k];
            }
        }
    }
    for ( j = 0; j < size_vet; j++)
    {
        mean[j] = sum[j] / size_ind;
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