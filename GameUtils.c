/*By Toby McGuire*/
#include "GameUtils.h"

char Map00[12][40]={"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
					"XXXXXXXXXXX $     E         E XXXXX $ X",
					"XX$XXX         ~~~             XXX    X",
					"X   E        ~~~~~~~                  X",
					"XXXXXXXXXXX~~~~~~~~~    E             X",
					"XXXXXXXX$   ~~~~~~~~~          XXX    X",
					"XXXX      E    ~~~          XXXXXXXXE X",
					"XXX   E                      XXXXXXXXXX",
					"XX                      $      XXXX $XX",
					"XXX E           $             $   E   X",
					"XXXXXXXXX   %                      XXXX",
					"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"};



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
void Save(char *savePath){
	int i;
	FILE* saveFile = fopen(savePath,"w");
	fprintf(saveFile,"%s\n%d\n%d\n%d\n%d\n%d\n%d\n%d\t%d\n%d\t%d\n",player->name,player->level,player->xp,player->maxHealth,player->currentHealth, player->damage, player->gold,playerLocation[0],playerLocation[1],player->potionCounts[0],player->potionCounts[1]);
	for(i = 0; i<MAPHEIGHT; i++){
		fprintf(saveFile,"%s",Map00[i]);
	}
	fclose(saveFile);
}

/*Reads in the save data and returns a corresponding player*/
void ReadSaveData(FILE* saveFile){
	int i;
	char playerName[21];
	fscanf(saveFile,"%[^\n]",playerName);
	createNewPlayer(playerName);
	fscanf(saveFile,"%d\n%d\n%d\n%d\n%d\n%d\n%d\t%d\n%d\t%d\n",&(player->level),&(player->xp),&(player->maxHealth),&(player->currentHealth),&(player->damage),&(player->gold),&playerLocation[0],&playerLocation[1],&(player->potionCounts[0]),&(player->potionCounts[1]));
	for(i = 0; i<MAPHEIGHT; i++){
		fgets(Map00[i],40,saveFile);
	}
}


/*Switches the highlight up or down depending on the input and number of choices given*/
void changeHighlight(int c, int *highlight,int numChoices){
	switch(c)
	{	
		case 259:
		case 260:
			if(*highlight == 1)
				*highlight = numChoices;
			else
				(*highlight)--;
			break;
		case 258:
		case 261:
			if(*highlight == numChoices)
				*highlight = 1;
			else 
				(*highlight)++;
			break;
		default:
			break;
	}
}
