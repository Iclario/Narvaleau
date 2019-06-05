#include "interface.h"

#if GRAPHIQUE == 1

# include "game.h"
# include "utils.h"
# include <stdlib.h>
# include <stdio.h>
# include <SDL2/SDL.h>

SDL_Window * window;
SDL_Renderer * renderer;
SDL_Surface * image;
SDL_Rect rect;

void drawBoard ()
{
	int w, h;

	SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
	SDL_RenderClear (renderer);

	SDL_GetWindowSize (window, &w, &h);

	rect.w = 300;
	rect.h = 300;
	rect.x = (w - rect.w) / 2;
	rect.y = 50;

	SDL_SetRenderDrawColor (renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect (renderer, &rect);

	SDL_RenderPresent (renderer);
}

void initInterface ()
{
	window = SDL_CreateWindow ("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_DIMENSION_WIDTH, WINDOW_DIMENSION_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
}

void displayStart ()
{
	drawBoard();
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

			SDL_UpdateWindowSurface (window);
		}
	}
}

void quitInterface ()
{
	SDL_Quit();
}

#endif	/* if GRAPHIQUE == 1 */