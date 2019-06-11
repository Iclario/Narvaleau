#include "interface.h"

#if GRAPHIQUE == 1

# include "game.h"
# include "utils.h"
# include <stdlib.h>
# include <stdio.h>
# include <SDL2/SDL.h>

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Texture * shipImage[N_SHIPS];
SDL_Rect rect;

/*
 * Draws the board
 *
 * Arguments:
 * int upDown : Draws it up (0) or down (1)
 *
 */
void drawBoard (int upDown, Player * player)
{
	int w, h, i, j, flag;
	SDL_Rect dest;

	SDL_GetWindowSize (window, &w, &h);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			rect.w = SQUARE_SIZE;
			rect.h = SQUARE_SIZE;
			rect.y = SQUARE_SIZE * upDown * (BOARD_SIZE + 1) + SQUARE_SIZE + SQUARE_SIZE * i;
			rect.x = SQUARE_SIZE + SQUARE_SIZE * j;

			if (player->id == game.current)
			{
				if ((j + i) % 2 == 0)
					SDL_SetRenderDrawColor (renderer, 0x7F, 0, 0, 255);
				else
					SDL_SetRenderDrawColor (renderer, 0xB7, 0x1C, 0x1C, 255);
			}
			else
			{
				if ((j + i) % 2 == 0)
					SDL_SetRenderDrawColor (renderer, 0x21, 0x71, 0xA1, 255);
				else
					SDL_SetRenderDrawColor (renderer, 0, 0x21, 0x71, 255);
			}

			SDL_RenderFillRect (renderer, &rect);
		}
	}

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (player->board->ship[i][j] != NO_SHIP)
			{
				dest.w = SQUARE_SIZE * getShipLength (player->board->ship[i][j]);
				dest.h = SQUARE_SIZE;
				dest.y = SQUARE_SIZE * upDown * (BOARD_SIZE + 1) + SQUARE_SIZE + SQUARE_SIZE * i;
				dest.x = SQUARE_SIZE + SQUARE_SIZE * j;

				SDL_RenderCopy (renderer, shipImage[player->board->ship[i][j]], NULL, &dest);
			}
		}
	}
}	/* drawBoard */

void initInterface ()
{
	int i;

	window = SDL_CreateWindow (GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_DIMENSION_WIDTH, WINDOW_DIMENSION_HEIGHT, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

	char fileName[30];

	for (i = 0; i < N_SHIPS; i++)
	{
		sprintf (fileName, "images/ships/right/%d.bmp", i);
		shipImage[i] = SDL_CreateTextureFromSurface (renderer, SDL_LoadBMP (fileName));
	}
}

void displayStart ()
{
	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	SDL_RenderClear (renderer);

	drawBoard (1, otherPlayer());
	drawBoard (0, currentPlayer());
}

void displayGame ()
{
	SDL_Event event;

	int endGame = 0;

	while (!endGame)
	{
		if (SDL_PollEvent (&event) > 0)
		{
			switch (event.type)
			{
				case SDL_QUIT:
					endGame = 1;
					break;
			}

			if (game.round == 0)
				displayStart();

			SDL_RenderPresent (renderer);
			SDL_UpdateWindowSurface (window);
		}
	}
}

void quitInterface ()
{
	SDL_Quit();
}

#endif	/* if GRAPHIQUE == 1 */