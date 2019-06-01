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
	HIT		= 2,
	FLOWED	= 3
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
	int		 played;
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
	int		 round;
} Game;

Game game;

Player * currentPlayer ();
Player * otherPlayer ();
void initGame ();
int shipIsNotPlaceable (Player * player, Coordinates pos, Direction direction, ShipType shipType);
void initPlaceableShips (Player * player);
void nextPlayer ();
int allShipsPlaced (Player * player);
int placeShip (Player * player, Coordinates pos, Direction direction, ShipType shipType);
void placeShipsRandomly (Player * player);
int getShipLength (ShipType shipType);
int isPlaying (Player * player);
ShotType shootPlayer (Player * player, Coordinates pos);

#endif	// ifndef GAME_H