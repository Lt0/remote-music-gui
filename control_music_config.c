#include <gtk/gtk.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>
#include "control_music.h"
#include "control_music_config.h"

int analy_config_music() {
	int word_num;
	char *config_lines[50];
	
	word_num = split_lines_from_file(config_music_file_path, config_lines);
	
// 	printf("there are %d lines in config file\n", word_num);
	
	char *option_value[word_num];
	int option_iter;
	int i = 0;
	for (i = 0; i < word_num; i++) {
// 		printf("formatting: %s\n", config_lines[i]);
		config_format_line_and_save(config_lines[i]);
// 		free(config_lines[i]);
// 		printf("fred: %s\n", config_lines[i]);
	}
	printf("cur_config_music.music_server_ip: %s\n", cur_config_music.music_server_ip);
	printf("cur_config_music.socket_port: %d\n", cur_config_music.socket_port);
	printf("cur_config_music.lyric_save_path: %s\n", cur_config_music.lyric_save_path);
	return 0;
}

int config_format_line_and_save(char *line) {
	char *options[] = {"MUSIC_SERVER_IP", "SOCKET_PORT", "LYRIC_SAVE_PATH"};
	int config_artr_num = 3;
	char *words_of_line[strlen(line)];
	int words_num;
	int option_iter;
	int met_option = 0;
	int i = 0;
	if ((words_num = config_split_words(line, words_of_line)) <= 0) {
		return -1;
	}
// 	printf("splited line: %s\n%d words", line, words_num);
	for (i = 0; i < words_num; i++) {
// 		printf("checking word: %s\n", words_of_line[i]);
		if ((option_iter = word_is_option(words_of_line[i], options, config_artr_num)) >= 0) {
			if (++i > words_num) {
				break;
			}
			if (option_iter == 0) {
// 			      printf("formatting play mode\n");
			      config_format_music_server_ip(words_of_line, words_num, i);
			      met_option = 1;
// 			      printf("formated play mode\n");
			      break;
			} 
			if (option_iter == 1) {
// 			      printf("formatting music_path\n");
			      config_format_socket_port(words_of_line[i]);
			      met_option = 1;
			      break;
			}
			if (option_iter == 2) {
// 				printf("formating socket_port: %s\n", words_of_line[i]);
				config_format_music_lyric_save_path(words_of_line, words_num, i);
				met_option = 1;
				break;
			}
		}
	}
	for(i = 0; i < words_num; i++) {
		free(words_of_line[i]);
	}
	if (met_option == 1) {
		return 0;
	}
	return -1;
}

int config_format_music_server_ip(char *words[], int words_num, int start_iter) {
	char *tmp_str;
	int is_fist = 1;
	if ((tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
	memset(tmp_str, '\0', BUFSIZ);
	for (start_iter; start_iter < words_num; start_iter++) {
		if (is_fist == 1) {
			strcat(tmp_str, words[start_iter]);
			is_fist == 0;
			continue;
		}
		strcat(tmp_str, " ");
		strcat(tmp_str, words[start_iter]);
	}
	if ((cur_config_music.music_server_ip = malloc(strlen(tmp_str))) == NULL) {
		free(tmp_str);
		return -1;
	}
	strcpy(cur_config_music.music_server_ip, tmp_str);
	free(tmp_str);
	return 0;
}

int config_format_socket_port(char *port_str) {
	cur_config_music.socket_port = atoi(port_str);
	return 0;
}

int config_format_music_lyric_save_path(char *words[], int words_num, int start_iter) {
	char *tmp_str;
	int is_fist = 1;
	if ((tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
	memset(tmp_str, '\0', BUFSIZ);
	for (start_iter; start_iter < words_num; start_iter++) {
		if (is_fist == 1) {
			strcat(tmp_str, words[start_iter]);
			is_fist == 0;
			continue;
		}
		strcat(tmp_str, " ");
		strcat(tmp_str, words[start_iter]);
	}
	if ((cur_config_music.lyric_save_path = malloc(strlen(tmp_str))) == NULL) {
		free(tmp_str);
		return -1;
	}
	strcpy(cur_config_music.lyric_save_path, tmp_str);
	free(tmp_str);
	return 0;
}

int word_is_option(char *word, char *options[], int option_num) {
	int i;
	for (i = 0; i < option_num; i++) {
		if (!strcmp(options[i], word)) {
			return i;
		}
	}
	return -1;
}

int split_lines_from_file(char *path, char *lines[]) {
	FILE *file;
	char *buf;
	int num;
	if (access(path, F_OK) != 0) {
		printf("ERROR: split_lines_from_file error: %s.\n", path);
		perror("ERROR:");
		return -1;
	}
	if (access(path, R_OK) != 0) {
		printf("split_lines_from_file error:  %s.\n", path);
		perror("ERROR:");
		return -1;
	}
	file = fopen(path, "a+");
	if ((buf = malloc(1024*4)) == NULL) {
		return -1;
	}
	memset(buf, '\0', 1024 * 4);
	fread(buf, 1024, 4, file);
	fclose(file);
	num = split_lines(buf, lines);
	free(buf);
	return num;
}

int config_split_words(char *buf, char *words[]) {
// 	printf("buf: %s\n", buf);
	char *split_words_tmp_str;
	int i, j, k, changed;
	j = 0;
	k = 0;
	changed = 0;
	if ((split_words_tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
// 	for (i = 0; i<sizeof(split_words_buf) && *(buf + i) != '\0'; i++) {
	for (i = 0; i<strlen(buf) && *(buf + i) != '\0'; i++) {
// 		printf("i: %d\n", i);
// 		printf("split_words_buf[%d]: %c\n", i, *(buf + i));
		while (*(buf + i) != ' ' && *(buf + i) != '\n' && *(buf + i) != '\0' && *(buf + i) != ':') {
// 			printf("split_words_buf[%d]: %c\n", i, *(buf + i));
			*(split_words_tmp_str + j) = *(buf + i);
// 			printf("split_words_tmp_str[%d]: %c\n", j, split_words_tmp_str[j]);
			i++;
			j++;
			changed = 1;
		}
		if (changed != 0) {
// 			printf("changed: %d\n", changed);
			if ((words[k] = malloc(strlen(split_words_tmp_str) + 1)) == NULL) {
				printf("error: malloc for words[%d] failed\n", k);
				free(split_words_tmp_str);
				return k;
			}
// 			printf("malloc for words[%d]\n", k);
			*(split_words_tmp_str + j) = '\0';
			memset (words[k], '\0', (strlen(split_words_tmp_str) + 1));
// 			printf("split_words_tmp_str: %s\n", split_words_tmp_str);
			strcpy(words[k], split_words_tmp_str);
// 			printf("words[%d]: %s\n", k, words[k]);
			memset (split_words_tmp_str, '\0', BUFSIZ);
			j = 0;
			k++;
			changed = 0;
		}
	}
	free(split_words_tmp_str);
// 	printf("split_words finished\n");
	return k;
}