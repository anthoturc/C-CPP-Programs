/*
 * snake.h
 *
 * Author: Anthony Turcios 2019
 **/
#ifndef _SNAKE_H_
#define _SNAKE_H_

/* 
 * Macros that determine if stdin 
 * is in canonical mode or not
 **/
#define NB_ENABLE 1
#define NB_DISABLE 0

/* Macros for game over and game start */
#define GAMEOVER 0
#define GAMEON 1

/*
 * Macro that specifies how long the game over screen will be shown
 **/
#define GAMEOVERTIME 2

/* 
 * Constant to determine how long to wait (seconds) for game to sleep.
 * This is used to reduce the number of times the board is
 * printed. Otherwise it is too fast.
 **/
const unsigned int COOLDOWN = 1;

/* `W' serves as the width for the 'field of play' or game area */
#define W 40 

/* `H' serves as the height for the 'field of play' or game area */
#define H 20

/* `board' serves as the logical game board where the snake will live */
int board[H][W];

/* 
 * `snake' is a struct that maintains the x,y 
 * position in the board and the values of the 
 * head and tail. `head' and `tail' are used to 
 * determine the length of the snake. 
 * `mode' is used to determine if the snake is moving,
 * i.e. if the game is continuing or not.
 **/
typedef struct snake {
  int x;
  int y;
  int head;
  int tail;
  int mode;
  int direction;
} snake;

/*
 * The following macros define what the snake will look like
 * using the unicode values for them. The head is darker than
 * the body so that the two are distinguishible
 **/
#define HEAD "\u2593"
#define BODY "\u2592"

/*
 * `apple' will hold the current position of
 * the apple to be displayed on the board.
 * */
typedef struct apple {
  int x;
  int y;
  int val;
} apple;

#define APPLE "\u2587"

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

/*
 * These macros allow for control of the cursor. They can
 * be used to sepcify where things should be printed! And 
 * used to clear the screen.
 **/
#define clear() printf("\033[H\033[J")
#define goto(x,y) printf("\033[%d;%dH", (x), (y))

/*
 * The following macros are used for
 * keypresses
 **/
#define w 119
#define a 97
#define s 115
#define d 100

#endif /* _SNAKE_H_ */



