#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "The_14_15_puzzle.h"

struct puzzle
{
    int matrix[size_puzzle][size_puzzle];
    int x, y;
};

int main()
{
    srand(time(NULL));
    Puzzle *p;
    p = creat_matrix();
    game(p);
}

void game(Puzzle *p)
{
    int w = 0;
    for (; w == 0;)
    {
        system("clear");
        viewer(p);
        command(p);
        w = win(p);        
    }
}

void command(Puzzle *p)
{
    search(p);
    int i = p->x;
    int j = p->y;

    int choice = 0;
    scanf("%i", &choice);
    do
    {
        if ( choice == 8 && i - 1 >= 0 && i - 1 < size_puzzle) move(p, i - 1, j);
        else if ( choice == 2 && i + 1 >= 0 && i + 1 < size_puzzle) move(p, i + 1, j);
        else if ( choice == 4 && j - 1 >= 0 && j - 1 < size_puzzle) move(p, i, j - 1);
        else if ( choice == 6 && j + 1 >= 0 && j + 1 < size_puzzle) move(p, i, j + 1);
        else choice == 0;
    } while ( choice == 0);
    
}

int win(Puzzle *p)
{
    int i, j, k = 0;
    for ( i = 0; i < size_puzzle; i++)
    {
        for ( j = 0; j < size_puzzle; j++)
        {
            k++;
            if (p->matrix[i][j] != k)
            {
                return 0;
            }
        }
    }
    return 1;
}

void move(Puzzle *p, int i, int j)
{
    int aux = p->matrix[i][j];
    p->matrix[i][j] = p->matrix[p->x][p->y];
    p->matrix[p->x][p->y] = aux;
}

int search(Puzzle *p)
{
    int i, j;
    for ( i = 0; i < size_puzzle; i++)
    {
        for ( j = 0; j < size_puzzle; j++)
        {
            if ( p->matrix[i][j] == 16) 
            {
                p->x = i;
                p->y = j;
                return 0;
            }
        }
    }
    return 1;
}

void viewer(Puzzle *p)
{
    printf("\t      The 14-15 Puzzle\n\n\n\n");
    int i, j;
    for ( i = 0; i < size_puzzle; i++)
    {
        for ( j = 0; j < size_puzzle; j++)
        {
            if ( p->matrix[i][j] == 16) printf("\t[  ] ");
            else if( p->matrix[i][j] < 10) printf("\t[0%i] ", p->matrix[i][j]);
            else printf("\t[%i] ", p->matrix[i][j]);
            
        }
        printf("\n\n");
    }
}

Puzzle* creat_matrix()
{
    int i;
    Puzzle *p = (Puzzle *) malloc(sizeof(Puzzle));
    int *array = (int *) malloc((MAX) * (sizeof(int)));
    for ( i = 0; i < MAX; i++)
    {
        *(array + i) = i + 1;
        // array[i] = i + 1;
    }
    shuffle(array);
    input(p, array);
    return p;
}

void shuffle(int array[])
{
    int i, j;
    for ( i = MAX - 1; i > 0; i--)
    {
        j = rand() % i;
        swap(array, i, j);
    }
}

void swap(int array[], int i, int j)
{
    int aux = array[i];
    array[i] = array[j];
    array[j] = aux;
}

void input(Puzzle *p, int v[])
{
    int i, j, k = 0;
    for ( i = 0; i < size_puzzle; i++)
    {
        for ( j = 0; j < size_puzzle; j++)
        {
            p->matrix[i][j] = v[k];
            k++;
        }
    }
}