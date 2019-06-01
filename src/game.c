#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Player * currentPlayer ()
{
	if (game.current == PLAYER1)
		return game.player1;
	else
		return game.player2;
}

Player * otherPlayer ()
{
	if (game.current == PLAYER1)
		return game.player2;
	else
		return game.player1;
}

void initGame ()
{
	int i, j;

	game.player1 = malloc (sizeof(Player));
	game.player2 = malloc (sizeof(Player));
	game.current = PLAYER1;

	game.player1->board	  = malloc (sizeof(Board));
	game.player1->id	  = PLAYER1;
	game.player1->isReady = 0;

	game.player2->board	  = malloc (sizeof(Board));
	game.player2->id	  = PLAYER2;
	game.player2->isReady = 0;


	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			game.player1->board->ship[i][j] = NO_SHIP;
			game.player2->board->ship[i][j] = NO_SHIP;
			game.player1->board->flag[i][j] = NO_FLAG;
			game.player2->board->flag[i][j] = NO_FLAG;
			game.player1->board->shot[i][j] = NO_SHOT;
			game.player2->board->shot[i][j] = NO_SHOT;
		}
	}
}

int * shipIsPlaceable (Player * player, Coordinates pos, ShipType shipType)
{
	int i;
	int * directionLock;
	int length = getShipLength (shipType);

	directionLock = malloc (sizeof(int) * 4);

	for (i = 0; i < 4; i++)
		directionLock[i] = 0;

	if (pos.number + length > BOARD_SIZE + 1) directionLock[0] = 1;	// Bas
	if (pos.letter - length < 0) directionLock[1] = 1;				// Gauche
	if (pos.number - length < 0) directionLock[2] = 1;				// Haut
	if (pos.letter + length > BOARD_SIZE + 1) directionLock[3] = 1;	// Droite

	for (i = 0; i < length; i++)
	{
		if (directionLock[0] != 1 && player->board->ship[pos.number - 1 + i][pos.letter - 1] != 0)	// Bas
			directionLock[0] = 1;
		if (directionLock[1] != 1 && player->board->ship[pos.number - 1][pos.letter - 1 - i] != 0)	// Gauche
			directionLock[1] = 1;
		if (directionLock[2] != 1 && player->board->ship[pos.number - 1 - i][pos.letter - 1] != 0)	// Haut
			directionLock[2] = 1;
		if (directionLock[3] != 1 && player->board->ship[pos.number - 1][pos.letter - 1 + i] != 0)	// Droite
			directionLock[3] = 1;
	}

	return directionLock;
}

void initShips (Player * player)
{
	int i;

	for (i = 0; i < N_SHIPS; i++)
		currentPlayer()->placeableShips[i] = 1;
}

void nextPlayer ()
{
	if (game.current == PLAYER1)
		game.current = PLAYER2;
	else
		game.current = PLAYER1;
}

int allShipsPlaced (Player * player)
{
	int i;

	for (i = 0; i < N_SHIPS; i++)
		if (player->placeableShips[i] == 1)
			return 0;

	return 1;
}

void placeShip (Player * player, Coordinates pos, int direction, ShipType shipType)
{
	int i, j, k;
	int length = getShipLength (shipType);

	i = pos.number - 1;
	j = pos.letter - 1;

	for (k = 0; k < length; k++)
	{
		player->board->ship[i][j] = shipType;

		switch (direction)
		{
			case 1:
				i++;
				break;
			case 2:
				j--;
				break;
			case 3:
				i--;
				break;
			case 4:
				j++;
				break;
		}
	}

	player->placeableShips[shipType - 1]--;
}

int getShipLength (ShipType choiceShip)
{
	switch (choiceShip)
	{
		case CARRIER:
			return 5;

		case BATTLESHIP:
			return 4;

		case CRUISER:
		case SUBMARINE:
			return 3;

		case DESTROYER:
			return 2;

		default:
			return 0;
	}
}

int isPlaying (Player * player)
{
	if (game.current == player->id)
		return 1;

	return 0;
}