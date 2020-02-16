#ifndef _THE_14_15_PUZZLE_
#define _THE_14_15_PUZZLE_

#define size_puzzle 4
#define MAX 16 // size_puzzle * size_puzzle

typedef struct puzzle Puzzle;

Puzzle* creat_matrix();
void shuffle(int array[]);
void swap(int array[], int i, int j);
void input(Puzzle *p, int v[]);

void game(Puzzle *p);
void command(Puzzle *p);
void viewer(Puzzle *p);
void move(Puzzle *p, int i, int j);
int search(Puzzle *p);
int win(Puzzle *p);

#endif