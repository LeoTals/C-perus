#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "aaltogame.h"

GameArea *createGameArea(unsigned int x_size, unsigned int y_size)
{
	//printf("%d,%d\n",x_size,y_size);
	GameArea *newgame = calloc(1, sizeof(GameArea));
	newgame->cells = calloc(y_size+1,sizeof(CellStatus*));
	newgame->x_size = x_size;
	newgame->y_size = y_size;
	for(int i = 0;i<y_size;i++)
	{
		newgame->cells[i] = calloc(x_size+1,sizeof(CellStatus));
		for(int j = 0;j<x_size;j++){newgame->cells[i][j] = DEAD;}
	}
	return newgame;
}

int checkneighbor(GameArea *table, int y,int x)
{
	int num = 0;
	if ((y<0)||(x<0)||(x>=table->x_size)||(y>=table->y_size)){
		return 0;
	}
	if (table->cells[y][x] == ALIVE){
		num = 1;
	}
	else{ num = 0;}
	//printf("%d, %d - %d |",x,y,num);
	return num;
}

void releaseGameArea(GameArea *a)
{
	for (int i=0;i<a->y_size;i++){
		free(a->cells[i]);
	}
	free(a->cells);
	free(a);
}

void initGameArea(GameArea *a, unsigned int n)
{
	//printf("starting with %u cells\n",n);
	int row = 0;
	int column = 0;
	unsigned int born;
	unsigned int cellno = a->y_size * a->x_size;
	for (int i = 0;i<n;i++){
		born = rand();
		born = born%cellno;
		row = born / a->x_size;
		column = born % a->x_size;
		if (row == a->y_size){
			if (a->cells[a->y_size][a->x_size] == ALIVE){
				i--;
				continue;
			}
			a->cells[a->y_size][a->x_size] = ALIVE;
		}
		else{
			if(a->cells[row][column] == ALIVE){
				i--;
				continue;
			}
			a->cells[row][column] = ALIVE;
		}
		
	}
}
void printGameArea(const GameArea *a){
	for(int i = 0;i<a->y_size;i++){
		for(int j = 0;j<a->x_size;j++){
			if (a->cells[i][j] == ALIVE){
				printf("*");
			}
			else{
				printf(".");
			}
		}
	printf("\n");
	}
	
}


void gameTick(GameArea *a){
	GameArea *last_tick = createGameArea(a->x_size,a->y_size);
	for (int c = 0; c<a->y_size;c++){
		for (int b = 0; b<a->x_size;b++){
			last_tick->cells[c][b] = a->cells[c][b];
		}
	}
	//printf("allocated %d to last_tick\n",sizeof(GameArea)); //test
	//printGameArea(last_tick);
	int neighbors = 0;
	for (int i = 0; i<a->y_size;i++){
		for (int j = 0;j<a->x_size;j++){
			//printf("coordinates (%d,%d)\n",j,i);
			neighbors = 0;
				neighbors += checkneighbor(last_tick,i-1,j);
				neighbors += checkneighbor(last_tick,i-1,j-1);
				neighbors += checkneighbor(last_tick,i-1,j+1);
				neighbors += checkneighbor(last_tick,i+1,j);
				neighbors += checkneighbor(last_tick,i+1,j-1);
				neighbors += checkneighbor(last_tick,i+1,j+1);
				neighbors+=checkneighbor(last_tick,i,j-1);
				neighbors+=checkneighbor(last_tick,i,j+1);

			if(last_tick->cells[i][j] == ALIVE){
				if(neighbors == 2 || neighbors == 3){
					a->cells[i][j] = ALIVE;
				}
				else{
					a->cells[i][j] = DEAD;
				}
			}
			else{
				if(neighbors == 3){
					a->cells[i][j] = ALIVE;
				}
			}
			/*printf("Cell is now ");
			if (a->cells[i][j] == ALIVE){printf("alive.\n");
			}
			else {printf("dead.\n");}*/
		}
	}
	releaseGameArea(last_tick);
}

/*int main(void)
{
     Feel free to modify this function to test different things 

    // re-seed random number generator
    srand((unsigned)time(NULL));

    GameArea *a = createGameArea(50,20);
    initGameArea(a, 150);

    // how many iterations we want
    int rounds = 80;

    // loop iterations, cancel with ctrl-c
    for(int i=0; i<rounds; i++) {
        printf("\nGeneration: %d\n", i+1);
        printGameArea(a);
        // slow down iterations
        sleep(1);
        gameTick(a);
    }
    releaseGameArea(a);
    return 0;
}*/