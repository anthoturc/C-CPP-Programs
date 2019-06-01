#include <stdio.h>
#include <stdlib.h>

#include "snake.h"


void
init_brd(snake *gsnek)
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
  return gsnek;
}

void
print_brd(snake *gsnek)
{
  int i, j;
  /* Top section with coner*/
  printf("%s", TLCON);
  for (j = 1; j < W; ++j) {
    printf("%s", HORZ);
  }
  printf("%s\n", TRCON);

  /* Middle section with many spaces including 
   * the snake body
   **/
  for (i = 1; i <= H; ++i) {
    printf("%s", VERT);
    for (j = 1; j < W; ++j) {
      if (board[i][j] == 0) {
        printf(" ");
      } else {
        if (board[i][j] != gsnek->head) {
          printf("%s", BODY);
        } else if (board[i][j] == gsnek->head) {
          printf("%s", HEAD);
        }
      }
    }
    printf("%s\n", VERT);
  }

  /* Bottom section with corners*/
  printf("%s", BLCON);
  for (j = 1; j < W; ++j) {
    printf("%s", HORZ);
  }
  printf("%s\n", BRCON);

}




int
main(int argc, char **argv)
{
  snake *gsnek = init_snake();
  init_brd(gsnek);
  print_brd(gsnek);
  return 0;
}
