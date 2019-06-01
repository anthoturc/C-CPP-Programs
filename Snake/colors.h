/*
 * colors.h
 *
 * Author: Anthony Turcios 2019
 **/

#ifndef _COLORS_H_
#define _COLORS_H_

#define red() printf("\033[0;31m")   
#define green() printf("\033[0;32m")
#define yellow() printf("\033[0;33m")
#define blue() printf("\033[0;34m")
#define magenta() printf("\033[0;35m")
#define cyan() printf("\033[0;36m")

#define bred() printf("\033[1;31m")   
#define bgreen() printf("\033[1;32m")
#define byellow() printf("\033[1;33m")
#define bblue() printf("\033[1;34m")
#define bmagenta() printf("\033[1;35m")
#define bcyan() printf("\033[1;36m")

#define reset() printf("\033[0m")

#endif /* _COLORS_H_ */
