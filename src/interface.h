#ifndef INTERFACE_H
#define INTERFACE_H

#include "game.h"

#define GRAPHIQUE 0

#define WINDOW_DIMENSION_HEIGHT 800
#define SQUARE_SIZE				30
#define PADDING_UP				150
#define PADDING_LEFT			50
#define BORDER_THICKNESS		5
#define WINDOW_DIMENSION_WIDTH	PADDING_LEFT + (SQUARE_SIZE * (BOARD_SIZE)) + 400

void initInterface ();
void displayGame ();
void quitInterface ();

#endif	// ifndef INTERFACE_H