#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include "control_music.h"
#include "control_music_func.h"
#include "control_music_gui.h"
#include "common.h"

// void set_label_music_info_state () {
// }
// 
// void set_label_music_info_file () {
// 	
// }
// 
// void set_label_music_info_title () {
// 	
// }
// 
// void set_label_music_info_artist () {
// 	
// }
// 
// void set_label_music_info_song_title () {
// 	
// }
// 
// void set_label_music_info_total_time () {
// 	
// }
// 
// void set_label_music_info_bitrate () {
// 	
// }
// 
// void set_label_music_info_avg_bitrate () {
// 	
// }
// 
// void set_label_music_info_rate () {
// 	
// }

// void set_button_music_start_server(GtkWidget *button) {
// 	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_start_server), NULL);
// }

// void set_button_music_exit_server(GtkWidget *button) {
// 	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_exit_server), NULL);
// }

void set_button_music_play(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_play), NULL);
	g_signal_connect((button), "enter", G_CALLBACK(test_funck), NULL);
}

// void set_button_music_pause(GtkWidget *button) {
// 	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_pause), NULL);
// }

// void set_button_music_unpause(GtkWidget *button) {
// 	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_unpause), NULL);
// }

void set_button_music_stop(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_stop), NULL);
	g_signal_connect((button), "enter", G_CALLBACK(test_funck), NULL);
}

void set_button_music_next(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_next), NULL);
	g_signal_connect((button), "enter", G_CALLBACK(test_funck), NULL);
}

void set_button_music_pre(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_pre), NULL);
	g_signal_connect((button), "enter", G_CALLBACK(test_funck), NULL);
	g_signal_connect((button), "focus-in-event", G_CALLBACK(func_button_music_pre_focus), NULL);
	g_signal_connect((button), "focus-out-event", G_CALLBACK(func_button_music_pre_leave), NULL);
}

// void set_button_music_volume_up(GtkWidget *button) {
// 	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_volume_up), NULL);
// }

void set_button_music_silence(GtkWidget *button) {
// 	gpointer data = (gpointer)button_volume;
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_silence), NULL);
}

void set_button_music_volume(GtkWidget *button) {
	g_signal_connect((button), "value-changed", G_CALLBACK(func_button_music_volume), NULL);
// 	g_signal_connect((button), "popdown", G_CALLBACK(func_button_music_volume), NULL);
// 	g_signal_connect((button), "popup", G_CALLBACK(func_button_music_volume), NULL);
}

void set_button_music_reset_list(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_reset_list), NULL);
}

void set_button_music_choose_path(GtkWidget *button) {
// 	g_signal_connect((button), "clicked", G_CALLBACK(func_button_music_choose_path), NULL);
}

void set_button_music_delete_path(GtkWidget *button) {
  
}

void set_scale_music_process(GtkWidget *scale) {
	//gtk_range_set_update_policy(GTK_RANGE(button), GTK_UPDATE_CONTINUOUS);
	//scale_music_process = gtk_scale_button_new (15, 0, 100, 1, NULL);
	//gtk_scale_set_digits (scale_music_process, 2);
	//gtk_scale_set_draw_value(GTK_SCALE(scale_music_process), TRUE);
	gtk_scale_set_draw_value (GTK_SCALE (scale_music_process), FALSE);
	//gtk_scale_set_value_pos (GTK_SCALE (scale_music_process), GTK_POS_TOP);
// 	g_signal_connect(scale, )
	g_signal_connect((scale), "button-release-event", G_CALLBACK(func_scale_music_process), NULL);
	//gtk_range_set_fill_level (GTK_RANGE(button), 50);
// 	g_signal_connect(scale, "pressed", G_CALLBACK(func_scale_music_process_press), NULL);
// 	g_signal_connect(scale, "move-slider", G_CALLBACK(test_funck), NULL);
// 	g_signal_connect((button), "focus", G_CALLBACK(func_scale_music_process_focus), NULL);
}

void set_switch_music_autonext () {
	
}

void set_switch_music_repeat () {
	
}

void set_switch_music_shuffle () {
	
}

void set_radio_button_music_mode () {
	
	g_signal_connect (radio_button_music_mode_shuffle, "toggled", G_CALLBACK (func_radio_button_music_mode), NULL);
	g_signal_connect (radio_button_music_mode_loop_list, "toggled", G_CALLBACK (func_radio_button_music_mode), NULL);
	g_signal_connect (radio_button_music_mode_play_list, "toggled", G_CALLBACK (func_radio_button_music_mode), NULL);
	g_signal_connect (radio_button_music_mode_loop_one, "toggled", G_CALLBACK (func_radio_button_music_mode), NULL);
// 	g_signal_connect (radio_button_music_mode_shuffle, "toggled", G_CALLBACK (func_radio_button_music_mode_in_thread ), NULL);
// 	g_signal_connect (radio_button_music_mode_loop_list, "toggled", G_CALLBACK (func_radio_button_music_mode_in_thread ), NULL);
// 	g_signal_connect (radio_button_music_mode_play_list, "toggled", G_CALLBACK (func_radio_button_music_mode_in_thread ), NULL);
// 	g_signal_connect (radio_button_music_mode_loop_one, "toggled", G_CALLBACK (func_radio_button_music_mode_in_thread ), NULL);
}

void set_tree_view_music_dir_list() {
	gtk_tree_selection_set_mode (selection_music_dir_list, GTK_SELECTION_SINGLE);
	g_signal_connect (G_OBJECT (selection_music_dir_list), "changed", G_CALLBACK (func_selection_music_dir_list_clicked), NULL );
}

void set_tree_view_music_list () {
	gtk_tree_selection_set_mode (selection_music_list, GTK_SELECTION_SINGLE);
	g_signal_connect (G_OBJECT (selection_music_list), "changed", G_CALLBACK (func_selection_music_list_clicked), NULL );
}

