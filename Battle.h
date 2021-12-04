/*By Toby McGuire*/
#ifndef BATTLE_H
#define BATTLE_H

#include "Enemy.h"
#include "GameUtils.h"
#include "string.h"
#include "WindowTools/Windows.h"

/*Initializes the battle window and post battle calculations*/
int BattleSelection();

/*Initializes the battle and operates the battle window*/
int Battle(WINDOW* window, int difficulty);

/*Simulates one round of combat, including getting input and calculating victory*/
void PlayOneRound(WINDOW* battleWindow, int* hightlight, int* win, int* battling, Enemy* enemy);

/*Checks input and chooses what to do in the battle
  Returns 1 if the player has ran away            */
int checkBattleChoice(int input, int *highlight, Enemy* enemy, WINDOW* battleWindow);

/*The player will deal points of damage randomly from 1 to their STR level*/
int PlayerAttack(WINDOW* battleWindow, Enemy *enemy);

/*Enemy attacks randomly [1,STR-1]*/
void EnemyAttack(WINDOW* battleWindow, Enemy *enemy);

/*Opens up the window to use and item*/
int UseItem(WINDOW* battleWindow, Enemy *enemy);

/*Checks to see if a choice was made, and applying the effects of the choice
  Returns 1 if an action was made, 0 otherwise								*/
int checkChoice(WINDOW* itemWindow, WINDOW* battleWindow,int itemToUse, int *madeChoice, char input);

/*Initializes and returns an enemy with an input difficulty*/
Enemy* CreateEnemy(int difficulty);

#endif
