#include <stdio.h>
#include <string.h>
#include "main.h"
#include "game.h"
#include "interface.h"

int main ()
{
	initInterface();
	initGame();

	displayStart();

	return 0;
}