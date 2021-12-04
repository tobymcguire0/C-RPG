/*By Toby McGuire*/
#include "Battle.h"

/*Invisible winstreak to make the enemies get harder the better the player is doing*/
int winstreak = 0;

char* enemyNames[] = {"Wolf", "Zombie", "Dragon", "Bandit", "Duck"};
char* battleOptions[] = {"Attack", "Item", "Run"};
int (*actionOptions[2])() = {PlayerAttack,UseItem};

/*Initializes the battle window and post battle calculations*/
int BattleSelection(){
	int win;
	WINDOW *battleWindow = newwin(MENUHEIGHT,MENUWIDTH,0,0);
	refresh();
	keypad(battleWindow,TRUE);
	win = Battle(battleWindow,player->level + ((player->damage)>>1) + winstreak);
	if(win){
		winstreak++;
	} else {
		winstreak = 0;
	}
	werase(battleWindow);
	wrefresh(battleWindow);
	delwin(battleWindow);
	return win;
}

/*Initializes the battle and operates the battle window*/
int Battle(WINDOW* battleWindow, int difficulty){
	Enemy* enemy = CreateEnemy(difficulty);
	int battling = 1, highlight=1, win = 0;
	printBattle(battleWindow, highlight,battleOptions,3,enemy);
	mvwprintw(battleWindow,3,1,"A %s stands", enemy->name);
	mvwprintw(battleWindow,4,1,"menacingly in your path");
	mvwprintw(battleWindow,13,1,"HP: %d/%d        ",player->currentHealth, player->maxHealth);
	while(battling){
		PlayOneRound(battleWindow, &highlight, &win, &battling, enemy);
	}
	while(wgetch(battleWindow)!=10);
	free(enemy);
	return win;
}

/*Simulates one round of combat, including getting input and calculating victory*/
void PlayOneRound(WINDOW* battleWindow, int* highlight, int* win, int* battling, Enemy* enemy){
	int input = wgetch(battleWindow);
	changeHighlight(input,highlight,3);
	if(checkBattleChoice(input, highlight,enemy, battleWindow)){
		*battling = 0;
		return;
	}
	printBattle(battleWindow, *highlight,battleOptions,3,enemy);
	*win = enemy->currentHealth<=0;
	*battling = !*win && player->currentHealth>0;
	if(!*win && !*battling){
		mvwprintw(battleWindow,13,1,"You Died...");
	} else if(*win){
		mvwprintw(battleWindow,13,1,"Gained %d XP, %d Gold",enemy->xp, enemy->gold);
		gainXP(enemy->xp,1);
		player->gold+=enemy->gold;
	}
}

/*Checks input and chooses what to do in the battle
  Returns 1 if the player has ran away            */
int checkBattleChoice(int input, int *highlight, Enemy* enemy, WINDOW* battleWindow){
	if(input==10){
			if(*highlight!=3){
				if(actionOptions[*highlight-1](battleWindow, enemy) && enemy->currentHealth>0){
					EnemyAttack(battleWindow, enemy);
				}
				mvwprintw(battleWindow,13,1,"HP: %d/%d        ",player->currentHealth, player->maxHealth);
			} else {
				mvwprintw(battleWindow,13,1,"Ran away!");
				return 1;
			}
			*highlight = 1;
		}
	return 0;
}

/*The player will deal points of damage randomly from 1 to their STR level*/
int PlayerAttack(WINDOW* battleWindow, Enemy *enemy){
	int damageDealt = rand()%(player->damage)+1;
	enemy->currentHealth-=damageDealt;
	mvwprintw(battleWindow,3,1,"You dealt %d damage!     ", damageDealt);
	return 1;
}

char* itemOptions[3] = {"Potion", "Super Potion", "Back"};
int healAmount[2] = {10,15};

/*Opens up the window to use and item*/
int UseItem(WINDOW* battleWindow, Enemy *enemy){
	WINDOW* itemWindow = newwin(MENUHEIGHT,MENUWIDTH,0,0);
	int highlight = 1,choosing = 1,input, madeChoice = 1;
	printUseItemScreen(itemWindow,highlight,itemOptions,3);
	wrefresh(itemWindow);
	while(choosing){
		input = wgetch(itemWindow);
		changeHighlight(input,&highlight,3);
		mvwprintw(itemWindow,1,11,"                       ");
		madeChoice = checkChoice(itemWindow, battleWindow, highlight, &choosing, input);
		printUseItemScreen(itemWindow,highlight,itemOptions,3);
		wrefresh(itemWindow);
	}
	werase(itemWindow);
	wrefresh(itemWindow);
	delwin(itemWindow);
	return madeChoice;
}

/*Checks to see if a choice was made, and applying the effects of the choice
  Returns 1 if an action was made, 0 otherwise								*/
int checkChoice(WINDOW* itemWindow, WINDOW* battleWindow,int itemToUse, int *choosing, char input){
	if(input == 10){
		if(itemToUse == 3){
			*choosing = 0;
			return 0;
		}
		itemToUse--;
		if(player->potionCounts[itemToUse]>0){
			player->currentHealth+=healAmount[itemToUse];
			player->potionCounts[itemToUse]--;
			if(itemToUse==0 && player->currentHealth>player->maxHealth){
				player->currentHealth = player->maxHealth;
			}
			mvwprintw(battleWindow,3,1,"Used a %s",itemOptions[itemToUse]);
			*choosing = 0;
			return 1;
		} else {
			mvwprintw(itemWindow,11,1,"You don't have enough!");
			return 0;
		}
	}
	return 0;
}

/*Enemy attacks randomly [1,STR-1]*/
void EnemyAttack(WINDOW* battleWindow, Enemy* enemy){
	int damageDone = rand()%enemy->damage;
	player->currentHealth -= damageDone;
	mvwprintw(battleWindow,4,1,"%s hit for %d damage!",enemy->name, damageDone);
}

/*Initializes and returns an enemy with an input difficulty*/
Enemy* CreateEnemy(int difficulty){
	int nameSeed = (player->name[0]+player->gold+player->xp+difficulty)%5;
	Enemy* enemy = calloc(1,sizeof(Enemy));
	enemy->maxHealth = (int) (difficulty * 1.5f);
	enemy->currentHealth = enemy->maxHealth;
	enemy->damage = difficulty;
	enemy->xp = (int)(difficulty*1.5f);
	enemy->gold = rand()%10;
	strcpy(enemy->name, enemyNames[nameSeed]);
	return enemy;
}
