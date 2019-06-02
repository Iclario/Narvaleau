#ifndef INTERFACE_H
#define INTERFACE_H

#include "game.h"

#define GRAPHIQUE 1

#if GRAPHIQUE == 0

#else

# include "gtk/gtk.h"

#endif

void initInterface ();
void displayGame ();

#if GRAPHIQUE == 0

void clear ();
void displayStart ();
void displayCenteredText (char * text);
void displayTextHead (char * text);
void displayTextHeadDouble (char * text);
void displayHeader ();
void displayBoard (Player * player);
void displayStartHeader ();
void displayGameHeader ();
void displayStartBoard ();
void displayGameBoard ();
void pressEnterToContinue ();

#else	// if GRAPHIQUE == 0

GtkApplication * app;
int status;

void activate (GtkApplication * app, gpointer user_data);

#endif	// if GRAPHIQUE == 0

#endif	// ifndef INTERFACE_H