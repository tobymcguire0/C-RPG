/*By Toby McGuire*/
#ifndef GAME_UTILS_H
#define GAME_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Player.h"
#include "MapTravel.h"
#include "WindowTools/Colors.h"
#include <curses.h>

#define MENUWIDTH 27
#define MENUHEIGHT 15
#define SECONDARYWIDTH 30
#define SECONDARYHEIGHT 15
#define SHOPWIDTH 35
#define SHOPHEIGHT 16
#define POPUPWIDTH 20
#define POPUPHEIGHT 7
#define MAPWIDTH 40
#define MAPHEIGHT 12

/*Lets the user make a choice from [1,numChoices] and returns the decremented value between [0,numChoices-1]*/
int Choose(int numChoices);

/*
Save files save each part of the player's state on different lines
0: Player Name
1: Level
2: XP
3/4: Max Health /  Current Health
5: Damage
6: Gold
7/8: LocationX/Y
9/10: # Potions
The rest is the saved map
*/
void Save(char *savePath);

/*Reads in the save data and returns a corresponding player*/
void ReadSaveData(FILE* saveFile);

/*Switches the highlight up or down depending on the input and number of choices given*/
void changeHighlight(int c, int *highlight,int numChoices);

#endif
