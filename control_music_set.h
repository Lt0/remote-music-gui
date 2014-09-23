#ifndef CONTROL_MUSIC_SET_H
#define CONTROL_MUSIC_SET_H

extern int client_sock;

void set_label_music_info_state ();
void set_label_music_info_file ();
void set_label_music_info_title ();
void set_label_music_info_artist ();
void set_label_music_info_song_title ();
void set_label_music_info_total_time ();
void set_label_music_info_bitrate ();
void set_label_music_info_avg_bitrate ();
void set_label_music_info_rate ();
// void set_button_music_start_server(GtkWidget *button) ;
// void set_button_music_exit_server(GtkWidget *button);
void set_button_music_play(GtkWidget *button);
// void set_button_music_pause(GtkWidget *button);
// void set_button_music_unpause(GtkWidget *button);
void set_button_music_stop(GtkWidget *button);
void set_button_music_next(GtkWidget *button);
void set_button_music_pre(GtkWidget *button);
// void set_button_music_volume_up(GtkWidget *button);
void set_button_music_silence(GtkWidget *button);
void set_button_music_volume(GtkWidget *button);
void set_button_music_reset_list(GtkWidget *button);
void set_button_music_delete_path(GtkWidget *button);
void set_button_music_choose_path(GtkWidget *button);

void set_button_music_process(GtkWidget *button);
void set_switch_music_autonext ();
void set_switch_music_repeat ();
void set_switch_music_shuffle ();
void set_radio_button_music_mode ();

void set_tree_view_music_dir_list();
void set_tree_view_music_list ();

#endif