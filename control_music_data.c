#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include "control_music.h"
#include "common_string.h"
#include "common.h"
#include "control_music_data.h"

struct music_info *client_music_info_ptr = &client_music_info;

int data_update_music_state_change(int state) {
  switch (state) {
    case state_play:
      data_update_music_info(state_play);
      break;
    case state_pause:
      data_update_music_info(state_pause);
      break;
      case state_stop:
      data_update_music_info(state_stop);
      break;
      case state_server_start:
      data_update_music_info(state_server_start);
      break;
      case state_server_stop:
      data_update_music_info(state_server_stop);
      break;
      default:
	printf("data_update_music_state_change error: unknow state.\n");
	return -1;
  }
  return 0;
}

int data_update_music_info(int state) {
  switch (state) {
    case state_play:
      data_update_music_info_play();
      break;
    case state_pause:
      data_update_music_info_pause();
      break;
      case state_stop:
      data_update_music_info_stop();
      break;
      case state_server_start:
      data_update_music_info_server_start();
      break;
      case state_server_stop:
      data_update_music_info_server_stop();
      break;
      default:
	printf("data_update_music_info error: unknow state.\n");
	return -1;
  }
  return 0;
}

int data_update_music_info_play() {
  strcpy(client_music_info_ptr->state, "PLAY");
  return 0;
}
int data_update_music_info_pause() {
  strcpy(client_music_info_ptr->state, "PAUSE");
  return 0;
}
int data_update_music_info_stop() {
  strcpy(client_music_info_ptr->state, "STOP");
  return 0;
}
int data_update_music_info_server_start() {
  strcpy(client_music_info_ptr->state, "SERVER_START");
  return 0;
}

//unsafe
int data_update_music_info_server_stop() {
  strcpy(client_music_info_ptr->state, "SERVER_STOP");
  strcpy(client_music_info_ptr->file, "\0");
  strcpy(client_music_info_ptr->title, "\0");
  strcpy(client_music_info_ptr->artist, "\0");
  strcpy(client_music_info_ptr->song_title, "\0");
  strcpy(client_music_info_ptr->album, "\0");
  strcpy(client_music_info_ptr->total_time, "\0");
  strcpy(client_music_info_ptr->time_left, "\0");
  client_music_info_ptr->total_sec = 0;
  strcpy(client_music_info_ptr->cur_time, "\0");
  client_music_info_ptr->cur_sec = 0; 	
  strcpy(client_music_info_ptr->bitrate, "\0");
  strcpy(client_music_info_ptr->avg_bitrate, "\0");
  strcpy(client_music_info_ptr->rate, "\0");
  return 0;
}

//刷新当前播放状态结构体中的数据
int data_update_client_music_info (int sock, char info_buf[], struct music_info *info) {
	if (get_music_info_from_server(sock, info_buf) < 0) {
// 		perror("error: get_music_info_from_server failed\n");
		return -1;
	}
	if (format_music_info(info_buf, &client_music_info) < 0) {
		perror("error: format_music_info");
		return -1;
	}
	return 0;
}

//为单独设计的更新当前播放状态的函数
gpointer data_update_client_music_info_for_thread (gpointer data) {
	play_info_sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port);
	static char *info_buf;
	info_buf = malloc(BUFSIZ);
	memset(info_buf, 0, BUFSIZ);
	while (1) {
		data_update_client_music_info (play_info_sock, info_buf, &client_music_info);
		g_usleep(FREQ_GET_DATA);
// 		g_usleep(10000);
	}
	free(info_buf);
}

//通过一个已经和服务器连接好的socket，从服务器端获取当前播放状态信息
int get_music_info_from_server(int sock, char info_buf[]) {
// 	printf("sock in get_music_info_from_server is: %d\n", sock);
	check_connection(sock);
	send_len = send(sock, "mocp -i", 7, 0);
// 	printf("send_len: %d\n", send_len);
	memset(info_buf, '\0', sizeof(info_buf));
// 	printf("get_music_info sock befor recv is: %d\n", sock);
	
	recv_timeout.tv_usec  = 500;
	gint tmp_sock = sock;
	int ret;
	FD_ZERO (&recv_readfd);
	FD_SET (sock, &recv_readfd);
	ret = select (sock + 1, &recv_readfd, NULL, NULL, &recv_timeout);
		switch (ret) {
		case -1 :
			perror ("get_music_info");
			return -1;
			break;
		case  0 :
			break;
		default :
			//printf("in switch of ret default\n");
			if (FD_ISSET(sock, &recv_readfd)) {
// 				printf ("recving ....\n");
// 				check_connection();
				recv_len = recv(sock, info_buf, BUFSIZ, 0);
			} else {
				//printf("can't read anything from music server....\n");
				return -1;
			}
	}
	
// 	recv_len = recv(sock, info_buf, BUFSIZ, 0);
// 	printf("recv_len is: %d\nrecv: %s\n", recv_len, info_buf);
	if (recv_len < 0) {
// 		perror("get_music_info_from_server recv");
		return 0;
	}
	info_buf[recv_len] = '\0';
	if (!strcmp (info_buf, "")) {
// 		printf("recv nothing from music server\nIt may be closed\n%s\n", info_buf);
		return -1;
	}
// 	sock = tmp_sock;
// 	recv_timeout.tv_usec  = 5000;
// 	send(sock, "get -m", 7, 0);
// 	ret = select (sock + 1, &recv_readfd, NULL, NULL, &recv_timeout);
// 		switch (ret) {
// 		case -1 :
// 			perror ("get_music_info");
// 			return -1;
// 			break;
// 		case  0 :
// 			break;
// 		default :
// 			//printf("in switch of ret default\n");
// 			if (FD_ISSET(sock, &recv_readfd)) {
// // 				printf ("recving ....\n");
// // 				check_connection();
// 				recv_len = recv(sock, info_buf, BUFSIZ, 0);
// 			} else {
// 				//printf("can't read anything from music server....\n");
// 				return -1;
// 			}
// 	}
// 	client_music_info.play_mode = atoi(info_buf);
// 	printf("client_music_info.play_mode: %d\n", client_music_info.play_mode);
}

//将字符串形式的播放状态格式化并存储到播放状态信息的全局结构体中
int format_music_info(char *info_buf, struct music_info *info) {
	int i;
// 	int len;
	int splited_words_num;
	static char *splited_music_info_words[100];
// 	printf("buf befor format: %s\n", info_buf);
	if ((splited_words_num = split_words(info_buf, splited_music_info_words, 100)) <= 0) {
// 		printf("error: split_words failed\nnum : %d\n", splited_words_num);
		return -1;
	}
// 	for(i = 0; i < splited_words_num; i++) {
// 	  printf("%d: %s\n", i, splited_music_info_words[i]);
// 	}
// 	printf("words  num: %d\n", splited_words_num);
// 	printf("splited_music_info_words[2] is: %s\n", splited_music_info_words[2]);
// 	GET_ARRAY_LEN(splited_music_info_words, len);
// 	printf("length of words is: %d\n", len);
// 	memset(format_music_info_unsave_str, 0, sizeof(format_music_info_unsave_str));
	if (!strcmp(splited_music_info_words[0], "State:")) { 
// 		printf("splited_music_info_words[1] is: %s\n", splited_music_info_words[1]);
	// 	printf("len is: %d\n", len);
		for (i = 0; i < splited_words_num; i++) {
// 		   printf("i: %d\n", i);
// 	      	  printf("%s\n", splited_music_info_words[i]);
			      if (!strcmp(splited_music_info_words[i], "State:") || 
				  !strcmp(splited_music_info_words[i], "File:") || 
				  !strcmp(splited_music_info_words[i], "Title:") || 
				  !strcmp(splited_music_info_words[i], "Artist:") || 
				  !strcmp(splited_music_info_words[i], "SongTitle:") || 
				  !strcmp(splited_music_info_words[i], "Album:") || 
				  !strcmp(splited_music_info_words[i], "TotalTime:") || 
				  !strcmp(splited_music_info_words[i], "TimeLeft:") || 
				  !strcmp(splited_music_info_words[i], "TotalSec:") || 
				  !strcmp(splited_music_info_words[i], "CurrentTime:") || 
				  !strcmp(splited_music_info_words[i], "CurrentSec:") || 
				  !strcmp(splited_music_info_words[i], "Bitrate:") || 
				  !strcmp(splited_music_info_words[i], "AvgBitrate:") || 
				  !strcmp(splited_music_info_words[i], "Rate:") || 
				  !strcmp(splited_music_info_words[i], "Mode:") ||
				  !strcmp(splited_music_info_words[i], "PlayPath:") ||
				  !strcmp(splited_music_info_words[i], "PlayIter:")){		     
					if (!strcmp(splited_music_info_words[i], "State:")) {
						memset(info->state, 0, sizeof(info->state));
						if (!strcmp(splited_music_info_words[i+1], "STOP")) {
							strcpy(info->state, splited_music_info_words[++i]);
							break;
						}
						strcpy(info->state, splited_music_info_words[++i]);
						continue;
					} else if (!strcmp(splited_music_info_words[i], "File:")) {
						memset(info->file, 0, sizeof(info->file));
						while ( 1 ) {
							i++;
							if (!strcmp(splited_music_info_words[i], "Title:")) {
								i--;
								break;
							}
							strcat(info->file, " ");
							strcat(info->file, splited_music_info_words[i]);
						}
						continue;
					} else if(!strcmp(splited_music_info_words[i], "Title:")) {
						memset(info->title, 0, sizeof(info->title));
						while ( 1 ) {
							i++;
							if (!strcmp(splited_music_info_words[i], "Artist:")) {
								i--;
								break;
							}
							strcat(info->title, " ");
							strcat(info->title, splited_music_info_words[i]);
						}
						continue;
					} else if(!strcmp(splited_music_info_words[i], "Artist:")) {
						memset(info->artist, 0, sizeof(info->artist));
						while ( 1 ) {
							i++;
							if (!strcmp(splited_music_info_words[i], "SongTitle:")) {
								i--;
								break;
							}
							strcat(info->artist, " ");
							strcat(info->artist, splited_music_info_words[i]);
						}
						continue;
					} else if(!strcmp(splited_music_info_words[i], "SongTitle:")) {
						memset(info->song_title, 0, sizeof(info->song_title));
						while ( 1 ) {
							i++;
							if(!strcmp(splited_music_info_words[i], "Album:")) {
								i--;
								break;
							}
							strcat(info->song_title, " ");
							strcat(info->song_title, splited_music_info_words[i]);
						}
						continue;
					} else if(!strcmp(splited_music_info_words[i], "Album:")) {
						memset(info->album, 0, sizeof(info->album));
						while ( 1 ) {
							i++;
							if(!strcmp(splited_music_info_words[i], "TotalTime:")) {
								i--;
								break;
							}
							strcat(info->album, " ");
							strcat(info->album, splited_music_info_words[i]);
						}
						continue;
					} else if(!strcmp(splited_music_info_words[i], "TotalTime:")) {
						memset(info->total_time, 0, sizeof(info->total_time));
						while ( 1 ) {
							i++;
							if (!strcmp(splited_music_info_words[i], "TimeLeft:")) {
								i--;
								break;
							}
							strcat(info->total_time, " ");
							strcat(info->total_time, splited_music_info_words[i]);
						}
						continue;
					} else if(!strcmp(splited_music_info_words[i], "TimeLeft:")) {
						memset(info->time_left, 0, sizeof(info->time_left));
						while ( 1 ) {
							i++;
							if (!strcmp(splited_music_info_words[i], "TotalSec:")) {
								i--;
								break;
							}
							strcat(info->time_left, " ");
							strcat(info->time_left, splited_music_info_words[i]);
						}
						continue;
					} else if(!strcmp(splited_music_info_words[i], "TotalSec:")) {
						info->total_sec = atoi(splited_music_info_words[++i]);
						continue;
					} else if(!strcmp(splited_music_info_words[i], "CurrentTime:")) {
						strcpy(info->cur_time, splited_music_info_words[++i]);
						continue;
					} else if(!strcmp(splited_music_info_words[i], "CurrentSec:")) {
	      // 				  }
						info->cur_sec = atoi(splited_music_info_words[++i]);
						continue;
					} else if(!strcmp(splited_music_info_words[i], "Bitrate:")) {
						strcpy(info->bitrate, splited_music_info_words[++i]);
						continue;
					} else if(!strcmp(splited_music_info_words[i], "AvgBitrate:")) {
						strcpy(info->avg_bitrate, splited_music_info_words[++i]);
						continue;
					} else if(!strcmp(splited_music_info_words[i], "Rate:")) {
						strcpy(info->rate, splited_music_info_words[++i]);
// 						printf("i is: %d\n next word: %s",i, splited_music_info_words[i + 1]);
						continue;
					} else if (!strcmp(splited_music_info_words[i], "Mode:")) {
						info->play_mode = atoi(splited_music_info_words[++i]);
						continue;
					} else if (!strcmp(splited_music_info_words[i], "PlayPath:")) {
						info->play_path = atoi(splited_music_info_words[++i]);
// 						printf("PlayPath: %d\n", info->play_path);
						continue;
					} else if (!strcmp(splited_music_info_words[i], "PlayIter:")) {
						info->play_iter = atoi(splited_music_info_words[++i]);
// 						printf("PlayIter: %d\n", info->play_iter);
						continue;
					}

			      }
		      }
	} else {
		    printf("it is stop or server is shutdown\n");
		    
	}
	  
	  for (i = 0; i < splited_words_num; i++) {
// 		  printf("splited_music_info_words[%d]: %s\n", i, splited_music_info_words[i]);
		  free(splited_music_info_words[i]);
// 		  printf("splited_music_info_words[%d]: %s\n", i, splited_music_info_words[i]);
	  }
	  splited_words_num = -1;
	  return 0;
}

//获取
int get_music_dirs_from_server(int force_update) {
  static int updated;
  //不要求强制 刷新 文件夹列表时，若列表已更新则不更新
  if (force_update == 0) {
    if (updated != 0) {
      printf("Ignore dir_list data update\n");
      return 0;
    }
  }
  int dir_sock;
  if ((dir_sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
		return -1;
  }
  char *buf;
  int dir_num;
  if ((buf = malloc(BUFSIZ*10)) == NULL) {
    perror("ERROR: get_music_dirs_from_server: ");
    return -1;
  }
  send(dir_sock, "get -d", 6, 0);
  recv(dir_sock, buf, BUFSIZ*10, 0);
//   printf("get: %s\n", buf);
  dir_num = split_array_by_pattern(buf, dir_list, split_pattern);

  music_dir_list_num = dir_num;
  free(buf);
  close(dir_sock);
  return dir_num;
}

//新建一个连接到服务器的端口获取播放列表
int get_music_list_from_server() {
  while (music_list_num) {
    free(music_list[--music_list_num]);
  }
  int sock;
  if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
		return -1;
  }
//   char buf[BUFSIZ];
  char *buf;
  if ((buf = malloc(BUFSIZ*10)) == NULL) {
    perror("ERROR: get_music_list_from_server: ");
    return -1;
  }
  memset(buf, '\0', BUFSIZ*10);
  int list_num;
  
  sprintf(buf, "get -l %d", client_music_info.play_path);
  send(sock, buf, 10, 0);
  memset(buf, '\0', BUFSIZ*10);
  recv(sock, buf, BUFSIZ*10, 0);
//   list_num = atoi(buf);
//   printf("get: %s\n", buf);
  list_num = split_array_by_pattern(buf, music_list, split_pattern);

  free(buf);
  music_list_num = list_num;
  close(sock);
  return music_list_num;
}

gpointer get_music_list_from_server_in_thread(gpointer data) {
  get_music_list_from_server();
}
