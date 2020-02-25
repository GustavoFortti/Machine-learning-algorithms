#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "AG.H"

int main()
{
    srand(time(NULL));
    Pop *p;
    p = startPop();
    viewerPop(p);

    for (int i = 0; i < generation; i++)
    {
        printf("\n\tGeneration = %i\n", i);
        int index_best = getBest(p);
        double array_best[size_gen];
        conversion_StrctForVector(p, array_best, index_best);
        double score_best = getScore(array_best);
        double x = 0;
        // printf("\t");
        // viewerPop(p);
        for (int i = 0; i < size_gen; i++)
        {
            // if ( array_best[i] > 0) printf("\t %.1lf ", array_best[i]);
            // else printf("\t%.1lf ", array_best[i]);
            x = x + array_best[i];
        }
        printf("\n\tx = %.1lf  score = %lf\n", x, score_best);
        if ( score_best >= (double)value && score_best < ((double)value + 0.01))
        {
            printf(" win %i\n", i);
            break;
        }

        int elitism = rand() % size_gen;
        for (int j = 0; j < tournament; j++)
        {
            double prob = (double)rand() / ((double)RAND_MAX + 1);
            if ( prob < prob_cross )
            {
                int index_xx;
                int index_xy;
                do
                {
                    index_xx = rand() % size_gen;
                    index_xy = rand() % size_gen;
                } while ( index_xy == index_xx || index_xy == elitism || index_xx == elitism);

                double son[size_gen] = {0};
                cross(p, index_xx, index_xy, son);

                double prob = (double)rand() / ((double)RAND_MAX + 1);
                if ( prob < prob_mutation) mutation(son);
                

                double v_xx[size_gen], v_xy[size_gen];
                conversion_StrctForVector(p, v_xx, index_xx);
                conversion_StrctForVector(p, v_xy, index_xy);

                // for (int k = 0; k < size_gen; k++)
                // {
                //     printf("%0.1lf ", v_xy[k]);
                // }
                // printf("\n");

                double score_xx = getScore(v_xx);
                double score_xy = getScore(v_xy);
                double score_son = getScore(son);

                // printf("%lf  %lf  %lf\n", score_xx , score_xy  , score_son);
                double nears_xx = howClose(score_xx);
                double nears_xy = howClose(score_xy);
                double nears_son = howClose(score_son);

                // printf("%lf  %lf  %lf\n", nears_xx , nears_xy  , nears_son);

                // printf("%i\n", nears_xx < nears_xy && score_xx < nears_son);
                // printf("%i\n", nears_xy < nears_xx && nears_xy < nears_son);

                if ( nears_xx > nears_xy && score_xx > nears_son) Dominant(p, son, index_xx);
                else if ( nears_xy > nears_xx && nears_xy > nears_son) Dominant(p, son, index_xy);
            }
        }
    }
    return 0;
}

void Dominant(Pop *p, double son[], int index)
{
    for (int i = 0; i < size_gen; i++)
    {
        (index + p)->gen[i] = son[i];
    }
}

void mutation(double son[])
{
    int gen = rand() % size_gen;
    int choice;

    choice = rand() % 2;
    if ( choice == 1) son[gen] = ((rand() % RAND_MAX)); //pos
    else son[gen] = ((rand() % RAND_MAX) * (-1));       //neg
    son[gen] = son[gen] / (rand() % RAND_MAX);
}

void cross(Pop *p, int xx, int xy, double son[])
{
    int inherited[size_gen] = {0};
    int dominant = rand() % 2;

    for (int i = 0; i < size_gen; i++)
    {
        inherited[i] = i;
    }
    shuffle(inherited);

    for (int i = 0; i < size_gen; i++)
    {
        int choice = rand() % 2;
        if ( choice == 0) son[i] = (xx + p)->gen[inherited[i]];
        else son[i] = (xy + p)->gen[inherited[i]];
    }
}

void shuffle(int v[])
{
    int j;
    for (int i = size_gen - 1; i > 0; i--)
    {
        j = rand() % i;
        swap(v, i, j);
    }
}

void swap(int v[], int i, int j)
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

int getBest(Pop *p)
{
    double result_right, result_left;
    double neares_right = RAND_MAX;
    double neares_left = RAND_MAX * (-1);
    int index_right, index_left, index;
    for (int i = 0; i < size_pop; i++)
    {
        double v[size_gen];
        conversion_StrctForVector(p, v, i);
        double score = getScore(v);
        result_right = score;
        result_left  = score;
        if ((result_right) < neares_right && result_right >= value) neares_right = result_right, index_right = i;
        else if ((result_left) > neares_left && result_left <= value) neares_left = result_left, index_left = i;
    }
    neares_right = howClose(neares_right);
    neares_left = howClose(neares_left);
    if ( neares_right < neares_left) return index_right;
    return index_left;
}

double howClose(double neares)
{
    if ( value > 0)
    {
        if (neares < 0) neares = (neares  * (-1)) + value;
        else neares = value - neares;
    }
    else
    {
        if (neares < 0) neares = value - (neares * (-1));
        else neares = value - neares;
    }
    if ( neares < 0) neares = neares * (-1);
    
    return neares;
}

void conversion_StrctForVector(Pop *p, double v[], int i)
{
    for (int j = 0; j < size_gen; j++)
    {
        v[j] = (i + p)->gen[j];
    }
}

double getScore(double v[])
{
    double x = 0;
    for (int i = 0; i < size_pop; i++)
    {
        x = x + v[i];
    }
    return ((2 * x) + 5);
}

void viewerPop(Pop *p)
{
    double x = 0;
    for (int i = 0; i < size_pop; i++)
    {
        printf("\tG - %i", i);
        for (int j = 0; j < size_gen; j++)
        {
            if ( (i + p)->gen[j] > 0)  printf("\t %0.1Lf",(i + p)->gen[j]);
            else printf("\t%0.1Lf",(i + p)->gen[j]);
            x = x + (i + p)->gen[j];
        }
        printf(" \t x = %.1lf \n", x);
        x = 0;
    }
}

Pop* startPop()
{
    Pop *p = (Pop*) malloc(size_pop*sizeof(Pop));
    int choice;
    for (int i = 0; i < size_pop; i++)
    {
        for (int j = 0; j < size_gen; j++)
        {
            choice = rand() % 2;
            if ( choice == 1) (i + p)->gen[j] = ((rand() % RAND_MAX)); //pos
            else (i + p)->gen[j] = ((rand() % RAND_MAX) * (-1));       //neg
            (i + p)->gen[j] = (i + p)->gen[j] / (rand() % RAND_MAX);
        }
    }
    return p;
}