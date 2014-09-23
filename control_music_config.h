#ifndef CONTROL_MUSIC_CONFIG_H
#define CONTROL_MUSIC_CONFIG_H

int analy_config_music();
int config_format_line_and_save(char *line);
int config_format_music_server_ip(char *words[], int words_num, int start_iter);
int config_format_socket_port(char *port_str);
int config_format_music_lyric_save_path(char *words[], int words_num, int start_iter);
int word_is_option(char *word, char *options[], int option_num);
int split_lines_from_file(char *path, char *lines[]);
int config_split_words(char *buf, char *words[]);


#endif