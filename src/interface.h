#ifndef INTERFACE_H
#define INTERFACE_H

#define GRAPHIQUE 0

void clear ();
void displayCenteredText (char * text);
void displayTextHead (char * text);
void displayTextHeadDouble (char * text);
void displayHeader ();
void initInterface ();
void displayBoard (Player * player);
void displayStartHeader ();
void displayGameHeader ();
void displayStartBoard ();
void displayStart ();
void displayGameBoard ();
void displayGame ();
void pause ();

#endif	// ifndef INTERFACE_H