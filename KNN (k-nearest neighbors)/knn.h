#ifndef KNN_H
#define KNN_H

typedef struct node Node;
typedef struct element Element;

char *classificationClass(Node No_main[], Node *No_sub, int k, int trein_size, int indice);
long double EuclideanDistance( Node main[], Node *sub, int i);
void QuickSort( Element v[], int began, int end);
void InserctionSort( Element v[], int size);
void SelectionSort( Element v[], int size);
void swap( Element v[], int i, int j);
void input( Node No[], int size);


#endif