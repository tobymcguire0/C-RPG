game:
	gcc -ansi -pedantic -std=c89 -Wall -Werror -lncurses -g *.c WindowTools/*.c -D GAME -o CRPG
