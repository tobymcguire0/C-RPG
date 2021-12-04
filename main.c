/*By Toby McGuire*/
#include <time.h>
#include <unistd.h>

#include "GameUtils.h"
#include "Player.h"
#include "Battle.h"
#include "WindowTools/Windows.h"


char* currentSavePath;

/*Function Declarations*/
void ShopMenu();
void InShop();
void MainMenu();
void NewPlayerInitiation(char* savePath);
void DisplayStats();
void Init(char* saveFilePath);
void PreLoadInstructions(char* cmdInput,char* saveFilePath);

void (*select_array[3])() = {EnterMap,ShopMenu,DisplayStats};
char* menuOptions[] = {"Explore",
					"Shop",
					"Stats",
					"Quit"};

/*Initializes the shop menu*/
void ShopMenu(){
	WINDOW *shopWindow = newwin(SHOPHEIGHT,SHOPWIDTH,0,MENUWIDTH);
	refresh();
	keypad(shopWindow,TRUE);
	box(shopWindow,0,0);
	wattron(shopWindow,A_BOLD);
	mvwprintw(shopWindow,1,(SHOPWIDTH>>1)-2,"Shop");
	wattroff(shopWindow,A_BOLD);
	wrefresh(shopWindow);
	InShop(shopWindow);
	werase(shopWindow);
	wrefresh(shopWindow);
	delwin(shopWindow);
}


/*Opens up a window to display the user's stats*/
void DisplayStats(){
	WINDOW *statsWindow = newwin(SECONDARYHEIGHT,SECONDARYWIDTH,0,0);
	refresh();
	keypad(statsWindow,TRUE);
	mvwprintw(statsWindow,13,1,"Press Enter to exit");
	wrefresh(statsWindow);
	printStats(statsWindow);
	werase(statsWindow);
	wrefresh(statsWindow);
	delwin(statsWindow);
}



/*Creates the main menu, the base for the game*/
void MainMenu(){
	int highlight = 1,input;
	WINDOW *menuWindow = newwin(MENUHEIGHT,MENUWIDTH,0,0);
	keypad(menuWindow, TRUE);
	printMenu(menuWindow,highlight,menuOptions,4);
	wrefresh(menuWindow);
	while(1){
		input = wgetch(menuWindow);
		changeHighlight(input,&highlight,4);
		if(input==10){
				if(highlight!=4){
					select_array[highlight-1]();
				} else {
				break;
				}
			highlight = 1;
		}
		printMenu(menuWindow,highlight,menuOptions,4);
	}
	delwin(menuWindow);
}


/*Prompts the user to input a name for their new character*/
void NewPlayerInitiation(char* savePath){
	char *playerName = calloc(21,sizeof(char));
	playerLocation[0] = 11;
	playerLocation[1] = 15;
	printw("Welcome new player! Enter the name of your character (Max 20 characters): \n");
	refresh();
	getnstr(playerName,20);
	if(!strcmp(playerName,""))
		strcpy(playerName, "No Name");
	createNewPlayer(playerName);
	Save(savePath);
}

/*Initializes all important parts of NCurses and the random number generator*/
void Init(char* saveFilePath){
	time_t t;
	strcpy(saveFilePath,"SaveFiles/");
	srand((unsigned) time(&t));
	initscr();
	echo();
	cbreak();
	curs_set(0);
	InitializeColors();
}

/*Does setup for the save file and reading in previous save data*/
void PreLoadInstructions(char* cmdInput, char* saveFilePath){
	FILE* saveFile;
	strcat(saveFilePath,cmdInput);
	currentSavePath = saveFilePath;
	saveFile = fopen(saveFilePath,"r");
	if(!saveFile){
		NewPlayerInitiation(saveFilePath);
		clear();
	} else {
		ReadSaveData(saveFile);
		printw("Welcome back %s \n*Press Any Key to continue*\n", player->name);
		refresh();
		fclose(saveFile);
		getchar();
	}
	noecho();
	clear();
}

#ifdef GAME
int main(int argc, char* argv[]){
	char* saveFilePath = calloc(100,sizeof(char));
	Init(saveFilePath);
	if(argc<2){
		printw("Enter save name to run the program\n"
			"Quitting...\n");
		refresh();
		sleep(2);
	} else {
		PreLoadInstructions(argv[1], saveFilePath);
		MainMenu();
		free(player);
	}
	free(saveFilePath);
	endwin();
	return 0;
}
#endif

