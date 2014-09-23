#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "control_music.h"
#include "common.h"
#include "control_music_data.h"


int retry_connect_music_server() {

}

int unconnect_music_server() {
	
}

//初始化播放器界面所需要的全局变量，并启动播放状态刷新、歌词刷新线程
int init_music() {
	//设置配置路径
// 	config_music_file_path = strdup("./config/config_music.txt");
	
	//分析并设置配置变量
	
	if ((client_sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	}
	client_music_info.play_path = -1;
// 	get_music_dirs_from_server();
	g_thread_new(NULL, data_update_client_music_info_for_thread, NULL);
}


//获取路径中的文件名
int get_file_name (char name[], char *file) {
	int i = strlen (file) - 1;
	if (i < 1) {
// 		printf("file path length less than 1\n");
		name[0] = '\0';
		return -1;
	}
// 	printf("file is: %s\n", file);
// 	printf("file len is: %ld\n", strlen(file));
	char tmp_file_str[BUFSIZ];
	
	int len_name;
	
	strcpy (tmp_file_str, file);
	if (tmp_file_str[i] == '/') {
	  tmp_file_str[--i] == '\0';
	}
	while (tmp_file_str[i] != '/') {
	  i--;
	}
	len_name = strlen(file) - 1 - i;
	if (len_name >= BUFSIZ) {
		printf("file name too long\n");
		return -1;
	}
// 	printf("len_name is: %d\n", len_name);
	char tmp_name_str[len_name + 1];
	int j;
	for (j = 0; j < len_name; j++) {
		tmp_name_str[j] = tmp_file_str[++i];
	}
	tmp_name_str[len_name] = '\0';
// 	printf("tmp_name_str is: %s\n", tmp_name_str);

	strcpy(name, tmp_name_str);
	name[len_name] = '\0';
// 	printf("name is: %s\n", name);
	return len_name;
	
}

// int get_last_dir(char *dir, char *path) {
//   int i = strlen(path);
//   char tmp_str[strlen(path) + 1];
//   strcpy(tmp_str, path);
//   if (tmp_str[])
//   }
// }

char *tmp_get_file_name(char *file_name, char *path) {
// 	printf("path_name: %s\n");
	int i = strlen(path) - 1;
// 	printf("i: %d\n", strlen(path));
	if (strlen(path) < 1) {
		return NULL;
	}
	while (i >= 0 && *(path + i) != '/') {
// 		printf("*(path + i): %c\n",*(path + i));
		i--;
	}
	if ((file_name = malloc(strlen(path) - i)) == NULL) {
		perror("malloc for file_name failed");
		return NULL;
	}
	memset(file_name, '\0', sizeof(file_name));
	int k = 0;
// 	printf("file_name len in path: %d\n", strlen(path) - i);
// 	printf("sizeof file_name: %d\nstrlen of path: %d\n", sizeof(file_name), strlen(path));
	for (k = 0; i < strlen(path); k ++) {
// 		printf("k: %d\n", k);
		i++;
		*(file_name + k) = *(path + i);
// 		printf("*(file_name + k): %c\n*(path + i): %c\n",*(file_name + k) , *(path + i));
	}
// 	printf("file_name: %s\n", file_name);
	return file_name;
}

int get_music_state (char *state) {
	if (!strcmp(state, "PLAY")) {
		printf("current state is PLAY\n");
		return state_play;
	} else if (!strcmp(state, "PAUSE")) {
		printf("current state is PAUSE\n");
		return state_pause;
	} else if (!strcmp (state, "STOP")) {
		printf("current state is STOP\n");
		return state_stop;
	} else {
		printf("current state is SERVER_STOP\n");
		return state_server_stop;
	}
	return -1;
}

int music_state_change(int state) {
	int res;
	switch (state) {
		case state_play:
			//printf("music state change to play\n");
			strcpy(client_music_info.state, "PLAY");
			//gui_update_music_state_change (state_play);
			//gui_update_music_info_play ();
			break;
		case state_pause:
			//printf("music state change to pause\n");
			strcpy(client_music_info.state, "PAUSE");
			gui_update_music_state_change (state_pause);
			break;
		case state_unpause:
			//printf("music state change to unpause\n");
			strcpy(client_music_info.state, "PLAY");
			gui_update_music_state_change (state_unpause);
			break;
		case state_stop:
			//printf("music state change to stop\n");
			strcpy(client_music_info.state, "STOP");
			gui_update_music_state_change (state_stop);
			break;
		case state_server_stop:
			printf("music state change to server_stop\n");
			strcpy(client_music_info.state, "SERVER STOP");
			//gui_update_music_state_change (state_server_stop);
			 break;
		case state_server_start:
			  strcpy(client_music_info.state, "SERVER START");
			  //printf("music state change to server_start\n");
			 gui_update_music_state_change (state_server_start);
			break;
		default:
			printf("unknown state!\n");
	}
}

int music_change_mode(char option, char *mode) {
	if ((strlen(mode)) > 8) {
		printf("invalid mode\n");
		return -1;
	}
	char tmp_str[30] = {'m', 'o', 'c', 'p', ' ', '-', ' ', ' ',};
	tmp_str[6] = option;
	strcat(tmp_str, mode);
	//printf("tmp_str is: %s\n", tmp_str);
	send(client_sock, tmp_str, 30, 0);
	return 0;
}

int get_lyric_from_server(char *music_name) {

  
}

int get_lyric_from_file(char *music_name) {
	memset(cur_lyric_name, '\0', BUFSIZ);
	int fread_len;
	get_lyric_name_from_music_name(cur_lyric_name, music_name);
	memset(local_lyric_folder, '\0', sizeof(local_lyric_folder));
	memset(lyric_buf,'\0', sizeof(lyric_buf));
// 	strcat(local_lyric_folder, cur_config_music.lyric_save_path);
	strcat(local_lyric_folder, cur_config_music.lyric_save_path);
	strcat(local_lyric_folder, cur_lyric_name);
	
	if (access(local_lyric_folder, F_OK) != 0) {
		cur_lyric_file_existed = FALSE;
		printf("File not found: %s\n", local_lyric_folder);
		return -1;
	}
	cur_lyric_file_existed = TRUE;
      	lyric_file = fopen(local_lyric_folder, "r");
	fread_len = fread(lyric_buf, 1024, 4, lyric_file);
	fclose(lyric_file);
	return 0;
  
}

int get_lyric_name_from_music_name(char lyric_name[], char *music_name){
	int music_name_len = strlen(music_name) - 1;
	memset(lyric_name, 0, sizeof(lyric_name));
	strcpy(lyric_name, music_name);
	while (lyric_name[music_name_len] != '.') {
		music_name_len--;
		if (music_name_len == 0) {
// 		  printf("threr is no '.' in the music_name\n");
		  return -1;
		}
	}
	lyric_name[music_name_len + 1] = 'l';
	lyric_name[music_name_len + 2] = 'r';
	lyric_name[music_name_len + 3] = 'c';
	lyric_name[music_name_len + 4] = '\0';
	
	return 0;
}

int get_file_name_without_extension (char new_name[], char file_name[]) {
	char tmp_str[BUFSIZ];
	strcpy(tmp_str, file_name);
	int i = strlen(file_name) - 1;
	if (strlen(file_name) < 1) {
		return -1;
	}
	gboolean met_point = FALSE;
	for (i; i >= 0; i--) {
		if (tmp_str[i] == '.') {
			met_point = TRUE;
			new_name[i] = '\0';
			i--;
		}
		if (met_point == TRUE) {
			new_name[i] = tmp_str[i];
		}
		  
	 }
// 	 printf("new_str: %s\n", new_name);
	 if (met_point == FALSE) {
		return -1;
	 }
	 return 0;
}

int get_music_name_from_lyric_name(char music_name[], char lyric_name[]){
	int lyric_name_len = strlen(lyric_name) - 1;
	memset(music_name, 0, sizeof(music_name));
	strcpy(music_name, lyric_name);
	while (music_name[lyric_name_len] != '.') {
		lyric_name_len--;
		if (lyric_name_len == 0) {
// 		  printf("threr is no '.' in the lyric_name\n");
		  return -1;
		}
	}
	music_name[lyric_name_len + 1] = 'm';
	music_name[lyric_name_len + 2] = 'p';
	music_name[lyric_name_len + 3] = '3';
	music_name[lyric_name_len + 4] = '\0';
	
	return 0;
}

int lyric_get_tags(char lyric_tags[BUFSIZ][BUFSIZ], char lyric[]) {
	memset(lyric_tags, 0, BUFSIZ*BUFSIZ);
	int i = 0;
	int j = 0;
	int k = 0;
	
	for (i; i < strlen(lyric); i++) {
// 		printf("lyric[i]: %c\n", lyric[i]);
		if (lyric[i] == '[' ) {
// 			printf("lyric[%d]: %c\nin copying\n", i, lyric[i]);
			i++;
// 			printf("lyric[%d]: %c\n", i, lyric[i]);
			for (i; lyric[i] != ']'; i++) {
				lyric_tags[j][k] = lyric[i];
// 				printf("lyric_tags[%d][%d] is: %c\n", j, k, lyric_tags[j][k]);
				k++;
// 				printf("*********%c", lyric[i]);
			  
			}
			if (k > 0) {
// 			    lyric_tags[j][k] = '0';
// 			    printf("lyric_tags[%d] is: %s\n", j, lyric_tags[j]);
			    j++;
			    k = 0;
			}
			
		}
	}
	return 0;
  
}

int format_lyric(struct music_lyric_sentence cur_lyric[], char lyric_buf[]) {
	int i = 0;
	int j = 0;
	int k = 0;
	int repeat_time = 0;
	char tmp_str[BUFSIZ];
	float sec;
	for (i; i < strlen(lyric_buf); i++) {
		if (lyric_buf[i] == '[') {
			i++;
			if (lyric_buf[i] == 't' || lyric_buf[i] == 'b' || lyric_buf[i] == 'a') {
// 				printf("获取概述\n");
				memset(tmp_str, '\0',  BUFSIZ);
				cur_lyric[j].time = -1.0;
				k = 0;
				for (i; lyric_buf[i] != ']'; i++) {
					tmp_str[k] = lyric_buf[i];
					k++;
				}
				strcpy(cur_lyric[j].sentence, tmp_str);
				tmp_cur_lyric[j].sentence =  g_convert (cur_lyric[j].sentence, -1, "UTF-8", "GB2312", NULL, NULL, NULL);
				j++;
				continue;
			}
// 			printf("获取时间标签");
			k = 0;
			for (i; lyric_buf[i] != ']'; i++) {
				tmp_str[k] = lyric_buf[i];
				k++;
			}
			tmp_str[k] =  '\0';
			convert_str_min_to_sec(tmp_str, &sec);
			cur_lyric[j].time = sec;
			tmp_cur_lyric[j].time = sec;
			j ++;
			repeat_time ++;
		}
		if (lyric_buf[i] == ']' && lyric_buf[i + 1] != '[') {
			i++;
// 			printf("获取单句歌词");
			k = 0;
			memset(tmp_str, '\0',  BUFSIZ);
			for (i; lyric_buf[i] != '[' && lyric_buf[i] != '\0' && lyric_buf[i] != '\n'; i++) {
				tmp_str[k] = lyric_buf[i];
				k++;
			}
			tmp_str[k] =  '\0';
			for (; repeat_time > 0; repeat_time--) {
				strcpy(cur_lyric[j - repeat_time].sentence, tmp_str);
				tmp_cur_lyric[j - repeat_time].sentence =  g_convert (cur_lyric[j - repeat_time].sentence, -1, "UTF-8", "GB2312", NULL, NULL, NULL);
			}
			i--;
		}
	}
	return j;//return lyric_valid_iter
}

int sort_lyric_data() {
	struct tmp_music_lyric_sentence tmp_sentence;
	int i, j, k;
	for (i = 0; i < lyric_valid_iter; i++) {
		for (j = 0; j < lyric_valid_iter; j++) {
			if (tmp_cur_lyric[j].time > tmp_cur_lyric[j + 1].time) {
				tmp_sentence.time = tmp_cur_lyric[j].time;
				tmp_sentence.sentence = tmp_cur_lyric[j].sentence;
				
				tmp_cur_lyric[j].time = tmp_cur_lyric[j+1].time;
				tmp_cur_lyric[j].sentence = tmp_cur_lyric[j+1].sentence;
				
				tmp_cur_lyric[j+1].time = tmp_sentence.time;
				tmp_cur_lyric[j+1].sentence = tmp_sentence.sentence;
			}
		}
	}
	i = 0;
	return 0;
}

int convert_str_min_to_sec(char min[BUFSIZ], float *sec) {
	char tmp_str[6];
	float time[3] = {0, 0, 0};
	float time_sec = -1;
	int i = strlen(min) - 1;
	int k = 2;
	int j = 5;
	for (i; i >=0; i--) {
// 		printf("nmin[%d]: %c\n", i, min[i]);
		j = 5;
		memset(tmp_str, 0, 5);
		for (i; min[i] != ':' && i >= 0; i--) {
// 			printf("min[%d]: %c\n", i, min[i]);
			if (j >= 0) {
				tmp_str[j] = min[i];
// 				printf("tmp_str[%d]: %c\n", j, tmp_str[j]);
				j--;
			}
		}
		for (j; j >= 0; j--) {
		  tmp_str[j] = '0';
		}
// 		printf("tmp_str: %s\n", tmp_str);
		if (k >= 0) {
			time[k] = atof(tmp_str);
// 			printf("time[%d]: %f\n", k, time[k]);
			k--;
		} else {
// 			printf("the time is too long\n");
			return -1;
			break;
		}
		
		
	}
	time_sec = time[0] * 60 *60 + time[1] * 60 + time[2];
// 	printf("convert %s to %f\n", min, time_sec);
	*sec = time_sec;
	return 0;
// 	return time_sec;
}


int load_cur_lyric() {
	lyric_init_data();
	char tmp_name[BUFSIZ];
	get_file_name(tmp_name, client_music_info.file);
	if (get_lyric_from_file (tmp_name) < 0) {
// 		printf("error: can not get_lyric_from_file\n");
		return -1;
	}

	lyric_valid_iter = format_lyric(cur_lyric, lyric_buf);
// 	printf("valid iter: %d\n", lyric_valid_iter);
	return 0;
}

int lyric_init_data() {
	int i = 0;
	for (i; i < lyric_valid_iter; i++) {
		cur_lyric[i].time = 0;
// 		printf("memset lyric data: %d\n", i);
		memset(cur_lyric[i].sentence, '\0', 1024);
	}
	return 0;
}
/*


gpointer analy_config_music_for_thread() {
	analy_config_music();
	return NULL;
}

int analy_config_music_in_thread() {
	g_thread_new(NULL, analy_config_music_for_thread, NULL);
	return 0;
}

int analy_config_music() {
	char *config_file_path = "./config/config_music.txt\0";
	int word_num;
	char *config_words[50];
	
	word_num = split_words_from_file(config_file_path, config_words, 50);
	
	char *option_value[word_num];
	int option_iter;
	int i = 0;
	for (i = 0; i < word_num; i++) {
		if ((option_iter = word_is_option(config_words[i])) >= 0) {
			free(config_words[i]);
			option_value[option_iter] = config_words[++i];
		}
	}
	config_format_play_mode(option_value[0]);
// 	printf("get playmode: %d\n", cur_config_music.play_mode);
	free(option_value[0]);
	cur_config_music.lyric_save_path = option_value[1];
// 	printf("get lyric_save_path: %s\n", cur_config_music.lyric_save_path);
	return 0;
	
}

int word_is_option(char *word) {
	int option_num = 2;
	char *options[] = {"PLAYMODE:", "LYRIC_SAVE_PATH:"};
	int i;
	for (i = 0; i < option_num; i++) {
		if (!strcmp(options[i], word)) {
			return i;
		}
	}
	return -1;
}*/

// int config_format_play_mode(char *mode_str) {
// 	char *modes[] = {"SHUFFLE", "LOOP_LIST", "PLAY_LIST", "LOOP_ONE", "PLAY_ONE"};
// 	int i = 0;
// 	for (i = 0; i < 5; i++) {
// 		if (!strcmp(modes[i], mode_str)) {
// 			cur_config_music.play_mode = i;
// 			return i;
// 		}
// 	}
// 	return -1;
// }


void test_func() {
// 	analy_config_music();
	char *tmp_splited_words[BUFSIZ];
	int num = split_words(recv_buf, tmp_splited_words, BUFSIZ);
	int i = 0;
	for(i = 0; i < num; i++) {
		free(tmp_splited_words[i]);
	}
	printf("____\n");
}