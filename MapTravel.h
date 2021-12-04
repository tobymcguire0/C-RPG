/*By Toby McGuire*/
#ifndef MAPTRAVEL_H
#define MAPTRAVEL_H
#include "GameUtils.h"
#include "Battle.h"
#include "WindowTools/Windows.h"

/*Creates the map window and gameplay loop*/
void EnterMap();

/*Moves the character on the screen, checking collisions
  Returns 0 if player entered a town				*/
int moveCharacter(WINDOW* window);

/*Prints the player's position and previous position on the screen*/
void getInputToMove(WINDOW* window);

/*Waits for user input, then moves the player in the input direction*/
void printPlayerStep(WINDOW* window, int oldX, int oldY);

/*Used to see what the player ran into, if anything, and deal with it*/
char* detectCollisions(WINDOW* mapWindow, int oldY, int oldX);

/*Handles if the player collided with an enemy*/
char* enemyCollision(WINDOW* mapWindow);



#endif
