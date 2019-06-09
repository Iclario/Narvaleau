#ifndef UTILS_H
#define UTILS_H

int scanint ();
const char * shipName (ShipType shipType);
Coordinates getPosFromString (char * posChar);
char * getStringFromPos (char * buffer, Coordinates pos);
const char * directionName (Direction dir);
int positionIsInBound (Coordinates pos);
int directionIsInBound (Direction dir);
int shipTypeIsInBound (ShipType shipType);
int randInBounds (int a, int b);
const char * getStringFromShot (ShotType shot);

#endif	// ifndef UTILS_H