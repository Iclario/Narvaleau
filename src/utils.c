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

char * getStringFromPos (Coordinates pos)
{
	char * posChar = malloc (sizeof(char) * 5);

	sprintf (posChar, "%c%d", pos.letter + 'A' - 1, pos.number);

	return posChar;
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