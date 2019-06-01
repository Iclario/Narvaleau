#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "interface.h"
#include "utils.h"

void clear ()
{
	printf ("\033[H\033[J");
	printf ("\033[H\033[J");

	displayHeader();
}

void displayCenteredText (char * text)
{
	int length = strlen (text);
	int size   = BOARD_SIZE * 3 + 4 - length;
	int left   = size / 2.0 + 0.5;
	int i;

	for (i = 0; i < left; i++)
		printf (" ");

	printf ("%s\n", text);
}

void displayTextHead (char * text)
{
	int length = strlen (text);
	int size   = BOARD_SIZE * 3 + 2 - length;
	int left   = size / 2.0 + 0.5;
	int right  = size / 2;
	int i;

	for (i = 0; i < left; i++)
		printf ("%c%c%c", 0xE2, 0x80, 0x95);

	printf (" %s ", text);

	for (i = 0; i < right; i++)
		printf ("%c%c%c", 0xE2, 0x80, 0x95);

	printf ("\n");
}

void displayTextHeadDouble (char * text)
{
	int length = strlen (text);
	int size   = BOARD_SIZE * 3 + 2 - length;
	int left   = size / 2.0 + 0.5;
	int right  = size / 2;
	int i;

	for (i = 0; i < left; i++)
		printf ("=");

	printf (" %s ", text);

	for (i = 0; i < right; i++)
		printf ("=");

	printf ("\n");
}

void displayHeader ()
{
	displayTextHeadDouble ("Bataille navale");
	displayTextHeadDouble (GAME_NAME);
}

void initInterface ()
{
	char bin;

	clear();

	printf ("Appuyez sur \"Entrée\" pour continuer\n");
	scanf ("%c", &bin);
}

void displayBoard (Player * player)
{
	int i, j;

	for (i = 0; i < BOARD_SIZE * 3 + 4; i++)
		printf ("=");

	printf ("\n");

	printf ("%c%c%c ", 0xE2, 0x88, 0xA5);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf ("  %c", i + 'A');
	}

	printf (" %c%c%c\n", 0xE2, 0x88, 0xA5);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf ("%c%c%c%2d", 0xE2, 0x88, 0xA5, i + 1);

		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (player->board->shot[i][j] == 1)
				printf (" %c%c%c ", 0xE2, 0x9D, 0x8C);
			else if (player->board->shot[i][j] == 2)
				printf (" %c%c%c%c ", 0xF0, 0x9F, 0x94, 0xA5);
			else if (player->board->flag[i][j] == 1 && !isPlaying(player))
				printf (" %c%c%c%c ", 0xF0, 0x9F, 0x9A, 0xA9);
			else if (isPlaying(player) && (player->board->ship[i][j] != 0))
				printf (" %c%c%c ", 0xE2, 0x96, 0xA0);
			else
				printf (" . ");
		}

		printf ("%c%c%c\n", 0xE2, 0x88, 0xA5);
	}

	for (i = 0; i < BOARD_SIZE * 3 + 4; i++)
		printf ("=");

	printf ("\n\n");
}	/* displayBoard */

void displayStartHeader ()
{
	char playerHeadText[10];

	printf ("\n");
	displayTextHead ("Placement des bateaux");
	sprintf (playerHeadText, "Joueur %d", currentPlayer()->id);
	displayTextHead (playerHeadText);
	printf ("\n");
}

void displayStart ()
{
	char bin;
	int i;					// Couting variable
	int choiceDirection;	// User direction choice
	ShipType choiceShip;	// User ship choice
	Coordinates choicePos;	// User position choice
	char choicePosChar[10];	// User position choice (String)

	while (!game.player1->isReady || !game.player2->isReady)
	{
		initShips (currentPlayer());

		do
		{
			clear();
			displayStartHeader();
			displayBoard (currentPlayer());

			printf ("Bateaux restants :\n\n");

			for (i = 1; i < 6; i++)
				printf ("%d. %s (%d cases) : %d\n", i, shipName (i), getShipLength (i), currentPlayer()->placeableShips[i - 1]);

			printf ("\n");

			do
			{
				printf ("Quel bateau voulez-vous placer ? ");
				choiceShip = scanint();
			}
			while (choiceShip < 1 || choiceShip > 5 || currentPlayer()->placeableShips[choiceShip - 1] <= 0);

			do
			{
				printf ("Où souhaitez-vous le placer (De A1 à %c%d) ? ", 'A' + BOARD_SIZE - 1, BOARD_SIZE);
				scanf ("%s", choicePosChar);
				choicePos = getPosFromString (choicePosChar);
			}
			while (choicePos.letter < 1 || choicePos.letter > BOARD_SIZE || choicePos.number < 1 || choicePos.number > BOARD_SIZE);

			int * directionLock = shipIsPlaceable (currentPlayer(), choicePos, getShipLength (choiceShip));

			printf ("Dans quelle orientation ?\n");

			for (i = 0; i < 4; i++)
				printf ("%d. %s %s\n", i + 1, directionName (i), directionLock[i] ? "X" : "");

			printf ("%d. Annuler\n", i + 1);

			do
			{
				printf ("Choix : ");
				choiceDirection = scanint();
			}
			while (choiceDirection < 1 || choiceDirection > 5 || directionLock[choiceDirection - 1] == 1);

			if (choiceDirection != 5)
				placeShip (currentPlayer(), choicePos, choiceDirection, choiceShip);
		}
		while (!allShipsPlaced (currentPlayer()));

		clear();
		displayStartHeader();
		displayBoard (currentPlayer());
		displayCenteredText ("Voici votre disposition");
		printf ("\nAppuyez sur \"Entrée\" pour continuer");
		scanf ("%c%c", &bin, &bin);

		currentPlayer()->isReady = 1;
		nextPlayer();
	}
}	/* displayStart */

void displayGame ()
{
	clear();

	displayBoard (currentPlayer());
	displayBoard (otherPlayer());
}