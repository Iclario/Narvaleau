#include "interface.h"

#if GRAPHIQUE == 0

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "game.h"
# include "utils.h"

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

void initInterface ()
{
	char bin;

	clear();

	printf ("\nAppuyez sur \"Entrée\" pour continuer");
	scanf ("%c", &bin);
}

void pressEnterToContinue ()
{
	char bin;
	char buffer[30];

	printf ("\n");
	sprintf (buffer, "Au tour du joueur %d", currentPlayer()->id);
	displayCenteredText (buffer);
	displayCenteredText ("Appuyez sur \"Entrée\" pour continuer");
	scanf ("%c%c", &bin, &bin);
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
			if (player->board->shot[i][j] == MISSED)
				printf (" %c%c%c ", 0xE2, 0xA8, 0xAF);
			else if (player->board->shot[i][j] == HIT)
				printf (" %c%c%c%c ", 0xF0, 0x9F, 0x94, 0xA5);
			else if (player->board->shot[i][j] == FLOWED)
				printf (" %c%c%c ", 0xE2, 0x9C, 0x9D);
			else if (isPlaying (player) && (player->board->ship[i][j] != NO_SHIP))
				printf (" %c%c%c ", 0xE2, 0x96, 0xA0);
			else if (!isPlaying (player) && player->board->flag[i][j] == PERSONNAL)
				printf (" %c%c%c ", 0xE2, 0x8A, 0x95);
			else
				printf (" . ");
		}

		printf ("%c%c%c\n", 0xE2, 0x88, 0xA5);
	}

	for (i = 0; i < BOARD_SIZE * 3 + 4; i++)
		printf ("=");

	printf ("\n");
}	/* displayBoard */

void displayStartHeader ()
{
	char buffer[10];

	printf ("\n");
	displayTextHead ("Placement des navires");
	sprintf (buffer, "Joueur %d", currentPlayer()->id);
	displayTextHead (buffer);
	printf ("\n");
}

void displayGameHeader ()
{
	char buffer[10];

	printf ("\n");
	sprintf (buffer, "Tour %d", game.round);
	displayTextHead (buffer);
	sprintf (buffer, "Joueur %d", currentPlayer()->id);
	displayTextHead (buffer);
	printf ("\n");
}

void displayStartBoard ()
{
	clear();
	displayStartHeader();
	displayBoard (currentPlayer());
}

void displayStart ()
{
	int i;						// Couting variable
	Direction choiceDirection;	// User direction choice
	ShipType choiceShip;		// User ship choice
	Coordinates choicePos;		// User position choice
	char buffer[10];			// User position choice (String)

	while (!allShipsPlaced (game.player1) || !allShipsPlaced (game.player2))
	{
		do
		{
			displayStartBoard();

			printf ("\nBateaux restants :\n\n");

			for (i = 1; i <= N_SHIPS; i++)
				printf ("%d. %s (%d cases) : %d\n", i, shipName (i), getShipLength (i), currentPlayer()->placeableShips[i - 1]);

			printf ("\n%d. Finir de placer aléatoirement\n\n", i);

			do
			{
				printf ("Quel bateau voulez-vous placer ? ");
				choiceShip = scanint();

				if (choiceShip == N_SHIPS + 1)
					break;
			}
			while (!shipTypeIsInBound (choiceShip) || currentPlayer()->placeableShips[choiceShip - 1] <= 0);

			if (choiceShip == N_SHIPS + 1)
			{
				placeShipsRandomly (currentPlayer());
				break;
			}


			do
			{
				printf ("Où souhaitez-vous le placer (De A1 à %c%d) ? ", 'A' + BOARD_SIZE - 1, BOARD_SIZE);
				scanf ("%s", buffer);
				choicePos = getPosFromString (buffer);
			}
			while (!positionIsInBound (choicePos));

			printf ("Dans quelle orientation ?\n");

			for (i = 0; i < 4; i++)
				printf ("%d. %s %s\n", i + 1, directionName (i), shipIsNotPlaceable (currentPlayer(), choicePos, i, choiceShip) ? "X" : "");

			printf ("%d. Annuler\n", i + 1);

			do
			{
				printf ("Choix : ");
				choiceDirection = scanint() - 1;
				if (choiceDirection == 4)
					break;
			}
			while (choiceDirection < 0 || choiceDirection > 3 || shipIsNotPlaceable (currentPlayer(), choicePos, choiceDirection, choiceShip) );

			placeShip (currentPlayer(), choicePos, choiceDirection, choiceShip);
		}
		while (!allShipsPlaced (currentPlayer()));

		displayStartBoard();

		displayCenteredText ("Voici votre disposition");

		nextPlayer();

		pressEnterToContinue();
	}
}	/* displayStart */

void displayGameBoard ()
{
	clear();

	displayGameHeader();
	displayBoard (otherPlayer());
	displayBoard (currentPlayer());
}

void displayGame ()
{
	Coordinates choicePos;	// User position choice
	char buffer[30];		// User position choice (String)
	ShotType shot;

	displayStart();

	while (!gameIsOver())
	{
		displayGameBoard();

		if (game.lastHit.number != 0 && game.lastHit.letter != 0)
			printf ("Joueur %d a attaqué en %s\n", otherPlayer()->id, getStringFromPos (buffer, game.lastHit));

		printf ("\n");

		do
		{
			printf ("Où souhaitez-vous attaquer ? (De A1 à %c%d) ? ", 'A' + BOARD_SIZE - 1, BOARD_SIZE);
			scanf ("%s", buffer);
			choicePos = getPosFromString (buffer);

			shot = shootPlayer (otherPlayer(), choicePos);
		}
		while (shot == NO_SHOT);

		clear();

		displayGameHeader();
		displayBoard (otherPlayer());
		nextPlayer();
		displayBoard (otherPlayer());

		displayCenteredText ((char *) getStringFromShot (shot));
		pressEnterToContinue();
	}

	clear();

	printf ("\n");
	sprintf (buffer, "Victoire du joueur %d !", game.winner);
	displayCenteredText (buffer);
}	/* displayGame */

void quitInterface ()
{
	printf ("\n\nA bientôt !\n\n");
}

#endif	// if GRAPHIQUE = 0