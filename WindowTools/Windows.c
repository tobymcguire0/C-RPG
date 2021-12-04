/*By Toby McGuire*/
#include "Windows.h"
#include "../GameUtils.h"


/*Prints all the choices in the options array every 2 lines
  The option at index highlight-1 is bolded and is being pointed to*/
void printChoices(WINDOW *window, int highlight, char* options[], int numOptions)
{
	int xOffset = 2, yOffset = 3, i;	
	
	for(i = 1; i <= numOptions; i++)
	{	
		if(highlight == i) 
		{	
			wattron(window, A_BOLD); 
			mvwprintw(window, yOffset, xOffset, "%s", options[i-1]);
			wattron(window, A_BLINK);
			mvwprintw(window, yOffset, xOffset+strlen(options[i-1])+1,"<--");
			wattroff(window,A_BLINK);
			wattroff(window, A_BOLD);
		} else {
			mvwprintw(window, yOffset, xOffset, "%s    ", options[i-1]);
		}
		yOffset+=2;
	}
	wrefresh(window);
}

/*Prints the menu window with all it's choices for input*/
void printMenu(WINDOW* menuWindow, int highlight,char* options[], int numOptions){
	box(menuWindow,0,0);
	mvwprintw(menuWindow, 1, MENUWIDTH/2-2, "Menu");
	mvwprintw(menuWindow,12, 1, "Arrow keys to select");
	mvwprintw(menuWindow,13,1, "Enter to choose");
	printChoices(menuWindow, highlight,options,numOptions);
}

/*Prints the player's stats and waits for user input to quit*/
void printStats(WINDOW* statsWindow){
	box(statsWindow, 0, 0);
	wattron(statsWindow, A_BOLD);
	mvwprintw(statsWindow, 1, SECONDARYWIDTH/2 - (strlen(player->name)>>1), "%s",player->name);
	wattroff(statsWindow, A_BOLD);

	mvwprintw(statsWindow, 2, 2 , "Level -----> ");
	mvwprintw(statsWindow, 2, 16, "%d",player->level);
	mvwprintw(statsWindow, 4, 2 , "XP --------> ");
	mvwprintw(statsWindow, 4, 16 , "%d",player->xp);
	mvwprintw(statsWindow, 6, 2 , "Health ----> ");
	mvwprintw(statsWindow, 6, 16 , "%d/%d",player->currentHealth,player->maxHealth);
	mvwprintw(statsWindow, 8, 2 , "Strength --> ");
	mvwprintw(statsWindow, 8, 16 , "%d", player->damage);
	mvwprintw(statsWindow, 10, 2 , "Gold -----> ");
	mvwprintw(statsWindow, 10, 16 , "%d",player->gold);
	wrefresh(statsWindow);
	while(wgetch(statsWindow) != 10);
}

/*Prints info to the level up window to indicate the user can
  choose which stat to buff in the levelup                   */
void printLevelUp(WINDOW* lvlupWindow, int highlight, char* options[], int numOptions){
	int i,xOffset = 4;
	box(lvlupWindow,0,0);
	mvwprintw(lvlupWindow,1,(POPUPWIDTH>>1)-4,"Level UP!");
	mvwprintw(lvlupWindow,3,(POPUPWIDTH>>1)-6,"Choose Buff:");
	for(i = 0; i<numOptions; i++){
		if(highlight==i){
			wattron(lvlupWindow, A_STANDOUT); 
			mvwprintw(lvlupWindow, 4, xOffset, "%s", options[i]);
			wattroff(lvlupWindow, A_STANDOUT);
		} else {
			mvwprintw(lvlupWindow, 4, xOffset, "%s", options[i]);
		}
		xOffset+=8;
	}
	wrefresh(lvlupWindow);
}

/*Prints the stat changes from leveling up*/
void printChangedStats(WINDOW* lvlupWindow, int oldDamage, int oldHealth){
	wclear(lvlupWindow);
	box(lvlupWindow,0,0);
	mvwprintw(lvlupWindow,1,(POPUPWIDTH>>1)-4,"Level UP!");
	mvwprintw(lvlupWindow,3,4,"HP  %d --> %d",oldHealth, player->maxHealth);
	mvwprintw(lvlupWindow,4,4,"STR %d --> %d",oldDamage,player->damage);
	wrefresh(lvlupWindow);
	while(wgetch(lvlupWindow) != 10);
}

/*Prints the battle screen options, with the index at highlight-1 being 
  indicated by a sword icon*/
void printBattle(WINDOW* battleWindow, int highlight, char* options[], int numOptions, Enemy *enemy){
	int xOffset = 2, yOffset = 6, i;	
	box(battleWindow, 0, 0);
	mvwprintw(battleWindow, 1, MENUWIDTH/2-((strlen(enemy->name)>>1)+3), "%s %d/%d   ",enemy->name,enemy->currentHealth,enemy->maxHealth);
	for(i = 1; i <= numOptions; i++)
	{	
		if(highlight == i) 
		{	
			wattron(battleWindow, A_BOLD); 
			mvwprintw(battleWindow, yOffset, xOffset, "%s", options[i-1]);
			wattron(battleWindow, A_BLINK);
			mvwprintw(battleWindow, yOffset, xOffset+strlen(options[i-1])+1,"<==|-");
			wattroff(battleWindow,A_BLINK);
			wattroff(battleWindow, A_BOLD);
		} else{
			mvwprintw(battleWindow, yOffset, xOffset, "%s      ", options[i-1]);
		}
		yOffset+=2;
	}
	wrefresh(battleWindow);
}

/*Prints the map one character at a time to correctly color each piece*/
void printMap(WINDOW* mapWindow, char map[][40]){
	int i,j;
	box(mapWindow,0,0);
	for(i=0;i<MAPHEIGHT;i++){
		for(j=0;j<MAPWIDTH;j++){
			printInColor(mapWindow,map[i][j],i+1,j+1);
		}
	}
	wattron(mapWindow,COLOR_PAIR(PLAYER_PAIR));
	mvwprintw(mapWindow,playerLocation[0],playerLocation[1],"*");
	wattroff(mapWindow,COLOR_PAIR(PLAYER_PAIR));
	wrefresh(mapWindow);
}

/*Prints a character in the color specific in Colors.h*/
void printInColor(WINDOW* window, char toPrint, int locY, int locX){
	switch (toPrint){
		case STEPPED:
		case GRASS:
			wattron(window,COLOR_PAIR(GRASS_PAIR)); break;
		case WATER:
			wattron(window,COLOR_PAIR(WATER_PAIR)); break;
		case ROCK:
			wattron(window,COLOR_PAIR(ROCK_PAIR)); break;
		case ITEM:
			wattron(window,COLOR_PAIR(ITEM_PAIR)); break;
		case PLAYER:
			wattron(window,COLOR_PAIR(PLAYER_PAIR)); break;
		case ENEMY:
			wattron(window,COLOR_PAIR(ENEMY_PAIR)); break;
		case TOWN:
			wattron(window,COLOR_PAIR(TOWN_PAIR)); break;
		default:
			break;
	}
	mvwprintw(window,locY,locX,"%c",toPrint);
	wattrset(window,A_NORMAL);

}

char* options[5] = {"Whetstone", "Reinforce", "Potion", "Super Potion", "Back"};
char* descriptions[5]={"Increases STR by 1    ", "Increases HP by 1     ", "Recovers up to 10HP     ", "Recovers 15HP      ", "Back to Town       "};
int price[5] = {5,5,10,20,0};

/*Handles the shop window*/
void InShop(WINDOW* shopWindow){
	int highlight = 1, input;
	printShopChoices(shopWindow, highlight, options, 5);
	while(1){
		input = wgetch(shopWindow);
		changeHighlight(input,&highlight,5);
		if(input == 10&&highlight!=5){
			if(player->gold>=price[highlight-1]){
				BuyItem(highlight-1);
				mvwprintw(shopWindow,14,1,"Bought %s       ",options[highlight-1]);
			} else {
				mvwprintw(shopWindow,14,1,"Not enough gold  ");
			}
		} else if(input == 10){
			break;
		} else {
			printShopChoices(shopWindow, highlight, options, 5);
		}
		wrefresh(shopWindow);
	}
}

/*Alternative form of printChoices, but adds the price and decription of the item, 
  along with the player's currency                                                 */
void printShopChoices(WINDOW* window, int highlight, char* options[], int numOptions){
	printChoices(window, highlight, options, numOptions);
	mvwprintw(window,2,(SHOPWIDTH>>1)-1, "$%d  ",player->gold);
	mvwprintw(window,13,1,"Cost: %d    ", price[highlight-1]);
	mvwprintw(window,14,1,"%s",descriptions[highlight-1]);
}

/*Finalizes a purchase by adding it to the player's inventory and removing gold*/
void BuyItem(int item){
	player->gold-=price[item];
	if(item<2){
		price[item] = (int)(price[item]*1.5);
		if(item){
			player->maxHealth++;
		} else {
			player->damage++;
		}
	} else {
		player->potionCounts[item-2]++;
	}
}

/*Prints the screen where the player chooses which item to use in battle*/
void printUseItemScreen(WINDOW* window, int highlight, char* itemOptions[], int numOptions){
	box(window,0,0);
	keypad(window,true);
	wattron(window,A_UNDERLINE);
	mvwprintw(window,1,(MENUWIDTH>>1)-2,"Items");
	wattroff(window,A_UNDERLINE);
	printChoices(window,highlight,itemOptions,numOptions);
	if(highlight == 3){
		mvwprintw(window,13,1,"Back to Battle ");
	} else {
		mvwprintw(window,13,1,"Available: %d  ", player->potionCounts[highlight-1]);
	}
}
