/*
 * ball.c
 * 
 * Author: Anthony Turcios
 **/

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DELAY 30000
#define NOBJS 20

typedef struct object
{
	int x, y, 
		dir_x, dir_y;
	char* body;
} object_t;

object_t* init_objarr();

int
main(int argc, char **argv)
{
	srand(time(NULL));
	int max_x = 0,
		max_y = 0;

	initscr();
	noecho();
	curs_set(FALSE);

	object_t *arr = init_objarr();
	while (1) {
		getmaxyx(stdscr, max_y, max_x);
		clear();
		
		for (int i = 0; i < NOBJS; ++i) {
			mvprintw(arr[i].y, arr[i].x, arr[i].body);	
		}

		refresh();
		usleep(DELAY);
		
		for (int i = 0; i < NOBJS; ++i) {
			if (arr[i].x + arr[i].dir_x >= max_x 
				|| arr[i].x + arr[i].dir_x < 0) {
				arr[i].dir_x *= -1;
			} else {
				arr[i].x += arr[i].dir_x;
			}

			if (arr[i].y + arr[i].dir_y >= max_y 
				|| arr[i].y + arr[i].dir_y < 0) {
				arr[i].dir_y *= -1;
			} else {
				arr[i].y += arr[i].dir_y;
			}
		}
	}

	endwin();
}

object_t* 
init_objarr()
{
	int max_x = 0, 
		max_y = 0;

	getmaxyx(stdscr, max_y, max_x);
	object_t *arr = (object_t *)malloc(NOBJS*sizeof(object_t));
	if (arr == NULL) {
		printf("malloc error\n");
		exit(1);
	}
	
	for (int i = 0; i < NOBJS; ++i) {
		arr[i].x = rand() % (max_x + 1);
		arr[i].y = rand() % (max_y + 1);
		arr[i].dir_x = 1;
		arr[i].dir_y = 1;
		arr[i].body = "o";
	}

	return arr;
}