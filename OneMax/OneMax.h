#ifndef _ONEMAX_
#define _ONEMAX_

#define size_gen 100
#define size_pop 50
#define size_torneio 20
#define generation 100
#define prob_mut 0.2
#define prob_cruz 0.7

void startPop( int pop[][size_gen]);
void viewerPop( int pop[][size_gen]);
int getScore( int individuo, int pop[][size_gen]);
void mutation( int son[][size_gen]);
void cross( int index_father1, int index_father2, int son[][size_gen], int pop[][size_gen]);
int getBest( int pop[][size_gen]);

#endif 