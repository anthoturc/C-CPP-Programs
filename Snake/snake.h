#ifndef _CONSTS_H_
#define _CONSTS_H_

/* `W' serves as the width for the 'field of play' or game area */
#define W 40 

/* `H' serves as the height for the 'field of play' or game area */
#define H 20

/* `board' serves as the logical game board where the snake will live */
int board[H][W];

typedef struct snake {
  int x;
  int y;
  int head;
  int tail;
} snake;

/*
 * The following macros define what the snake will look like
 * using the unicode values for them. The head is darker than
 * the body so that the two are distinguishible
 **/

#define HEAD "\u2593"
#define BODY "\u2592"


/*
 * The following unicode values are used for making the board that
 * are used to print a square. The extend set of ascii characters 
 * could have been used here, but it is not reliable imo.
 **/

#define TLCON "\u2554" /* Top left corner */
#define TRCON "\u2557" /* Top right corner */
#define BLCON "\u255A" /* Bottom left corner */
#define BRCON "\u255D" /* Bottom right corner */
#define VERT "\u2551" /* Vertical section */  
#define HORZ "\u2550" /* Horizontal section */

#endif /* _CONSTS_H_ */
