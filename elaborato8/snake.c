#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "snake.h"
#include "panel.h"

unsigned int righe;
unsigned int colonne;

enum direction { UP, DOWN, LEFT, RIGHT };

struct position {
	unsigned int i;
	unsigned int j;
};

struct snake {
	unsigned int max_length; // body array length
	unsigned int length;     // snake length
	struct position *body;   // snake array
};

/*
* Creates a snake's head in a world of size rows*cols;
*/
struct snake *snake_create(unsigned int rows, unsigned int cols)
{

	struct snake * snake_iniziale;
	snake_iniziale = (struct snake *) calloc(rows*cols, sizeof(struct snake));
	struct position * position_iniziale;
	position_iniziale = (struct position *) calloc(rows*cols, sizeof(struct position));
	srand(time(NULL));
	position_iniziale-> i = rand() % rows;
	position_iniziale-> j = rand() % cols;
	snake_iniziale-> body = position_iniziale;
	snake_iniziale->max_length = rows * cols;
	snake_iniziale->length = 1; 
	righe = rows;
	colonne = cols;
	return snake_iniziale;



}
/*
* Destroys the snake data structure.
*/
void snake_kill(struct snake *s)
{	
	 free(s->body);


}
/*
* Returns the (coordinates of the) snake's head.
*/
struct position snake_head(struct snake *s)
{
	return s->body[0];


}
/*
* Returns the (position of the) i-th part of the snake body.
*
* Position 0 is equivalento the snake's head. If the snake
* is shorter than i, the position returned is not defined.
*/
struct position snake_body(struct snake *s, unsigned int i)
{
	return s->body[i];


}
/*
* Returns 1 if the snake crosses himself, 0 otherwise.
*/
int snake_knotted(struct snake *s)
{
	int z;
	for (z = 1; z < (s->length); z++) {
		if ((s->body[0].i == s->body[z].i)&&(s->body[0].j ==s->body[z].j )) return 1;
	}

	return 0;

}
/*
* Moves the snake one step forward in the dir direction
* into a toroidal world of size rows*cols.
*/
void snake_move(struct snake *s, enum direction dir)
{
	snake_increase(s, dir);
	snake_decrease(s, 1);
}
/*
* Reverses the snake.
*
* The tail of the snake is now the new head.
*/
void snake_reverse(struct snake *s)
{
	int r;
	struct position scambio;
	unsigned int lunghezza = 0;
	lunghezza = (s->length );
	for(r=0 ; r<(lunghezza/2) ; r++)
	{
		scambio = s->body[r];
		s->body[r] = s->body[lunghezza - r -1];
		s->body[lunghezza - r - 1] = scambio;
	}

}
/*
* Increases the snake length.
*
* This is equivalent to:
* - add a new head in the dir direction wrt the old head.
*/
void snake_increase(struct snake *s, enum direction dir)
{	
	unsigned int newi=0;
	unsigned int newj=0;
	s->length = (s->length)+1;
	unsigned int w = s->length;
	
	while (0 < w)
	{
		s->body[w] = s->body[w - 1];
		w--;

	}
	if (dir == UP) 
	{
		newi = (s->body[0].i - 1 + righe) % righe;
		s->body[0].i = newi;
	}
	else if (dir == DOWN)
	{	
		newi= (s->body[0].i + 1 + righe) % righe;
		s->body[0].i = newi;
	}
	else if (dir == LEFT)
	{	
		newj = (s->body[0].j - 1 + colonne) % colonne;
		s->body[0].j = newj;

	}
	else if (dir == RIGHT)
	{	
		newj= (s->body[0].j + 1 + colonne) % colonne;
		s->body[0].j = newj;
	}
}
/*
* Removes from the tail of the snake decrease_len parts.
*/
void snake_decrease(struct snake *s, unsigned int decrease_len)
{
	s->length = s->length - decrease_len;
}

#endif
