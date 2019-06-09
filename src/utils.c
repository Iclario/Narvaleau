#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "utils.h"

int scanint ()
{
	char answer[10];

	scanf ("%s", answer);

	return strtol (answer, NULL, 10);
}

const char * shipName (ShipType shipType)
{
	switch (shipType)
	{
		case NO_SHIP:
			return "Erreur";

		case CARRIER:
			return "Porte-avion";

		case BATTLESHIP:
			return "Croiseur   ";

		case CRUISER:
			return "Torpilleur ";

		case SUBMARINE:
			return "Sous-marin ";

		case DESTROYER:
			return "Torpilleur ";

		default:
			return "Erreur";
	}
}

Coordinates getPosFromString (char * posChar)
{
	Coordinates pos;

	pos.number = strtol (posChar + 1, NULL, 10);
	pos.letter = posChar[0] - 'A' + 1;

	return pos;
}

char * getStringFromPos (char * buffer, Coordinates pos)
{
	if (pos.number >= 1 && pos.number <= BOARD_SIZE && pos.letter >= 1 && pos.letter <= BOARD_SIZE)
		sprintf (buffer, "%c%d", pos.letter + 'A' - 1, pos.number);
	else
		sprintf (buffer, "ER%d-%d", pos.letter, pos.number);

	return buffer;
}

const char * directionName (Direction dir)
{
	switch (dir)
	{
		case BAS:
			return "Bas   ";

		case GAUCHE:
			return "Gauche";

		case HAUT:
			return "Haut  ";

		case DROITE:
			return "Droite";

		default:
			return "Erreur";
	}
}

int positionIsInBound (Coordinates pos)
{
	return pos.letter >= 1 && pos.letter <= BOARD_SIZE && pos.number >= 1 && pos.number <= BOARD_SIZE;
}

int directionIsInBound (Direction dir)
{
	return dir >= 0 && dir <= 3;
}

int shipTypeIsInBound (ShipType shipType)
{
	return shipType >= 1 && shipType <= N_SHIPS;
}

int randInBounds (int a, int b)
{
	return rand() % (b - a) + a;
}

const char * getStringFromShot (ShotType shot)
{
	switch (shot)
	{
		case HIT:
			return "Touché !";

		case MISSED:
			return "Manqué !";

		case FLOWED:
			return "Coulé !";

		default:
			return "Erreur";
	}
}