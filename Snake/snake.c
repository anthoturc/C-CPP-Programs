/*
 * snake.c
 *
 * Author: Anthony Turcios 2019
 **/
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "snake.h"
#include "colors.h"

void
init_brd(snake *gsnek, apple *apel)
{
  /* Start set all values of the board to zero */
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      board[i][j] = 0;
    }
  }
  
  int offy = gsnek->y;
  int head = gsnek->head;
  int x = gsnek->x;
  for (int i = 0; i < head; ++i) {
    board[x][offy-head] = i+1;
    ++offy;
  }

  board[apel->x][apel->y] = apel->val;
}

snake *
init_snake()
{
  snake *gsnek;
  if ((gsnek = (snake *)malloc(sizeof(snake))) == NULL) {
    perror("snake: malloc in init_snake @ line 22\n");
  }

  gsnek->x = H/2;
  gsnek->y = W/2;
  
  /* These values can be tweaked depending 
   * on how big the snake should be to start
   **/
  gsnek->head = 5;
  gsnek->tail = 1;

  gsnek->mode = GAMEON; /* The game will be running to start */
  return gsnek;
}

apple *
init_apple()
{
  apple *apel;
  if ((apel = (apple *)(malloc(sizeof(apple)))) == NULL) {
    perror("snake: malloc in init_apple @ line 22\n");
  }

  /* Give the apple a random position in the board */
  apel->x = rand()%H;
  apel->y = rand()%W;
  apel->val = (int)'a';

  return apel;
}

void
print_brd(snake *gsnek, apple *apel)
{
  int i, j;
  /* Top section with coner*/
  bred();
  printf("%s", TLCON);
  for (j = 1; j < W; ++j) {
    printf("%s", HORZ);
  }
  printf("%s\n", TRCON);
  reset();

  /* Middle section with many spaces including 
   * the snake body
   **/
  for (i = 1; i <= H; ++i) {
    bred();
    printf("%s", VERT);
    reset();
    for (j = 1; j < W; ++j) {
      if (board[i][j] == 0) {
        printf(" ");
      } else if (board[i][j] == apel->val) {
        bgreen();
        printf("%s", APPLE);
        reset();
      } else {
        if (board[i][j] != gsnek->head) {
          bmagenta();
          printf("%s", BODY);
          reset();
        } else if (board[i][j] == gsnek->head) {
          bmagenta();
          printf("%s", HEAD);
          reset();
        }
      }
    }
    bred();
    printf("%s\n", VERT);
    reset();
  }

  /* Bottom section with corners*/
  bred();
  printf("%s", BLCON);
  for (j = 1; j < W; ++j) {
    printf("%s", HORZ);
  }
  printf("%s\n", BRCON);
  reset();
}

int
kbhit()
{
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  if (select(STDIN_FILENO+1, &fds, NULL, NULL, &tv) == -1) {
    perror("snake: select in kbhit @ line 115\n");
  }
  return FD_ISSET(STDIN_FILENO, &fds);
}

void
noblock(int state)
{
  struct termios ttystate;
  tcgetattr(STDIN_FILENO, &ttystate);
  if (state == NB_ENABLE) {
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_cc[VMIN] = 1;
  } else if (state == NB_DISABLE) {
    ttystate.c_lflag |= ICANON;
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int
main(int argc, char **argv)
{
  /* XXX: move this into a different function.
   *
   * Get he size of the terminal. Note that this
   * does handle resizing windows
   **/
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
    perror("snake: ioctl in main @ line 105\n");
  }


  clear();
  snake *gsnek = init_snake();
  apple *apel = init_apple();
  init_brd(gsnek, apel);

  /* Setup for key press events */
  int key;
  noblock(NB_ENABLE);

  /* game loop */
  while (gsnek->mode == GAMEON) {
    /* clear the screen and print the board from the origin */
    clear();
    goto(0, 0);
    print_brd(gsnek, apel);

    /* Check for keypress events */
    if (kbhit()) { /* key was pressed */
      key = getchar();
      switch (key) {
        case w:
          break;
        case s:
          break;
        case a:
          break;
        case d:
          break;
      }

    }
    /* move snake*/


    //XXX: what if COOL seconds is too long? try nanoseconds?
    sleep(COOLDOWN);
  }

  /* Show the 'GAME OVER!' Screen */
  clear();
  goto(ws.ws_row/2, ws.ws_col/2);
  bred();
  printf("GAME OVER!\n");
  reset();
  sleep(GAMEOVERTIME);
  clear();

  noblock(NB_DISABLE);

  free(gsnek);
  free(apel);
  return 0;
}

