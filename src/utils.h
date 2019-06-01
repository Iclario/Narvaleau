#ifndef UTILS_H
#define UTILS_H

int scanint ();
const char * shipName (ShipType shipType);
Coordinates getPosFromString (char * posChar);
char * getStringFromPos (Coordinates pos);
const char * directionName(Direction dir);
#endif