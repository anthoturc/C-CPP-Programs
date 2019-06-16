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
#include <time.h>

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
  gsnek->direction = RIGHT; /* Snake will move right to begin */
  return gsnek;
}

void
rand_apple(apple *apel)
{
  /* The apple should lie within the board */
  if (NAPPLES == 0) {
    srand(time(NULL));
    apel->x = 1 + rand()%(H-1);
    apel->y = 1 + rand()%(W-1);

    /* There is now one apple */
    NAPPLES = 1;
  }
}

apple *
init_apple()
{
  apple *apel;
  if ((apel = (apple *)(malloc(sizeof(apple)))) == NULL) {
    perror("snake: malloc in init_apple @ line 22\n");
  }

  /* Give the apple a random position in the board */  
  apel->val = APPLEVAL;
  rand_apple(apel);
  
  return apel;
}

void
print_brd(snake *gsnek, apple *apel)
{
  /* Put the apple on the board */
  board[apel->x][apel->y] = apel->val;

  int i, j;
  /* Top section with coner*/
  bred();
  printf("%s", TLCON);
  for (j = 1; j < W-1; ++j) {
    printf("%s", HORZ);
  }
  printf("%s\n", TRCON);
  reset();

  /* Middle section with many spaces including 
   * the snake body
   **/
  for (i = 1; i < H-1; ++i) {
    bred();
    printf("%s", VERT);
    reset();
    for (j = 1; j < W-1; ++j) {
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
  for (j = 1; j < W-1; ++j) {
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
move(snake *gsnek)
{ 
  /* Check for keypress events */
  int key = 0;
  if (kbhit()) { /* key was pressed */
    key = getchar();
    switch (key) {
      case UP:
        if (gsnek->direction != UP && gsnek->direction != DOWN) {
          --gsnek->x;
          gsnek->direction = UP;
          /* Check if snake crashed into itself */
          if (board[gsnek->x][gsnek->y] != 0 && board[gsnek->x][gsnek->y] != APPLEVAL) {
            return 1;
          }
        } else {
          key = 0;
        }
        break;
      case LEFT:
        if (gsnek->direction != LEFT && gsnek->direction != RIGHT) {
          --gsnek->y;
          gsnek->direction = LEFT;
          /* Check if snake crashed into itself */
          if (board[gsnek->x][gsnek->y] != 0 && board[gsnek->x][gsnek->y] != APPLEVAL) {
            return 1;
          }
        } else {
          key = 0;
        }
        break;
      case DOWN:
        if (gsnek->direction != DOWN && gsnek->direction != UP) {
          ++gsnek->x;
          gsnek->direction = DOWN;
          /* Check if snake crashed into itself */
          if (board[gsnek->x][gsnek->y] != 0 && board[gsnek->x][gsnek->y] != APPLEVAL) {
            return 1;
          }
        } else {
          key = 0;
        }
        break;
      case RIGHT:
        if (gsnek->direction != RIGHT && gsnek->direction != LEFT) {
          ++gsnek->y;
          gsnek->direction = RIGHT;
          /* Check if snake crashed into itself */
          if (board[gsnek->x][gsnek->y] != 0 && board[gsnek->x][gsnek->y] != APPLEVAL) {
            return 1;
          }
        } else {
          key = 0;
        }
        break;
    }
  }

  /* XXX: does this need to be here?
   * My idea was to use this to avoid filling 
   * putting things into the `stdin' buffer.
   *
   * So pressing 'S' 3 times will not have any effect
   * I could move fflush to the game loop
   **/
  fflush(stdin);

  /* The head should keep moving */
  if (key == 0) {
    if (gsnek->direction == DOWN) {
      ++gsnek->x;
    } else if (gsnek->direction == UP) {
      --gsnek->x;
    } else if (gsnek->direction == LEFT) {
      --gsnek->y;
    } else { /* direction is RIGHT */
      ++gsnek->y;
    }
  }
  
  /* Snake crashed into itself */
  if (board[gsnek->x][gsnek->y] != 0 && board[gsnek->x][gsnek->y] != APPLEVAL) {
    return 1;
  }
  
  ++gsnek->head;
  board[gsnek->x][gsnek->y] = gsnek->head;

  return 0;
}

int
check_collision(snake *gsnek, apple *apel)
{
  int sx = gsnek->x, sy = gsnek->y;
  if (apel == NULL) { /* Check wall collision */
    if (gsnek->direction == UP) {
      if (sx+1 == H || sx == H) return 1;
    } else if (gsnek->direction == DOWN) {
      if (sx-1 == -1 || sx == -1) return 1;
    } else if (gsnek->direction == LEFT) {
      if (sy-1 == -1 || sy == -1) return 1;
    } else { /* Moving RIGHT */
      if (sy+1 == W || sy == W) return 1;
    }
    return 0;
  }

  /* Check if snake ate apple */
  int ax = apel->x, ay = apel->y;
  int ate = sx == ax && sy == ay;
  return ate;
}

void
rem_up_tail(snake *gsnek)
{
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      if (board[i][j] == gsnek->tail) {
        board[i][j] = 0;
      }
    }
  }
  ++gsnek->tail;
}

int
main(int argc, char **argv)
{
  /* XXX: move this into a different function.
   *
   * Get he size of the terminal. Note that this
   * does not handle resizing windows
   **/
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
    perror("snake: ioctl in main @ line 105\n");
  }

  /* Set up for game */
  clear();
  snake *gsnek = init_snake();
  apple *apel = init_apple();
  init_brd(gsnek, apel);

  /* Setup for key press events that are non blocking */
  noblock(NB_ENABLE);

  /* game loop */
  while (gsnek->mode == GAMEON) {
    /* clear the screen */
    clear();

    /* Print board from origin */  
    goto(0, 0);
    print_brd(gsnek, apel);

    /* Move snake */
    if (move(gsnek) == 1) {
      sleep(CRASHED);
      break;
    }

    /* Remove and update last piece of tail */
    rem_up_tail(gsnek);

    /* Check if snake ate apple */
    if (check_collision(gsnek, apel)) {
      gsnek->tail -= UPDATELEN;
      /* There should be no apples on board now*/ 
      NAPPLES = 0;
      /* Old apple position should be empty*/
      board[apel->x][apel->y] = 0;
      /* Make a new apple somewhere else */
      rand_apple(apel);
    }

    /* 
     * Wait `COOLDOWN' microseconds so that
     * the game does not move too fast. The printing 
     * looks bad without this 
     * */
    usleep(COOLDOWN);
  }

  /* Show the 'GAME OVER!' Screen */
  clear();
  goto(ws.ws_row/2, ws.ws_col/2);
  bred();
  printf("GAME OVER!\n");
  reset();
  sleep(GAMEOVERTIME);
  clear();

  /* Clean up */
  noblock(NB_DISABLE);
  free(gsnek);
  free(apel);

  return 0;
}

