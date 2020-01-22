#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size_gen 10
#define size_pop 50
#define size_torneio 20
#define generation 100
#define prob_mut 0.2
#define prob_cruz 0.7

int main()
{
    int pop[size_pop][size_gen] = {0};
    int individuo = 0;

    startPop( pop);


    return 0;
}

void startPop( int pop[][size_gen])
{
    int i, j;
    for ( i = 0; i < size_pop; i++)
    {
        for ( j = 0; j < size_gen; j++)
        {
            int num = rand() % 2;
            pop[i][j] = num;
        }
    }
}

void viewerPop( int pop[][size_gen])
{
    int i, j;
    for ( i = 0; i < size_pop; i++)
    {
        for ( j = 0; j < size_gen; j++)
        {
            printf("%i ", pop[i][j]);
        }
        printf("\n");
    }
}

int getScore( int individuo, int pop[][size_gen], int i)
{
    int sum = 0, i;

    for ( i = 0; i < size_gen; i++)
    {
        sum += pop[individuo][i];
    }
    return sum;
}

void mutation( int individuo, int pop[][size_gen])
{
    int gene = rand() % size_gen;

    if ( pop[individuo][gene] == 0)
    {
        pop[individuo][gene] = 1;
    }
    else
    {
        pop[individuo][gene] = 0;
    }
}

void cross( int index_father1, int index_father2, int son[], int pop[][size_gen])
{
    int point = rand() % size_gen;
    int i, j;
    for ( i = 0; i <= point; i++)
    {
        // son[i] = pop[index_father1][i];
    }
    for ( i = point + 1; i < size_gen; i++)
    {
        // son[i]
    }
}

int getBest(int individuo, int pop[][size_gen])
{
    int index_Best = 0;
    int i = 0;
    int score_Best = getScore( individuo, pop, i);

    for ( i = 0; i < size_pop; i++)
    {
        int score = getScore( individuo, pop, i);
    }
    
}