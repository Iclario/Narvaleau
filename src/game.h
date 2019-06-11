#ifndef GAME_H
#define GAME_H

#define GAME_NAME "Naval'eau"

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

typedef enum DIRECTION
{
	RIGHT,
	DOWN
} Direction;

typedef struct SHIP
{
	ShipType  type;
	int		  master;	// 1: Master ship - 0: Not master ship
	Direction dir;		// The direction of the ship (only if master ship)
} Ship;

typedef struct BOARD
{
	Ship	 ship[BOARD_SIZE][BOARD_SIZE];
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
	NONE	= 0,
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

typedef struct GAME
{
	Player *	player1;
	Player *	player2;
	PlayerId	current;
	PlayerId	winner;
	int			round;
	Coordinates lastHit;
} Game;

Game game;

Player * currentPlayer ();
Player * otherPlayer ();
void initGame ();
void quitGame ();
int shipIsNotPlaceable (Player * player, Coordinates pos, Direction direction, ShipType shipType);
void initPlaceableShips (Player * player);
void nextPlayer ();
int allShipsPlaced (Player * player);
int placeShip (Player * player, Coordinates pos, Direction direction, ShipType shipType);
void placeShipsRandomly (Player * player);
int isPlaying (Player * player);
ShotType shootPlayer (Player * player, Coordinates pos);
int gameIsOver ();

#endif	// ifndef GAME_H