/*By Toby McGuire*/
#ifndef PLAYER_H
#define PLAYER_H

#include "GameUtils.h"
#include <string.h>
#include "WindowTools/Windows.h"
#include "Enemy.h"

typedef struct{
    char name[100];
    int level;
    int xp;
    int xpToNextLevel;
    int damage;
    int maxHealth;
    int currentHealth;
    int gold;
    int potionCounts[2];
} Player;

Player *player;
int playerLocation[2];

/*Creates a player with default stats and a provided name*/
void createNewPlayer(char* name);

/*Adds xp to the player's xp count*/
void gainXP(int amount, int popup);

/*Calculates and returns the needed amount of xp to reach the next level*/
int XpToNextLevel();

/*Levels a player up, healing them and giving their stats a boost*/
void levelUp(int popup);

/*Heals the player a specified amount*/
void Heal(int amount);

/*Adds a random item to the player's inventory and returns the pickup message*/
char* PickupItem();

#endif
