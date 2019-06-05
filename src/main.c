#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "interface.h"
#include "utils.h"

int main ()
{
	initGame();
	initInterface();

	displayGame();

	quitInterface();
	quitGame();

	return 0;
}