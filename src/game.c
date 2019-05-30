#include <stdio.h>
#include "main.h"
#include "game.h"

void initGame ()
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			player1.ship[i][j] = 0;
			player2.ship[i][j] = 0;
			player1.flag[i][j] = 0;
			player2.flag[i][j] = 0;
			player1.shot[i][j] = 0;
			player2.shot[i][j] = 0;
		}
	}

	/* Test
	*  player1.ship[4][C] = 4;
	*  player1.ship[4][D] = 4;
	*  player1.ship[4][E] = 4;
	*  player1.flag[4][F] = 1;
	*  player1.shot[6][G] = 1;
	*  player1.shot[7][G] = 2;
	*
	*  player2.ship[4][C] = 4;
	*  player2.ship[4][D] = 4;
	*  player2.ship[4][E] = 4;
	*  player2.flag[4][F] = 1;
	*  player2.shot[6][G] = 1;
	*  player2.shot[7][G] = 2;
	*  Test */

	player = 1;
	edit   = 1;
}