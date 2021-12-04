/*By Toby McGuire*/
#include "Colors.h"
void InitializeColors(){
    start_color();
    init_color(COLOR_BROWN, 218,165,32);
    init_pair(GRASS_PAIR, COLOR_YELLOW, COLOR_GREEN);
    init_pair(WATER_PAIR, COLOR_CYAN, COLOR_BLUE);
    init_pair(ROCK_PAIR, COLOR_BROWN, COLOR_GREEN);
    init_pair(PLAYER_PAIR, COLOR_BLACK, COLOR_CYAN);
    init_pair(ENEMY_PAIR, COLOR_BLACK, COLOR_RED);
    init_pair(ITEM_PAIR, COLOR_BLACK, COLOR_YELLOW);
    init_pair(TOWN_PAIR, COLOR_BLACK, COLOR_GREEN);
}
