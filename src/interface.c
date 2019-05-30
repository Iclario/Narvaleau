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

void display ()
{
	clear();

	if (edit)
	{
		if (player == 1)
		{
			displayBoard (&player2, 0);
			displayBoard (&player1, 1);
		}
		else if (player == 2)
		{
			displayBoard (&player1, 0);
			displayBoard (&player2, 1);
		}
		else
		{
			printf ("Erreur");
		}

		edit = 0;
	}
}

void displayBoard (Board * pboard, int displayShips)
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

	/*
	 *  printf (" %c%c%c\n%c%c%c", 0xE2, 0x88, 0xA5, 0xE2, 0x88, 0xA5);
	 *
	 *  for (j = 0; j < BOARD_SIZE * 3 + 3; j++)
	 *      printf (" ");*/

	printf (" %c%c%c\n", 0xE2, 0x88, 0xA5);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf ("%c%c%c%2d", 0xE2, 0x88, 0xA5, i + 1);

		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (pboard->shot[i][j] == 1)
				printf (" %c%c%c ", 0xE2, 0x9D, 0x8C);
			else if (pboard->shot[i][j] == 2)
				printf (" %c%c%c%c ", 0xF0, 0x9F, 0x94, 0xA5);
			else if (pboard->flag[i][j] == 1 && displayShips == 0)
				printf (" %c%c%c%c ", 0xF0, 0x9F, 0x9A, 0xA9);
			else if (displayShips == 1 && (pboard->ship[i][j] != 0))
				printf (" %c%c%c ", 0xE2, 0x96, 0xA0);	// 0xE2, 0xAC, 0x9B : Carré
			else
				printf (" . ");
		}

		/*
		 *      printf ("%c%c%c\n%c%c%c", 0xE2, 0x88, 0xA5, 0xE2, 0x88, 0xA5);
		 *
		 *      for (j = 0; j < BOARD_SIZE * 5 + 3; j++)
		 *          printf (" ");*/

		printf ("%c%c%c\n", 0xE2, 0x88, 0xA5);
	}

	for (i = 0; i < BOARD_SIZE * 3 + 4; i++)
		printf ("=");

	printf ("\n\n");
}	/* displayBoard */

void displayStartHeader (int player)
{
	char playerHeadText[10];

	printf ("\n");
	displayTextHead ("Placement des bateaux");
	sprintf (playerHeadText, "Joueur %d", player);
	displayTextHead (playerHeadText);
	printf ("\n");
}

void displayStart ()
{
	Board * board;

	Coordinates pos;// Chosen position variable

	int player;		// Currently chosing player
	int ships[5];	// Remaining placable ships
	int i, j, k;	// Couting variables
	int shipLength;	// Length of the chosen ship
	int choiceShip, choiceDirection;// User choice variables
	int directionLock[4];
	int directionLocked;

	char choicePlace[6];
	char bin;

	for (player = 1; player <= 2; player++)
	{
		for (i = 1; i < 6; i++)
			ships[i] = 1;

		if (player == 1)
			board = &player1;
		else
			board = &player2;

		do
		{
			clear();
			displayStartHeader (player);

			displayBoard (board, 1);

			printf ("Bateaux restants :\n\n");

			for (i = 1; i < 6; i++)
			{
				printf ("%d. ", i);

				switch (i)
				{
					case 1:
						printf ("Porte-avion (5 cases) ");
						break;
					case 2:
						printf ("Croiseur (4 cases)    ");
						break;
					case 3:
						printf ("Torpilleur (3 cases)  ");
						break;
					case 4:
						printf ("Sous-marin (3 cases)  ");
						break;
					case 5:
						printf ("Torpilleur (2 cases)  ");
						break;
				}

				printf (" : %d\n", ships[i]);
			}

			printf ("\n");

			do
			{
				printf ("Quel bateau voulez-vous placer ? ");
				choiceShip = scanint();
			}
			while (choiceShip < 1 || choiceShip > 5 || ships[choiceShip] <= 0);

			switch (choiceShip)
			{
				case 1:
					shipLength = 5;
					break;

				case 2:
					shipLength = 4;
					break;

				case 3:
				case 4:
					shipLength = 3;
					break;

				case 5:
					shipLength = 2;
					break;
			}

			do
			{
				printf ("Où souhaitez-vous le placer (De A1 à %c%d) ? ", 'A' + BOARD_SIZE - 1, BOARD_SIZE);
				scanf ("%s", choicePlace);
				pos.number = strtol (choicePlace + 1, NULL, 10);
				pos.letter = choicePlace[0] - 'A' + 1;
			}
			while (pos.letter < 1 || pos.letter > BOARD_SIZE || pos.number < 1 || pos.number > BOARD_SIZE);

			for (i = 0; i < 4; i++)
				directionLock[i] = 0;

			if (pos.number + shipLength > BOARD_SIZE + 1) directionLock[0] = 1;	// Bas
			if (pos.letter - shipLength < 0) directionLock[1] = 1;				// Gauche
			if (pos.number - shipLength < 0) directionLock[2] = 1;				// Haut
			if (pos.letter + shipLength > BOARD_SIZE + 1) directionLock[3] = 1;	// Droite

			for (i = 0; i < shipLength; i++)
			{
				if (directionLock[0] != 1 && board->ship[pos.number - 1 + i][pos.letter - 1] != 0)	// Bas
					directionLock[0] = 1;
				if (directionLock[1] != 1 && board->ship[pos.number - 1][pos.letter - 1 - i] != 0)	// Gauche
					directionLock[1] = 1;
				if (directionLock[2] != 1 && board->ship[pos.number - 1 - i][pos.letter - 1] != 0)	// Haut
					directionLock[2] = 1;
				if (directionLock[3] != 1 && board->ship[pos.number - 1][pos.letter - 1 + i] != 0)	// Droite
					directionLock[3] = 1;
			}

			printf ("Dans quelle orientation ?\n");
			printf ("1. Bas");
			if (directionLock[0]) printf ("    X");
			printf ("\n2. Gauche");
			if (directionLock[1]) printf (" X");
			printf ("\n3. Haut");
			if (directionLock[2]) printf ("   X");
			printf ("\n4. Droite");
			if (directionLock[3]) printf (" X");
			printf ("\n5. Annuler\n");

			do
			{
				printf ("Choix : ");
				choiceDirection = scanint();
				directionLocked = 0;

				for (i = 0; i < 4; i++)
					if (choiceDirection == i + 1 && directionLock[i] == 1)
						directionLocked = 1;
			}
			while (choiceDirection < 1 || choiceDirection > 5 || directionLocked);

			if (choiceDirection != 5)
			{
				i = pos.number - 1;
				j = pos.letter - 1;

				for (k = 0; k < shipLength; k++)
				{
					board->ship[i][j] = choiceShip;

					switch (choiceDirection)
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

				ships[0] = 0;
				ships[choiceShip]--;

				for (i = 1; i <= 5; i++)
					if (ships[i] == 1)
						ships[0] = 1;
			}
		}
		while (ships[0] == 1);

		clear();
		displayStartHeader (player);
		displayBoard (board, 1);
		displayCenteredText ("Voici votre disposition");
		printf ("\nAppuyez sur \"Entrée\" pour continuer");
		scanf ("%c%c", &bin, &bin);
	}
}	/* displayStart */

void displayGame ()
{ }