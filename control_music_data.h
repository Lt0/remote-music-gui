#ifndef CONTROL_MUSIC_DATA_H
#define CONTROL_MUSIC_DATA_H

#define FREQ_GET_DATA 400000

int data_update_music_state_change(int state);
int data_update_music_info(int state);
int data_update_music_info_play();
int data_update_music_info_pause();
int data_update_music_info_stop();
int data_update_music_info_server_start();
int data_update_music_info_server_stop();
int data_update_client_music_info (int sock, char info_buf[], struct music_info *info);
gpointer data_update_client_music_info_for_thread (gpointer data);
int get_music_info_from_server(int sock, char info_buf[]);
int format_music_info(char *info_buf, struct music_info *info);

int get_music_dirs_from_server(int force_update);
gpointer get_music_list_from_server_for_thread(gpointer data);
int get_music_list_from_server();
gpointer get_music_list_from_server_in_thread(gpointer data);

#endif