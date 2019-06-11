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

	if (currentPlayer()->id == PLAYER1)
		printf ("\033[0;34m");	// Color : Blue
	else
		printf ("\033[0;31m");	// Color : Red

	for (i = 0; i < left; i++)
		printf ("%c%c%c", 0xE2, 0x80, 0x95);

	printf (" %s ", text);

	for (i = 0; i < right; i++)
		printf ("%c%c%c", 0xE2, 0x80, 0x95);

	printf ("\033[0m\n");
}

void displayTextHeadDouble (char * text)
{
	int length = strlen (text);
	int size   = BOARD_SIZE * 3 + 2 - length;
	int left   = size / 2.0 + 0.5;
	int right  = size / 2;
	int i;

	printf ("\033[01;32m");

	for (i = 0; i < left; i++)
		printf ("=");

	printf (" %s ", text);

	for (i = 0; i < right; i++)
		printf ("=");

	printf ("\033[0m");
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
	// printf ("\n\n\n\n\n\n");

	displayHeader();
}

void displayCenteredText (char * text)
{
	int length = customStrLen (text);
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

	printf ("\n");
	displayCenteredText ("\033[3;39mAppuyez sur \"Entrée\" pour continuer\033[0m");
	scanf ("%c", &bin);
}

void pressEnterToContinue ()
{
	char bin;
	char buffer[30];

	printf ("\n");

	if (gameIsOver())
		sprintf (buffer, "Fin de la partie !");
	else
		sprintf (buffer, "Au tour du \033%sjoueur %d\033[0m", currentPlayer()->id == PLAYER1 ? "[0;34m" : "[0;31m", currentPlayer()->id);

	displayCenteredText (buffer);
	printf ("\n");
	displayCenteredText ("\033[3;39mAppuyez sur \"Entrée\" pour continuer\033[0m");
	scanf ("%c%c", &bin, &bin);
}

void displayBoard (Player * player)
{
	int i, j;

	if (player->id == PLAYER1)
		printf ("\033[1;34m");	// Color : Blue
	else
		printf ("\033[1;31m");	// Color : Red

	printf ("%c%c%c", 0xE2, 0x95, 0x94);// ╔

	for (i = 1; i < BOARD_SIZE * 3 + 3; i++)
		printf ("%c%c%c", 0xE2, 0x95, 0x90);	// ═

	printf ("%c%c%c\n", 0xE2, 0x95, 0x97);	// ╗

	printf ("%c%c%c ", 0xE2, 0x95, 0x91);	// ║

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf ("  %c", i + 'A');
	}

	printf (" %c%c%c\n", 0xE2, 0x95, 0x91);	// ║

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf ("%c%c%c%2d", 0xE2, 0x95, 0x91, i + 1);	// ║

		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (player->board->shot[i][j] == MISSED)
				printf (" %c%c%c ", 0xE2, 0xA8, 0xAF);
			else if (player->board->shot[i][j] == HIT)
			{
				switch (player->board->ship[i][j].dir)
				{
					case RIGHT:
						printf ("%c%c%c", 0xE2, 0x96, 0x97);
						printf ("%c%c%c", 0xE2, 0x96, 0x97);
						printf ("%c%c%c", 0xE2, 0x96, 0x97);
						break;

					case DOWN:
						if (player->board->ship[i][j].master == 1)
							printf (" %c%c%c ", 0xE2, 0x96, 0x96);
						else
							printf (" %c%c%c ", 0xE2, 0x96, 0x9E);
						break;

					default:
						printf (" x ");
						break;
				}
			}
			else if (player->board->shot[i][j] == FLOWED)
				printf (" %c%c%c ", 0xE2, 0x9C, 0x9D);
			else if (isPlaying (player) && (player->board->ship[i][j].type != NO_SHIP))
			{
				switch (player->board->ship[i][j].dir)
				{
					case RIGHT:
						if (j == 0 || player->board->ship[i][j].master == 1)
							printf (" ");
						else
							printf ("%c%c%c", 0xE2, 0x96, 0x84);

						printf ("%c%c%c", 0xE2, 0x96, 0x84);

						if (j == BOARD_SIZE - 1)
							printf (" ");
						else
							printf ("%c%c%c", 0xE2, 0x96, 0x84);
						break;

					case DOWN:
						if (player->board->ship[i][j].master == 1)
							printf (" %c%c%c ", 0xE2, 0x96, 0x85);
						else
							printf (" %c%c%c ", 0xE2, 0x96, 0x88);

						break;

					default:
						printf (" x ");
						break;
				}
			}
			else if (!isPlaying (player) && player->board->flag[i][j] == PERSONNAL)
				printf (" %c%c%c ", 0xE2, 0x8A, 0x95);
			else
				printf (" . ");
		}

		printf ("%c%c%c\n", 0xE2, 0x95, 0x91);	// ║
	}

	printf ("%c%c%c", 0xE2, 0x95, 0x9A);// ╚

	for (i = 0; i < BOARD_SIZE * 3 + 2; i++)
		printf ("%c%c%c", 0xE2, 0x95, 0x90);	// ═

	printf ("%c%c%c", 0xE2, 0x95, 0x9D);// ╝

	printf ("\033[0m\n");
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

			printf ("\n\033[1;39mBateaux restants :\033[0;00m\n\n");

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

			for (i = 0; i <= 1; i++)
				printf ("%d. %s %s\n", i + 1, directionName (i), shipIsNotPlaceable (currentPlayer(), choicePos, i, choiceShip) ? "X" : "");

			printf ("%d. Annuler\n", i + 1);

			do
			{
				printf ("Choix : ");
				choiceDirection = scanint() - 1;
				if (choiceDirection == i)
					break;
			}
			while (!directionIsInBound (choiceDirection) || shipIsNotPlaceable (currentPlayer(), choicePos, choiceDirection, choiceShip));

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
	char buffer[30];
	char buffer2[10];	// User position choice (String)
	ShotType shot;

	displayStart();

	while (!gameIsOver())
	{
		displayGameBoard();

		if (game.lastHit.number != 0 && game.lastHit.letter != 0)
		{
			sprintf (buffer, "Joueur %d a attaqué en %s\n", otherPlayer()->id, getStringFromPos (buffer2, game.lastHit));
			displayCenteredText (buffer);
		}

		printf ("\n");

		do
		{
			printf ("Où souhaitez-vous attaquer ? (De A1 à %c%d) ? ", 'A' + BOARD_SIZE - 1, BOARD_SIZE);
			scanf ("%s", buffer2);
			choicePos = getPosFromString (buffer2);

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