#ifndef GAME_H
#define GAME_H

#define GAME_NAME "Naval'eau"

#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define F 6
#define G 7
#define H 8
#define I 9
#define J 10
#define K 11
#define L 12
#define M 13
#define N 14
#define O 15
#define P 16
#define Q 17
#define R 18
#define S 19
#define T 20
#define U 21
#define V 22
#define W 23
#define X 24
#define Y 25
#define Z 26

#define BOARD_SIZE_MAX 26
#define BOARD_SIZE	   10

typedef struct BOARD
{
	int ship[BOARD_SIZE][BOARD_SIZE];

	/*
	 * 0 - No ship
	 * 1 - Carrier    (5)
	 * 2 - Battleship (4)
	 * 3 - Cruiser    (3)
	 * 4 - Submarine  (3)
	 * 5 - Destroyer  (2)
	 */

	int flag[BOARD_SIZE][BOARD_SIZE];

	/*
	 * 0 - No flag
	 * 1 - Personnal flag
	 */

	int shot[BOARD_SIZE][BOARD_SIZE];

	/*
	 * 0 - No shoot
	 * 1 - Missed shoot
	 * 2 - Hit shoot
	 */
} Board;

typedef struct COORDINATES
{
	int number;
	int letter;
} Coordinates;

Board player1;
Board player2;

int player;
int edit;


void initGame ();


#endif	// ifndef GAME_H