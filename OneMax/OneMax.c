#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "OneMax.h"

int main()
{
    srand(time(NULL));
    int pop[size_pop][size_gen] = {0};
    int individuo = 0;

    startPop(pop);
    // viewerPop(pop);

    int i, j, k;
    for ( i = 0; i < generation; i++)
    {
        for ( j = 0; j < size_torneio; j++)
        {
            double prob = ((double) rand() / ((double)RAND_MAX + 1));
            if ( prob < prob_cruz)
            {
                    int index_father1 = rand() % size_pop;
                    int index_father2;
                do
                {
                    index_father2 = rand() % size_pop;
                } while ( index_father1 == index_father2);
                
                int son[1][size_gen] = {0};
                cross(index_father1, index_father2, son, pop);

                prob = ((double) rand() / ((double)RAND_MAX + 1));

                if ( prob < prob_mut)
                {
                    mutation(son);
                }

                int score_father = getScore(index_father1 ,pop);
                int score_son = getScore(0, son);
                
                if ( score_son > score_father)
                {
                    for ( k = 0; k < size_gen; k++)
                    {
                        pop[index_father1][k] = son[0][k];
                    }
                }
            }
        }

        int index_best = getBest(pop);
        int best_score = getScore(index_best, pop);
        printf("------------------\nGeneration - %i\n", i + 1);
        printf("Index = %i\tBest score = %i\n",index_best ,best_score);
        viewerPop(index_best , pop);
        printf("\n\n");
        if ( best_score == size_gen)
        {
            break;
        }
    }
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

void viewerPop( int i, int pop[][size_gen])
{
    int j, score;

    for ( j = 0; j < size_gen; j++)
    {
        printf("%i ", pop[i][j]);
    }

}

int getScore( int individuo, int pop[][size_gen])
{
    int sum = 0, i;

    for ( i = 0; i < size_gen; i++)
    {
        sum += pop[individuo][i];
    }
    return sum;
}

void mutation( int son[][size_gen])
{
    int gene = rand() % size_gen;

    if ( son[0][gene] == 0)
    {
        son[0][gene] = 1;
    }
    else
    {
        son[0][gene] = 0;
    }
}

void cross( int index_father1, int index_father2, int son[][size_gen], int pop[][size_gen])
{
    int point = rand() % size_gen;
    int i, j;
    for ( i = 0; i <= point; i++)
    {
        son[0][i] = pop[index_father1][i];
    }
    for ( i = point + 1; i < size_gen; i++)
    {
        son[0][i] = pop[index_father2][i];
    }
}

int getBest( int pop[][size_gen])
{
    int index_Best = 0;
    int i = 0;
    int score_Best = getScore( 0, pop);

    for ( i = 0; i < size_pop; i++)
    {
        int score = getScore( i, pop);
        if ( score > score_Best)
        {
            index_Best = i;
            score_Best = score;
        }
    }
    return index_Best;
}