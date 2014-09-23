#ifndef CONTROL_MUSIC_COMMON_H
#define CONTROL_MUSICmake_COMMON_H

extern client_sock;
extern struct timeval recv_timeout;



int retry_connect_music_server();

int music_state_change(int state);
int init_music();
// int init_music_list(char *music_path, char files[BUFSIZ][BUFSIZ]);
	
int get_file_name (char *name, char *file);
char *tmp_get_file_name(char *file_name, char *path);
int get_music_state (char *state);
int music_change_mode(char option, char *mode);
int get_lyric_from_server(char *music_name);
int get_lyric_from_file(char *music_name);
int get_lyric_name_from_music_name(char lyric_name[], char music_name[]);
int get_music_name_from_lyric_name(char music_name[], char lyric_name[]);
int get_file_name_without_extension (char new_name, char *file_name);
int lyric_get_tags(char lyric_tags[BUFSIZ][BUFSIZ], char lyric[]);
int format_lyric(struct music_lyric_sentence *cur_lyric[], char lyric_buf[]);
int sort_lyric_data();
int convert_str_min_to_sec(char min[BUFSIZ], float *sec);
int load_cur_lyric();
int lyric_init_data();
// int analy_config_music_in_thread();
// gpointer analy_config_music_for_thread();
// int analy_config_music();
// int word_is_option(char *word);
int config_format_play_mode(char *mode_str);


void test_func();

#endif