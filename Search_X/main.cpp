#include "Search_X.h"

int main()
{
    srand(time(NULL));
    Pop *p;
    p = startPop();

    for (int i = 0; i < generation; i++)
    {
        printf("Generation %i...", i);
        int index_best = getBest(p);
        double array_best[size_gen];
        conversion_StrctForVector(p, array_best, index_best);
        double score_best = getScore(array_best);
        double x = 0;
        for (int i = 0; i < size_gen; i++)
        {
            if ( array_best[i] > 0) printf(" %.1lf ", array_best[i]);
            else printf("%.1lf ", array_best[i]);
            x = x + array_best[i];
        }
        printf("\tx = %.1lf  y = %lf\n", x, score_best);
        if ( score_best >= (double)value && score_best < ((double)value + 0.0001))
        {
            printf("Solucao otima: %lf\n", x);
            break;
        }
        // viewerPop(p);
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
                    index_xx = selectionByRating(p, index_xy);
                    index_xy = selectionByRating(p, index_xy);
                } while ( index_xy == index_xx || index_xy == elitism || index_xx == elitism);

                double son[size_gen] = {0};
                cross(p, index_xx, index_xy, son);

                double prob = (double)rand() / ((double)RAND_MAX + 1);
                if ( prob < prob_mutation) mutation(son);
                

                double v_xx[size_gen], v_xy[size_gen];
                conversion_StrctForVector(p, v_xx, index_xx);
                conversion_StrctForVector(p, v_xy, index_xy);

                double score_xx = getScore(v_xx);
                double score_xy = getScore(v_xy);
                double score_son = getScore(son);

                double nears_xx = howClose(score_xx);
                double nears_xy = howClose(score_xy);
                double nears_son = howClose(score_son);

                if ( nears_xx > nears_xy && nears_xx > nears_son) Dominant(p, son, index_xx);
                else if ( nears_xy > nears_xx && nears_xy > nears_son) Dominant(p, son, index_xy);
            }
        }
    }
    return 0;
}