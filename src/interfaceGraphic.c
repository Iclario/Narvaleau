#include "interface.h"

#if GRAPHIQUE == 1

# include "game.h"
# include "utils.h"
# include <gtk/gtk.h>

void initInterface ()
{
	app = gtk_application_new ("fr.iclario.navaleau", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
}

void displayGame ()
{
	status = g_application_run (G_APPLICATION (app), 0, NULL);
	g_object_unref (app);
}

void print_hello (GtkWidget * widget, gpointer data)
{
	g_print ("Hello World\n");
}

void activate (GtkApplication * app, gpointer user_data)
{
	GtkWidget * window;
	GtkWidget * grid;
	GtkWidget * button;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), GAME_NAME);
	gtk_container_set_border_width (GTK_CONTAINER (window), 10);

	grid = gtk_grid_new();
	gtk_container_add (GTK_CONTAINER (window), grid);

	button = gtk_button_new_with_label ("Button 1");
	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

	button = gtk_button_new_with_label ("Button 2");
	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

	button = gtk_button_new_with_label ("Button 3");
	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);

	button = gtk_button_new_with_label ("Quit");
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 3, 1);

	gtk_widget_show_all (window);
}

#endif	/* if GRAPHIQUE == 1 */