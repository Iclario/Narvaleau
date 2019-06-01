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
void displayStart ();
void displayGame ();

#endif	// ifndef INTERFACE_H