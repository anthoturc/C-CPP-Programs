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
#define NCLRS 8

typedef struct object
{
	int x, y,					/* used for movement */ 
		dir_x, dir_y;
	int clr;					/* used for color */
	char* body;				/* shape of the body */
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

	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);

	object_t *arr = init_objarr();
	while (1) {
		getmaxyx(stdscr, max_y, max_x);
		clear();
		
		attron(A_BOLD);
		for (int i = 0; i < NOBJS; ++i) {
			attron(COLOR_PAIR(arr[i].clr));
			mvprintw(arr[i].y, arr[i].x, arr[i].body);	
			attroff(COLOR_PAIR(arr[i].clr));
		}
		attroff(A_BOLD);

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
		arr[i].clr = (rand() % NCLRS) + 1;
		arr[i].dir_x = 1;
		arr[i].dir_y = 1;
		arr[i].body = "o";
	}

	return arr;
}