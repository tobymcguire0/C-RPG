/*By Toby McGuire*/
#ifndef COLORS_H
#define COLORS_H

#include <ncurses.h>

#define COLOR_BROWN 8

#define GRASS ' '
#define STEPPED '.'
#define WATER '~'
#define ROCK 'X'
#define PLAYER '*'
#define ENEMY 'E'
#define ITEM '$'
#define TOWN '%'

#define STEPPED_PAIR 1
#define GRASS_PAIR 1
#define WATER_PAIR 2
#define ROCK_PAIR 3
#define ENEMY_PAIR 4
#define ITEM_PAIR 5
#define TOWN_PAIR 6
#define PLAYER_PAIR 7

void InitializeColors();

#endif
