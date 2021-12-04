# C-RPG
I Created an RPG from scratch in C using basic libraries

This project was created on linux a system with gcc installed and run in a terminal. It will likely work on other systems as long as the last two conditions are met but I haven't tested so I can't say for sure.

## Compilation Instructions:
Type 'make' into the terminal while in the game directory to have the makefile build the game

## Run instructions:
Run through the terminal using 'CRPG *savename*'

Use the arrowkeys to move the cursor and character, Enter to select when applicable

## Symbol Guide:
 *--> Your Character
 
 % --> Town (Enter to return to menu)
 
 E --> Enemies (Level scales to the player)
 
 $ --> Random item (Gold, Potion, Super Potion)
 
 X --> Tree (Cannot Pass)
 
 ~ --> Water (Cannot Pass)
 
 . --> Footstep (Aesthetic)

## Notes:
Player Loses 5 gold on death

Attacks deal damage from [1,STR level]

Potions heal 10 up to max HP, but Super Potions can overheal

Health is set to max on level up

## Bugs:
Sometimes the player can spawn on top of the down, deleting it and requiring a reset of the character save
