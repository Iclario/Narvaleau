#ifndef INTERFACE_H
#define INTERFACE_H

#include "game.h"

#define GRAPHIQUE 0

#define WINDOW_DIMENSION_HEIGHT 800
#define SQUARE_SIZE				30
#define WINDOW_DIMENSION_WIDTH	(SQUARE_SIZE * (BOARD_SIZE + 10))

void initInterface ();
void displayGame ();
void quitInterface ();

#endif	// ifndef INTERFACE_H