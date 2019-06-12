#include "interface.h"

#if GRAPHIQUE == 1

# include "game.h"
# include "utils.h"
# include <stdlib.h>
# include <stdio.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>

SDL_Texture * shipImage[2][N_SHIPS];

SDL_Window * window		  = NULL;
SDL_Renderer * renderer	  = NULL;
SDL_Surface * textSurface = NULL;
SDL_Texture * textTexture = NULL;

SDL_Rect rect;
SDL_Event event;

void displayText (char * text, int x, int y, int size)
{
	SDL_Color color = { 255, 255, 255, 255 };
	int w, h;

	TTF_Font * font = TTF_OpenFont ("fonts/Roboto/Roboto-Regular.ttf", size);

	textSurface = TTF_RenderText_Blended (font, text, color);
	TTF_CloseFont (font);

	textTexture = SDL_CreateTextureFromSurface (renderer, textSurface);

	SDL_QueryTexture (textTexture, NULL, NULL, &w, &h);
	SDL_Rect dest = { x, y, w, h };

	SDL_RenderCopy (renderer, textTexture, NULL, &dest);
}

void displayCenteredText (char * text, int y, int size)
{
	int w, h;

	TTF_Font * font = TTF_OpenFont ("fonts/Roboto/Roboto-Regular.ttf", size);

	TTF_SizeText (font, text, &w, &h);
	TTF_CloseFont (font);

	displayText (text, (WINDOW_DIMENSION_WIDTH - w) / 2.0, y, size);
}

void displayHeader ()
{
	displayCenteredText ("Bataille navale", 10, 30);
	displayCenteredText (GAME_NAME, 40, 30);
}

void displayStartHeader ()
{
	char buffer[10];

	sprintf (buffer, "Joueur %d", currentPlayer()->id);

	displayCenteredText ("Placement des navires", 80, 20);
	displayCenteredText (buffer, 100, 20);
}

void displayGameHeader ()
{
	char buffer[10];

	sprintf (buffer, "Tour %d", game.round);
	displayCenteredText (buffer, 80, 20);

	sprintf (buffer, "Joueur %d", currentPlayer()->id);
	displayCenteredText (buffer, 100, 20);
}

/*
 * Draws the board
 *
 * Arguments:
 * int upDown : Draws it up (0) or down (1)
 *
 */
void drawBoard (int upDown, Player * player)
{
	int i, j;
	SDL_Rect dest;

	rect.w = SQUARE_SIZE * BOARD_SIZE + 10;
	rect.h = SQUARE_SIZE * BOARD_SIZE + 10;
	rect.y = PADDING_UP + SQUARE_SIZE * upDown * (BOARD_SIZE + 1) - 5;
	rect.x = PADDING_LEFT - 5;

	if (player->id == game.current)
		SDL_SetRenderDrawColor (renderer, 0x00, 0x21, 0x71, 0xFF);
	else
		SDL_SetRenderDrawColor (renderer, 0x7F, 0x00, 0x00, 0xFF);

	SDL_RenderFillRect (renderer, &rect);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			rect.w = SQUARE_SIZE;
			rect.h = SQUARE_SIZE;
			rect.y = PADDING_UP + SQUARE_SIZE * upDown * (BOARD_SIZE + 1) + SQUARE_SIZE * i;
			rect.x = PADDING_LEFT + SQUARE_SIZE * j;

			if (player->id == game.current)
			{
				if ((j + i) % 2 == 0)
					SDL_SetRenderDrawColor (renderer, 0x21, 0x71, 0xA1, 0xFF);
				else
					SDL_SetRenderDrawColor (renderer, 0x00, 0x21, 0x71, 0xFF);
			}
			else
			{
				if ((j + i) % 2 == 0)
					SDL_SetRenderDrawColor (renderer, 0xB7, 0x1C, 0x1C, 0xFF);
				else
					SDL_SetRenderDrawColor (renderer, 0x7F, 0x00, 0x00, 0xFF);
			}

			SDL_RenderFillRect (renderer, &rect);
		}
	}

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (player->board->ship[i][j].type != NO_SHIP && player->board->ship[i][j].master == 1)
			{
				switch (player->board->ship[i][j].dir)
				{
					case RIGHT:
						dest.w = SQUARE_SIZE * getShipLength (player->board->ship[i][j].type);
						dest.h = SQUARE_SIZE;
						dest.y = PADDING_UP + SQUARE_SIZE * upDown * (BOARD_SIZE + 1) + SQUARE_SIZE * i;
						dest.x = PADDING_LEFT + SQUARE_SIZE * j;

						SDL_RenderCopy (renderer, shipImage[player->board->ship[i][j].dir][player->board->ship[i][j].type - 1], NULL, &dest);

						break;

					case DOWN:
						dest.w = SQUARE_SIZE;
						dest.h = SQUARE_SIZE * getShipLength (player->board->ship[i][j].type);
						dest.y = PADDING_UP + SQUARE_SIZE * upDown * (BOARD_SIZE + 1) + SQUARE_SIZE * i;
						dest.x = PADDING_LEFT + SQUARE_SIZE * j;

						SDL_RenderCopy (renderer, shipImage[player->board->ship[i][j].dir][player->board->ship[i][j].type - 1], NULL, &dest);

						break;

					default:
						break;
				}
			}
		}
	}
}	/* drawBoard */

void initInterface ()
{
	int i, j;

	SDL_Init (SDL_INIT_VIDEO);
	TTF_Init();

	window = SDL_CreateWindow (GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_DIMENSION_WIDTH, WINDOW_DIMENSION_HEIGHT, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

	char fileName[30];

	for (i = 0; i <= 1; i++)
	{
		for (j = 0; j < N_SHIPS; j++)
		{
			SDL_Surface * image = NULL;

			sprintf (fileName, "images/ships/%d/%d.bmp", i, j + 1);
			image			= SDL_LoadBMP (fileName);
			shipImage[i][j] = SDL_CreateTextureFromSurface (renderer, image);
			SDL_FreeSurface (image);
		}
	}
}

void displayShipChoice ()
{
	int i;
	SDL_Rect dest;

	for (i = 0; i < N_SHIPS; i++)
	{
		dest.w = 1.5 * SQUARE_SIZE * getShipLength (i + 1);
		dest.h = 1.5 * SQUARE_SIZE;
		dest.y = PADDING_UP + SQUARE_SIZE * (i * 2);
		dest.x = PADDING_LEFT + SQUARE_SIZE * (BOARD_SIZE + 3);

		SDL_RenderCopy (renderer, shipImage[0][i], NULL, &dest);
	}
}

void displayStart ()
{
	SDL_SetRenderDrawColor (renderer, 0x70, 0x70, 0x70, 0xFF);
	SDL_RenderClear (renderer);

	displayHeader();
	displayStartHeader();

	drawBoard (0, currentPlayer());
	displayShipChoice();
}

void displayGame ()
{
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

				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_WINDOWEVENT:
					displayStart();
					SDL_RenderPresent (renderer);
					SDL_UpdateWindowSurface (window);

					break;
			}
		}
	}
}

void quitInterface ()
{
	int i, j;

	TTF_Quit();

	for (i = 0; i <= 1; i++)
		for (j = 0; j < N_SHIPS; j++)
			SDL_DestroyTexture (shipImage[i][j]);

	SDL_DestroyRenderer (renderer);
	SDL_DestroyWindow (window);
	SDL_Quit();
}

#endif	/* if GRAPHIQUE == 1 */