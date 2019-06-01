#ifndef GAME_H
#define GAME_H

#define GAME_NAME "Naval'eau"

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9
#define K 10
#define L 11
#define M 12
#define N 13
#define O 14
#define P 15
#define Q 16
#define R 17
#define S 18
#define T 19
#define U 20
#define V 21
#define W 22
#define X 23
#define Y 24
#define Z 25

#define BOARD_SIZE_MIN 10
#define BOARD_SIZE_MAX 26
#define BOARD_SIZE	   10
#define N_SHIPS		   5

typedef enum SHIP_TYPE
{
	NO_SHIP	   = 0,
	CARRIER	   = 1,
	BATTLESHIP = 2,
	CRUISER	   = 3,
	SUBMARINE  = 4,
	DESTROYER  = 5
} ShipType;

typedef enum FLAG_TYPE
{
	NO_FLAG	  = 0,
	PERSONNAL = 1
} FlagType;

typedef enum SHOT_TYPE
{
	NO_SHOT = 0,
	MISSED	= 1,
	HIT		= 2
} ShotType;

typedef struct BOARD
{
	ShipType ship[BOARD_SIZE][BOARD_SIZE];
	FlagType flag[BOARD_SIZE][BOARD_SIZE];
	ShotType shot[BOARD_SIZE][BOARD_SIZE];
} Board;

typedef struct COORDINATES
{
	int number;
	int letter;
} Coordinates;

typedef enum PLAYERID
{
	ERROR	= 0,
	PLAYER1 = 1,
	PLAYER2 = 2
} PlayerId;

typedef struct PLAYER
{
	PlayerId id;
	Board *	 board;
	int		 isReady;
	int		 placeableShips[N_SHIPS];
} Player;

typedef enum DIRECTION
{
	BAS,
	GAUCHE,
	HAUT,
	DROITE
} Direction;

typedef struct GAME
{
	Player * player1;
	Player * player2;
	PlayerId current;
} Game;

Game game;

Player * currentPlayer ();
Player * otherPlayer ();
void initGame ();
int * shipIsPlaceable (Player * player, Coordinates pos, ShipType shipType);
void initShips (Player * player);
void nextPlayer ();
int allShipsPlaced (Player * player);
void placeShip (Player * player, Coordinates pos, int direction, ShipType shipType);
int getShipLength (ShipType choiceShip);
int isPlaying (Player * player);

#endif // ifndef GAME_H