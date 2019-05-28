#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "interface.h"

void clear()
{
	printf("\033[H\033[J");
}

void initInterface()
{
	char a;
	
	clear();
	printf("======================== Bataille navale ========================\n");
	printf("=========================== Naval'eau ===========================\n");
	
	printf("Appuyez sur \"Entrée\" pour continuer\n");
	/* scanf("%c", &a); */
}

void display()
{
	clear();

	if (edit)
	{
		if (player == 1)
		{
			displayBoard(&player2, 0);
			displayBoard(&player1, 1);
		}
		else if (player == 2)
		{
			displayBoard(&player1, 0);
			displayBoard(&player2, 1);
		}
		else
		{
			printf("Erreur");
		}

		edit = 0;
	}
}

void displayBoard(Board *pboard, int displayShips)
{
	int i, j;
	
	printf("===");
	for (i = 0; i < BOARD_SIZE; i++)
		printf("=====");
	printf("\n");
 
	printf("= ");
	
	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("    %c", i + 'A');
	}
	
	printf("\n=\n");
	
	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("= %2d", i + 1);
		
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (pboard->shot[i][j] == 1)
				printf("  %c%c%c  ", 0xE2, 0x9D, 0x8C);
			else if (pboard->shot[i][j] == 2)
				printf("  %c%c%c%c  ", 0xF0, 0x9F, 0x94, 0xA5);
			else if (pboard->flag[i][j] == 1 && displayShips == 0)
				printf("  %c%c%c%c  ", 0xF0, 0x9F, 0x9A, 0xA9);
			else if (displayShips == 1 && pboard->ship[i][j] == 4)
					printf("  %c%c%c  ", 0xE2, 0xAC, 0x9B);
			else
				printf("  .  ");
		}
		
		printf("\n=\n");
	}
	
	printf("\n");
	
}

void displayStart()
{
	Board *board;
	int ships[5], i, player, choiceShip, choiceDirection, posNum, posLetter, directionLock[4], directionLocked, shipLength;
	char choicePlace[6];

	for (player = 1; player <= 2; player++)
	{
		for (i = 1; i < 6; i++)
			ships[i] = 1;

		for (i = 0; i < 4; i++)
			directionLock[i] = 0;

		if (player == 1)
			board = &player1;
		else
			board = &player2;
		

		do
		{
			clear();
			printf("Joueur %d, placez vos bateaux !\n\n", player);

			displayBoard(board, 1);

			printf("Bateaux restants :\n");

			for (i = 1; i < 6; i++)
			{
				printf("    %d. ", i);

				switch (i)
				{
					case 1:
						printf("Porte-avion (5 cases)      ");
						break;
					case 2:
						printf("Croiseur (4 cases)         ");
						break;
					case 3:
						printf("Contre-torpilleur (3 cases)");
						break;
					case 4:
						printf("Sous-marin (3 cases)       ");
						break;
					case 5:
						printf("Torpilleur (2 cases)       ");
						break;
				}

				printf(" : %d\n", ships[i]);
			}

			printf("\n");

			do
			{
				printf("Quel bateau voulez-vous placer ? ");
				scanf("%d", &choiceShip);
			}while (choiceShip < 1 || choiceShip > 5 || ships[choiceShip] <= 0);
			
			ships[choiceShip]--;

			switch(choiceShip)
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
				printf("Où souhaitez-vous le placer (De A1 à %c%d) ? ", 'A' + BOARD_SIZE - 1, BOARD_SIZE);
				scanf("%s", choicePlace);
				posNum = strtol(choicePlace + 1, NULL, 10);
				posLetter = choicePlace[0];
			}while (posLetter < 'A' || posLetter > 'A' + BOARD_SIZE - 1 || posNum < 1 || posNum > BOARD_SIZE);

			/* shipLength
			* 0 : Bas
			* 1 : Gauche
			* 2 : Haut
			* 3 : Droite
			*/

			if (posLetter + 1 - 'A' - shipLength < 0)
				directionLock[1] = 1;
			if (posLetter + 1 - 'A' + shipLength > BOARD_SIZE + 1)
				directionLock[3] = 1;
			if (posNum - shipLength < 0)
				directionLock[2] = 1;
			if (posNum + shipLength > BOARD_SIZE + 1)
				directionLock[0] = 1;

			printf("Dans quelle orientation ?\n");
			printf("1. Bas");
			if (directionLock[0]) printf("    X");
			printf("\n2. Gauche");
			if (directionLock[1]) printf(" X");
			printf("\n3. Haut");
			if (directionLock[2]) printf("   X");
			printf("\n4. Droite");
			if (directionLock[3]) printf(" X");
			printf("\n");

			do
			{
				printf("Choix : ");
				scanf("%d", &choiceDirection);
				
				directionLocked = 0;

				for (i = 0; i < 4; i++)
					if (choiceDirection == i + 1 && directionLock[i] == 1)
						directionLocked = 1;
			}while (directionLocked);

			ships[0] = 0;

			for (i = 1; i < 5; i++)
				if (ships[i] == 1)
					ships[0] = 1;
			
			posLetter;
			posNum;
			shipLength;
			board;
			/* A faire :
			 * 
			 * Positionner les cases prises
			 */

		}while (ships[0] == 1);
	}
}