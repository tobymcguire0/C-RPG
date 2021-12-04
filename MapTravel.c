/*By Toby McGuire*/
#include "MapTravel.h"
extern char* currentSavePath;
extern char Map00[][40];

/*Creates the map window and gameplay loop*/
void EnterMap(){
	WINDOW* mapWindow = newwin(MAPHEIGHT+3,MAPWIDTH+1,0,MENUWIDTH);
	int inMap = 1;
	keypad(mapWindow,TRUE);
	printMap(mapWindow,Map00);
	while(inMap){
		inMap = moveCharacter(mapWindow);
		wrefresh(mapWindow);
	}
	werase(mapWindow);
	wrefresh(mapWindow);
	delwin(mapWindow);
}

/*Moves the character on the screen, checking collisions
  Returns 0 if player entered a town				*/
int moveCharacter(WINDOW* window){
	int oldX = playerLocation[1], oldY = playerLocation[0];
	int inMap = 1;
	char* info = "";
	getInputToMove(window);
	info = detectCollisions(window,oldY,oldX);
	inMap = strcmp(info,"town");
	if(inMap){
		mvwprintw(window,13,1,"%s",info);
		printPlayerStep(window,oldX,oldY);
		wrefresh(window);
	}
	return inMap;
}

/*Prints the player's position and previous position on the screen*/
void printPlayerStep(WINDOW* window, int oldX, int oldY){
	if(oldX!=playerLocation[1]||oldY!=playerLocation[0]){
		wattron(window,COLOR_PAIR(STEPPED_PAIR));
		mvwprintw(window,oldY,oldX,"%c",STEPPED);
		wattroff(window,COLOR_PAIR(STEPPED_PAIR));
		wattron(window,COLOR_PAIR(PLAYER_PAIR));
		mvwprintw(window,playerLocation[0],playerLocation[1],"%c",PLAYER);
		wattroff(window,COLOR_PAIR(PLAYER_PAIR));
		Map00[playerLocation[0]-1][playerLocation[1]-1] = ' ';
		Map00[oldY-1][oldX-1] = ' ';
	}
}

/*Waits for user input, then moves the player in the input direction*/
void getInputToMove(WINDOW* window){
	int input = wgetch(window);
	switch(input){
		case KEY_LEFT:
			playerLocation[1]-=2;
			break;
		case KEY_RIGHT:
			playerLocation[1]+=2;
			break;
		case KEY_UP:
			playerLocation[0]--;
			break;
		case KEY_DOWN:
			playerLocation[0]++;
			break;
		default:
			break;
	}
}

/*Used to see what the player ran into, if anything, and deal with it*/
char* detectCollisions(WINDOW* mapWindow,int oldY, int oldX){
	int nextSpace = Map00[playerLocation[0]-1][playerLocation[1]-1];
	char* collisionInfo = "";
	switch (nextSpace){
		case TOWN:
			playerLocation[1] = oldX;
			playerLocation[0] = oldY;
			Save(currentSavePath);
			collisionInfo = "town"; /*Fallthrough*/
		case ROCK:
		case WATER:
			playerLocation[1] = oldX;
			playerLocation[0] = oldY;
			break;  
		case ENEMY:
			collisionInfo = enemyCollision(mapWindow);
			break;
		case ITEM:
			collisionInfo = PickupItem();
			gainXP(5,1);
			Save(currentSavePath);
			break;	    
		default:
			break;
	}
	return collisionInfo;
}
/*Handles if the player collided with an enemy*/
char* enemyCollision(WINDOW* mapWindow){
	if(BattleSelection()){
		Save(currentSavePath);
		printMap(mapWindow, Map00);
		return "";
	} else {
		player->currentHealth = player->maxHealth;
		player->gold -=5;
		if(player->gold<0){
			player->gold =0;
		}
		playerLocation[1] = 17;
		playerLocation[0] = 11;
		return "town";
	}
}
