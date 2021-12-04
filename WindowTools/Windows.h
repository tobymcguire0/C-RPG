/*By Toby McGuire*/
#ifndef WINDOWS_H
#define WINDOWS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Enemy.h"
#include "Colors.h"

/*Prints all the choices in the options array every 2 lines
  The option at index highlight-1 is bolded and is being pointed to*/
void printChoices(WINDOW *menuWindow, int highlight,char* options[], int numOptions);

/*Prints the menu window with all it's choices for input*/
void printMenu(WINDOW* menuWindow, int highlight,char* options[], int numOptions);

/*Prints the player's stats and waits for user input to quit*/
void printStats(WINDOW* statsWindow);

/*Prints info to the level up window to indicate the user can
  choose which stat to buff in the levelup                   */
void printLevelUp(WINDOW* lvlupWindow, int highlight, char* options[], int numOptions);

/*Prints the stat changes from leveling up*/
void printChangedStats(WINDOW* lvlupWindow, int oldDamage, int oldHealth);

/*Prints the battle screen options, with the index at highlight-1 being 
  indicated by a sword icon*/
void printBattle(WINDOW* battleWindow, int highlight, char* options[], int numOptions, Enemy *enemy);


/*Prints the map one character at a time to correctly color each piece*/
void printMap(WINDOW* mapWindow, char map[][40]);

/*Prints a character in the color specific in Colors.h*/
void printInColor(WINDOW* window, char toPrint, int locY, int locX);

/*Handles the shop window*/
void InShop(WINDOW* shopWindow);

/*Finalizes a purchase by adding it to the player's inventory and removing gold*/
void BuyItem(int item);

/*Alternative form of printChoices, but adds the price and decription of the item, 
  along with the player's currency                                                 */
void printShopChoices(WINDOW* window, int highlight, char* options[], int numOptions);

/*Prints the screen where the player chooses which item to use in battle*/
void printUseItemScreen(WINDOW* window,int highlight, char* itemOptions[], int numOptions);



#endif
