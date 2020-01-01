#ifndef KNN_H
#define KNN_H

typedef struct node Node;
typedef struct element Element;

char *classificationClass(Node No_main[], Node *No_sub, int k, int trein_size);
double EuclideanDistance( Node main[], Node *sub, int i);
void QuickSort( Element v[], int began, int end);
void swap( Element v[], int i, int j);

#endif