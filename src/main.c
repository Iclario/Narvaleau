#include <stdio.h>
#include <string.h>
#include "game.h"
#include "interface.h"

int main ()
{
	initGame();
	initInterface();

	displayStart();

	while (1)
		displayGame();

	return 0;
}