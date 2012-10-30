#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gdk/gdkx.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"

GtkWidget *window;
GtkWidget *drawingarea;

GdkColor bg = {0, 0, 0, 0};

GtkWidget* create_mainwindow (int xres, int yres) {

	GtkWidget *box;

	GtkWidget *menubar;
  
	GtkWidget *filemenu;
	GtkWidget *file;
	GtkWidget *open;
	GtkWidget *sep1;
	GtkWidget *quit;
	
	GtkWidget *emulatormenu;
	GtkWidget *emulator;
	GtkWidget *cont;
	GtkWidget *pause;
	GtkWidget *sep2;
	GtkWidget *loadstate;
	GtkWidget *savestate;
	GtkWidget *sep3;
	GtkWidget *movieload;
	GtkWidget *movierecord;
	GtkWidget *moviestop;
	GtkWidget *sep4;
	GtkWidget *cheats;
	GtkWidget *sep5;
	GtkWidget *configuration;
	
	GtkWidget *configurationmenu;
	GtkWidget *configuration1;
	GtkWidget *videoconfig;
	GtkWidget *audioconfig;
	GtkWidget *inputconfig;
	GtkWidget *miscconfig;

	GtkWidget *helpmenu;
	GtkWidget *help;
	GtkWidget *about;
	
	GtkWidget *statusbar;
	
	GtkSettings *gtksettings;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Nestopia");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	menubar = gtk_menu_bar_new();

	filemenu = gtk_menu_new();
	emulatormenu = gtk_menu_new();
	configurationmenu = gtk_menu_new();
	helpmenu = gtk_menu_new();

	file = gtk_menu_item_new_with_label("File");
	open = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, NULL);
	sep1 = gtk_separator_menu_item_new();
	quit = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
	
	emulator = gtk_menu_item_new_with_label("Emulator");
	cont = gtk_image_menu_item_new_with_label("Continue");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(cont), gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_MENU));
	pause = gtk_image_menu_item_new_from_stock(GTK_STOCK_MEDIA_PAUSE, NULL);
	sep2 = gtk_separator_menu_item_new();
	loadstate = gtk_image_menu_item_new_with_label("Load State...");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(loadstate), gtk_image_new_from_stock(GTK_STOCK_GO_BACK, GTK_ICON_SIZE_MENU));
	savestate = gtk_image_menu_item_new_with_label("Save State...");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(savestate), gtk_image_new_from_stock(GTK_STOCK_SAVE, GTK_ICON_SIZE_MENU));
	sep3 = gtk_separator_menu_item_new();
	movieload = gtk_image_menu_item_new_with_label("Load Movie...");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(movieload), gtk_image_new_from_stock(GTK_STOCK_OPEN, GTK_ICON_SIZE_MENU));
	movierecord = gtk_image_menu_item_new_with_label("Record Movie...");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(movierecord), gtk_image_new_from_stock(GTK_STOCK_MEDIA_RECORD, GTK_ICON_SIZE_MENU));
	moviestop = gtk_image_menu_item_new_with_label("Stop Movie");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(moviestop), gtk_image_new_from_stock(GTK_STOCK_MEDIA_STOP, GTK_ICON_SIZE_MENU));
	sep4 = gtk_separator_menu_item_new();
	cheats = gtk_image_menu_item_new_with_label("Cheats...");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(cheats), gtk_image_new_from_stock(GTK_STOCK_DIALOG_WARNING, GTK_ICON_SIZE_MENU));
	sep5 = gtk_separator_menu_item_new();
	configuration = gtk_image_menu_item_new_with_label("Configuration...");
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(configuration), gtk_image_new_from_stock(GTK_STOCK_PREFERENCES, GTK_ICON_SIZE_MENU));
	
	configuration1 = gtk_menu_item_new_with_label("Config");
	videoconfig = gtk_menu_item_new_with_label("Video");
	audioconfig = gtk_menu_item_new_with_label("Audio");
	inputconfig = gtk_menu_item_new_with_label("Input");
	miscconfig = gtk_menu_item_new_with_label("Misc");
  
	help = gtk_menu_item_new_with_label("Help");
	about = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, NULL);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), sep1);
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(emulator), emulatormenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), cont);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), pause);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), sep2);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), loadstate);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), savestate);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), sep3);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), movieload);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), movierecord);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), moviestop);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), sep4);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), cheats);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), sep5);
	gtk_menu_shell_append(GTK_MENU_SHELL(emulatormenu), configuration);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(configuration1), configurationmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(configurationmenu), videoconfig);
	gtk_menu_shell_append(GTK_MENU_SHELL(configurationmenu), audioconfig);
	gtk_menu_shell_append(GTK_MENU_SHELL(configurationmenu), inputconfig);
	gtk_menu_shell_append(GTK_MENU_SHELL(configurationmenu), miscconfig);
  
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);
  
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), emulator);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), configuration1);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
	
	drawingarea = gtk_drawing_area_new();
	gtk_widget_set_size_request(drawingarea, xres, yres);
	
	statusbar = gtk_statusbar_new();
	
	gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), drawingarea, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box), statusbar, FALSE, FALSE, 0);

	g_signal_connect_swapped(G_OBJECT(window), "destroy",
		G_CALLBACK(on_mainwindow_destroy), NULL);

	g_signal_connect(G_OBJECT(open), "activate",
		G_CALLBACK(on_open_clicked), NULL);

	g_signal_connect(G_OBJECT(quit), "activate",
		G_CALLBACK(on_mainwindow_destroy), NULL);

	g_signal_connect(G_OBJECT(cont), "activate",
		G_CALLBACK(on_playbutton_clicked), NULL);

	//g_signal_connect(G_OBJECT(pause), "activate",
	//	G_CALLBACK(redraw_drawingarea), NULL);

	g_signal_connect(G_OBJECT(loadstate), "activate",
		G_CALLBACK(state_load), NULL);

	g_signal_connect(G_OBJECT(savestate), "activate",
		G_CALLBACK(state_save), NULL);
		
	g_signal_connect(G_OBJECT(movieload), "activate",
		G_CALLBACK(movie_load), NULL);
		
	g_signal_connect(G_OBJECT(movierecord), "activate",
		G_CALLBACK(movie_record), NULL);
		
	g_signal_connect(G_OBJECT(moviestop), "activate",
		G_CALLBACK(movie_stop), NULL);

	g_signal_connect(G_OBJECT(cheats), "activate",
		G_CALLBACK(on_cheatbutton_pressed), NULL);

	g_signal_connect(G_OBJECT(videoconfig), "activate",
		G_CALLBACK(create_videoconfig), NULL);

	g_signal_connect(G_OBJECT(audioconfig), "activate",
		G_CALLBACK(create_audioconfig), NULL);

	g_signal_connect(G_OBJECT(inputconfig), "activate",
		G_CALLBACK(create_inputconfig), NULL);

	g_signal_connect(G_OBJECT(miscconfig), "activate",
		G_CALLBACK(create_miscconfig), NULL);

	g_signal_connect(G_OBJECT(about), "activate",
		G_CALLBACK(create_about), NULL);
		
	gtksettings = gtk_settings_get_default();
	g_object_set(G_OBJECT(gtksettings), "gtk-application-prefer-dark-theme", TRUE, NULL);

	gtk_key_snooper_install(convertKeypress, NULL);

	gtk_widget_show_all(window);

	char SDL_windowhack[32];
	sprintf(SDL_windowhack, "SDL_WINDOWID=%ld", GDK_WINDOW_XID(gtk_widget_get_window(drawingarea)));
	set_window_id(SDL_windowhack);
	
	gtk_widget_modify_bg(drawingarea, GTK_STATE_NORMAL, &bg);

	return window;
}

void redraw_drawingarea(int xres, int yres) {
	gtk_widget_set_size_request(drawingarea, xres, yres);
	gtk_widget_modify_bg(drawingarea, GTK_STATE_NORMAL, &bg);
}
