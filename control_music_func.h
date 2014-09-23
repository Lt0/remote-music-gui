#ifndef CONTROL_MUSIC_FUNC_H
#define CONTROL_MUSIC_FUNC_H

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

// void func_button_music_start_server(GtkWidget *button);
// void func_button_music_exit_server(GtkWidget *button);

void func_button_music_play(GtkWidget *button);
void func_button_music_play_focus(GtkWidget *button);
gpointer func_button_music_play_start_play (gpointer data);
// void func_button_music_pause(GtkWidget *button);
// void func_button_music_unpause(GtkWidget *button);
void func_button_music_stop(GtkWidget *button);
void func_button_music_next(GtkWidget *button);
void func_button_music_pre(GtkWidget *button);
void func_button_music_pre_focus(GtkWidget *button);
void func_button_music_pre_leave(GtkWidget *button);

// void func_button_music_volume_up(GtkWidget *button);
void func_button_music_silence(GtkWidget *button);
void func_button_music_volume(GtkWidget *button);
// void func_button_music_get_list(GtkWidget *button);
void func_button_music_reset_list(GtkWidget *button, gpointer data);

int func_scale_music_process (GtkWidget *button);
int func_scale_music_process_press (GtkWidget *scale);
int test_funck(GtkWidget *widget);
int func_scale_music_process_focus (GtkWidget *button);

int func_label_music_info_state ();
int func_label_music_info_file ();
int func_label_music_info_title ();
int func_label_music_info_artist ();
int func_label_music_info_song_title ();
int func_label_music_info_total_time () ;
int func_label_music_info_bitrate ();
int func_label_music_info_avg_bitrate () ;
int func_label_music_info_rate () ;

int get_selected_mode ();
int func_switch_music_autonext ();
int func_switch_music_repeat ();
int func_switch_music_shuffle ();

int func_radio_button_music_mode_in_thread ();
gpointer func_radio_button_music_mode_for_thread (gpointer data);
int func_radio_button_music_mode ();

// int func_tree_view_music_list();
int func_selection_music_dir_list_clicked();
int func_selection_music_list_clicked();
int get_dir_list_iter_from_str(char *str, char *music_list[], int music_list_num);

#endif