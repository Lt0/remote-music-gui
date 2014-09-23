#ifndef CONTROL_MUSIC_GUI_H
#define CONTROL_MUSIC_GUI_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include "control_music.h"
#include "common.h"
#include "control_music_data.h"

extern client_sock;
extern struct timeval recv_timeout;

int gui_update_music_state_change (int state);

int gui_update_play_mode(int mode);

int gui_update_music_info();
int gui_update_music_info_play ();
int gui_update_music_info_pause ();
int gui_update_music_info_unpause ();
int gui_update_music_info_stop ();
int gui_update_music_info_server_stop ();
int gui_update_music_info_server_start ();

int gui_update_music_volume ();

int gui_update_music_process();

int gui_update_music_button_play();

 int gui_update_music_dir_list(int force_update);
 int gui_update_music_list();

gpointer gui_update_music_lyric_in_thread(gpointer data);
gpointer gui_update_music_lyric_for_thread(gpointer data);
int gui_update_music_lyric();
int lyric_check_data();

int music_gui_update_all();
gpointer music_gui_update_all_for_thread();
int music_gui_update_all_in_thread();
// int tmp_music_gui_update_all ();

#endif