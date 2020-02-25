#include "Search_X.h"

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

void inserctionSort( double v[], int size, int index[])
{
	double escolhido = 0;
    int j, i, aux = 0;
    for ( i = 1; i < size; i++){
        escolhido = v[i];
        aux = index[i];
        j = i - 1;
        while ((j >= 0) && ( v[j] < escolhido)){
            v[j + 1] = v[j];
            index[j + 1] = index[j];
            j--;
        }
        v[j + 1] = escolhido;        
        index[j + 1] = aux;
    }
}

int selectionByRating(Pop *p, int index)
{
    // printf("\n\n");
    double score_pop[size_pop], nears_pop[size_pop], pop[size_pop];
    int index_pop[size_gen];
    for (int i = 0; i < size_pop; i++)
    {
        conversion_StrctForVector(p, pop, i);
        score_pop[i] = getScore(pop);
        double aux = score_pop[i];
        nears_pop[i] = howClose(aux);
        index_pop[i] = i;
        // printf("\t%.1lf\t %.1lf\t %i \n", score_pop[i], nears_pop[i], i);
    }
    // printf("\n");
    int size = size_pop;
    inserctionSort(nears_pop, size, index_pop);
    // for (int i = 0; i < size_pop; i++)
    // {
    //     printf("\t%.1lf\t %.1lf\t %i \n", score_pop[index_pop[i]], nears_pop[i], index_pop[i]);
    // }
    
    int range;
    int weight[size_pop + 1] = {0};
    weight[0] = 1;
    for (int i = 1; i < size_pop + 1; i++)
    {
        weight[i] = weight[i - 1] + (i + 1);
    }
    range = weight[size_pop];

    // int choice = (rand() % range) + 1;
    // int choice = (rand() % weight[size_pop - 1]) + 1;
    int choice = (rand() % range) + 1;
    // printf("range = %i\n", range);
    // for (int i = 0; i < size_pop + 1; i++)
    // {
    //     printf("%lf %i %i\n", nears_pop[i], index_pop[i], weight[i]);
    // }
    // printf("%i\n", choice);
    for (int i = 0; i < size_pop; i++)
    {
        if ( choice >= weight[i] && choice < weight[i + 1])
        {
            index = index_pop[i];
            // printf("%i %Lf\n", index_pop[i], (i + p)->gen[index_pop[i]]);
            break;
        }
    }
    return index;          
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

void mutation(double son[])
{
    int gen = rand() % size_gen;
    int choice;

    choice = rand() % 2;
    if ( choice == 1) son[gen] = ((rand() % RAND_MAX)); //pos
    else son[gen] = ((rand() % RAND_MAX) * (-1));       //neg
    son[gen] = son[gen] / (rand() % RAND_MAX);
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

void Dominant(Pop *p, double son[], int index)
{
    for (int i = 0; i < size_gen; i++)
    {
        (index + p)->gen[i] = son[i];
    }
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