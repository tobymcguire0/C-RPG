/*By Toby McGuire*/
#include "Player.h"

/*Creates a player with default stats and a provided name*/
void createNewPlayer(char* name){
	player = calloc(1, sizeof(Player));
	strcpy(player->name, name);
	player->level = 1;
	player->damage = 1;
	player->maxHealth = 5;
	player->currentHealth = 5;
	player->gold = 5;
	player->potionCounts[0] = 0;
	player->potionCounts[1] = 0;
}


/*Calculates and returns the needed amount of xp to reach the next level*/
int XpToNextLevel(){
	int level = player->level;
	return 10 + 2*level*level;
}

/*Adds xp to the player's xp count*/
void gainXP(int amount, int popup){
	int newXp = player->xp + amount, needed = XpToNextLevel(player->level);
	while(newXp>=needed){
		newXp-=needed;
		levelUp(popup);
	}
	player->xp = newXp;
}

char* lvlUpOptions[] = {"HP", "STR"};

/*Levels a player up, healing them and giving their stats a boost*/
void levelUp(int popup){
	int input, highlight=0,oldDamage = player->damage, oldHealth = player->maxHealth;
	WINDOW* lvlupWindow;
	player->level++;
	player->damage += 1;
	player->maxHealth +=1;
	if(popup){
		lvlupWindow = newwin(POPUPHEIGHT,POPUPWIDTH,MENUHEIGHT,0);
		printLevelUp(lvlupWindow, highlight,lvlUpOptions,2);
		while(1){
			input = wgetch(lvlupWindow);
			if(input>=67&&input<=70){
				highlight = !highlight;
			}
			if(input==10){
				if(highlight){
					player->damage++;
				} else {
					player->maxHealth++;
				}
				break;
			}
			printLevelUp(lvlupWindow, highlight, lvlUpOptions,2);
		
		}
	printChangedStats(lvlupWindow,oldDamage,oldHealth);
	werase(lvlupWindow);
	wrefresh(lvlupWindow);
	delwin(lvlupWindow);
	}
	player->currentHealth = player->maxHealth;
}

/*Heals the player a specified amount*/
void Heal(int amount){
	player->currentHealth += amount;
	if(player->currentHealth > player->maxHealth){
		player->currentHealth = player->maxHealth;
	}
}


char* PickupItem(){
	int random = rand()%10;
	if(random<5){
	player->gold += 5;
	return "Picked up 5 gold         ";
	} else if(random<8){
	player->potionCounts[0]++;
	return "Picked up a Potion       ";
	} else {
	player->potionCounts[1]++;
	return "Picked up a Super Potion!";
	}
}
