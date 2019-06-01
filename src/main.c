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
	displayStart();

	/*
	 *  while (!allShipsPlaced (game.player1) || !allShipsPlaced (game.player2))
	 *  {
	 *      placeShipsRandomly (currentPlayer());
	 *      currentPlayer()->played = 1;
	 *
	 *      nextPlayer();
	 *  }
	 */
	
	displayGame();

	return 0;
}