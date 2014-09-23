#include "control_music_func.h"

char volume_adjust_str[13] = {'m', 'o', 'c', 'p', ' ', '-', 'v', ' ', ' ', };
// char process_adjust_str[15] = {'m', 'o', 'c', 'p', ' ', '-', 'k', ' ', ' ', };

int func_label_music_info_state () {
	
}

int func_label_music_info_file () {
	
}

int func_label_music_info_title () {
	
}

int func_label_music_info_artist () {
	
}

int func_label_music_info_song_title () {
	
}

int func_label_music_info_total_time () {
	
}

int func_label_music_info_bitrate () {
	
}

int func_label_music_info_avg_bitrate () {
	
}

int func_label_music_info_rate () {
	
}

// void func_button_music_start_server(GtkWidget *button) {
// 	
// 	printf("control_music sock is: %d\n", sock);
// 	//printf("sending control message....\n");
// 	send(sock, "mocp -S", 7, 0);
// 	printf("finish.\n");
// 	/*
// 	recv_len = recv(sock, recv_buf, BUFSIZ, 0);
// 	recv_buf[recv_len] = '\0';
// 	printf("%s\n", recv_buf);
// 	*/
// 	music_state_change(state_server_start);
// }

// void func_button_music_exit_server(GtkWidget *button) {
// 	
// 	//printf("sending control message....\n");
// 	
// 	send(sock, "mocp -x", 7, 0);
// // 	data_update_music_state_change(state_server_stop);
// 	switch (get_music_state(client_music_info.state)) {
// 	  case state_stop:
// 		  break;
// 	  case state_pause:
// 		  break;
// 	  case state_play:
// // 		  g_object_ref(box_music_pause);
// // 		  gtk_container_remove(GTK_CONTAINER(button_music_play), box_music_pause);
// // 		  gtk_container_add(GTK_CONTAINER(button_music_play), box_music_play);
// // 		  gtk_widget_show(box_music_play);
// 		  break;
// 	  default:
// 		  break;
// 	}
// 	gui_update_music_info(state_server_stop);
// // 	printf("finish.\n");
// 	/*
// 	recv_len = recv(sock, recv_buf, BUFSIZ, 0);
// 	recv_buf[recv_len] = '\0';
// 	printf("%s\n", recv_buf);
// 	*/
// 	music_state_change(state_server_stop);
// }

// gpointer func_button_music_play_start_play (gpointer data) {
// 		  send(sock, "mocp -S", 7, 0);
// 		  sleep (1);
// 		  send(sock, "mocp -p", 7, 0);
// // 		  data_update_music_state_change(state_play);
// 		  printf("updated the data state to %s\n", client_music_info.state);
// // 		  g_object_ref(box_music_play);
// // 		  gtk_container_remove(GTK_CONTAINER(button_music_play), box_music_play);
// // 		  gtk_container_add(GTK_CONTAINER(button_music_play), box_music_pause);
// // 		  gtk_widget_show(box_music_pause);
// 		  return NULL;
// }

void func_button_music_play(GtkWidget *button) {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	switch(get_music_state(client_music_info.state)) {
	  case state_stop:
	     send(sock, "mocp -p", 7, 0);
	     break;
	  case state_pause:
	    send(sock, "mocp -G", 7, 0);
	    break;
	  case state_play:
	    send(sock, "mocp -G", 7, 0);
	    break;
	  default:
	    send(sock, "mocp -S", 7, 0);
	    send(sock, "mocp -p", 7, 0);
	}
	send(sock, "quit", 5, 0);
	
	close(sock);

}

void func_button_music_play_focus(GtkWidget *button) {
	gtk_button_set_relief(GTK_BUTTON(button_music_play), GTK_RELIEF_NONE);
}

// void func_button_music_pause(GtkWidget *button) {
// 	
// 	//printf("sending control message....\n");
// 	send(sock, "mocp -P", 7, 0);
// 	data_update_music_state_change(state_pause);
// // 	tmp_music_gui_update_all ();
// 	 printf("update the data state to %s\n", client_music_info.state);
// 	printf("finish.\n");
// 
// 	music_state_change(state_pause);
// }

// void func_button_music_unpause(GtkWidget *button) {
// 	
// 	send(sock, "mocp -U", 7, 0);
// 	printf("finish.\n");
// 	music_state_change(state_play);
// }

void func_button_music_stop(GtkWidget *button) {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	//printf("sending control message....\n");
	send(sock, "mocp -s", 7, 0);
	close(sock);

}

void func_button_music_next(GtkWidget *button) {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	//printf("sending control message....\n");
	send(sock, "mocp -f", 7, 0);
	printf("finish.\n");
	close(sock);
	/*
	recv_len = recv(sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
	*/
}

void func_button_music_pre(GtkWidget *button) {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	//printf("sending control message....\n");
	send(sock, "mocp -r", 7, 0);
	printf("finish.\n");
	close(sock);
	/*
	recv_len = recv(sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
	*/
}

void func_button_music_pre_focus(GtkWidget *button) {
// 	g_object_ref(box_music_pre);
// 	gtk_container_remove(GTK_CONTAINER(button_music_pre), box_music_pre);
// 	gtk_container_add(GTK_CONTAINER(button_music_pre), box_music_pre_focus);
// 	gtk_widget_show(box_music_pre_focus);
	printf("pre_button get focus\n");
}

void func_button_music_pre_leave(GtkWidget *button) {
// 	g_object_ref(box_music_pre_focus);
// 	gtk_container_remove(GTK_CONTAINER(button_music_pre), box_music_pre_focus);
// 	gtk_container_add(GTK_CONTAINER(button_music_pre), box_music_pre);
// 	gtk_widget_show(box_music_pre);
	printf("pre_button lose focus\n");
}

// void func_button_music_volume_up(GtkWidget *button) {
// 	
// 	//printf("sending control message....\n");
// 	send(sock, "mocp -v +5", 10, 0);
// 	printf("finish.\n");
// 	/*
// 	recv_len = recv(sock, recv_buf, BUFSIZ, 0);
// 	recv_buf[recv_len] = '\0';
// 	printf("%s\n", recv_buf);
// 	*/
// 	//struct music_info client_music_info[3];
// 	data_update_client_music_info(&client_music_info);
// // 	printf("-------------------------\ninfo->cur_sec in button: %d\n--------------------------\n", client_music_info.cur_sec);
// 	
// }

void func_button_music_silence(GtkWidget *button) {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	volume_last_value = 0;
	gtk_scale_button_set_value (GTK_SCALE_BUTTON(button_music_volume), 0.00);
	//gtk_scale_button_set_value(GTK_SCALE_BUTTON(data), 0.000);
	//printf("%lf\n", gtk_scale_button_get_value(GTK_SCALE_BUTTON(data)));
	//gtk_widget_show_now(GTK_WIDGET(data));
	//printf("sending control message....\n");
	send(sock, "mocp -v -100", 15, 0);
	printf("set silence finish.\n");
	close(sock);
	/*
	recv_len = recv(sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
	*/
}

void func_button_music_volume(GtkWidget *button) {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	volume_get_value = gtk_scale_button_get_value(GTK_SCALE_BUTTON(button));
	//printf("volume_get_value: %lf\n", volume_get_value);
	volume_cur_value = volume_get_value * 100;
	//printf("volume_cur_value is: %d\n", volume_cur_value);
// 	//printf("volume_last_value is: %d\n", volume_last_value);
	if (volume_cur_value > volume_last_value) {
		volume_adjust_str[8] = '+';
		tmpvalue = volume_cur_value - volume_last_value;
	} else {
		volume_adjust_str[8] = '-';
		tmpvalue = volume_last_value - volume_cur_value;
	}
	
	//printf("tmpvalue: %d\n", tmpvalue);
	sprintf(tmpstr, "%d", tmpvalue);
	
	volume_adjust_str[9] = tmpstr[0];
	//printf("volume_adjust_str[9] is: %c\ntmpstr[0] is: %c\n", volume_adjust_str[9], tmpstr[0]);
	volume_adjust_str[10] = tmpstr[1];
	//printf("volume_adjust_str[10] is: %c\ntmpstr[1] is: %c\n", volume_adjust_str[10], tmpstr[1]);
	volume_adjust_str[11] = tmpstr[2];
	//printf("volume_adjust_str[11] is: %c\ntmpstr[2] is: %c\n", volume_adjust_str[11], tmpstr[2]);
	//printf("tmpstr is: %s\n", tmpstr);
	
	printf("volume_adjust_str is: %s\n", volume_adjust_str);
	
	send(sock, volume_adjust_str, 12, 0);
	volume_last_value = volume_cur_value;
	close(sock);
	//printf("seeded\n");
	/*
	recv_len = recv(sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
	*/
}

int func_scale_music_process (GtkWidget *scale) {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	double process_get_value;
	int process_cur_value;
	process_get_value = gtk_range_get_value(GTK_RANGE(scale));
	process_cur_value = (int)process_get_value * (((float)client_music_info.total_sec) / 100) ;
	char *p_command;
	p_command = malloc (20);
	memset(p_command, '\0', sizeof(p_command));
	sprintf(p_command, "mocp -j %ds", process_cur_value);
	printf("p_command: %s\n", p_command);
	send_len = send(sock, p_command, 20, 0);
	free(p_command);
	process_gui_update = TRUE;
	close(sock);
	return 1;
}

int func_scale_music_process_press (GtkWidget *scale) {
	process_gui_update = FALSE;
	printf("press process scale");
}
// int func_scale_music_process_press (GtkWidget *scale) {
// 	process_gui_update = FALSE;
// 	printf("press process scale");
// }

int test_funck(GtkWidget *widget) {
	printf("_____________________");
}

// void func_button_music_get_list(GtkWidget *button, gpointer data) {
// 	
// // 	char tmp_name[BUFSIZ];
// // 	get_file_name(tmp_name, client_music_info.file);
// // 	get_lyric_from_file(tmp_name);
// // // 	lyric_get_tags (lyric_tags, lyric_buf);
// // 	float tmp_sec;
// // 	convert_str_min_to_sec("02:18.01", &tmp_sec);
// // 	printf("tmp_sec: %f\n", tmp_sec);
// // 	format_lyric(cur_lyric, lyric_buf);
// // 	printf("cur_lyric[11].sentence: %s\n", cur_lyric[11].sentence);
// // 	printf("read lyric finished\n");
// // 	load_cur_lyric();
// // 	gui_update_music_lyric();
// 	send(sock, "test -v -100", 15, 0);
// // 	printf("lyric gui update finished\n");
// 
// }

void func_button_music_reset_list(GtkWidget *button, gpointer data) {
  int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
  send(sock, "set -l", 6, 0);
  close(sock);
}

int func_scale_music_process_focus (GtkWidget *button) {
	
}

int func_switch_music_autonext () {
	
}

int func_switch_music_repeat () {
	
}

int func_switch_music_shuffle () {
	
}


gpointer func_radio_button_music_mode_for_thread (gpointer data) {
	func_radio_button_music_mode ();
	return NULL;
}

int func_radio_button_music_mode_in_thread () {
	g_thread_new (NULL, func_radio_button_music_mode_for_thread, NULL);
	return 0;
}

int get_selected_mode () {
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio_button_music_mode_shuffle))) {
		return shuffle;
	}
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio_button_music_mode_loop_list))) {
		return loop_list;
	}
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio_button_music_mode_play_list))) {
		return play_list;
	}
	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio_button_music_mode_loop_one))) {
		return loop_one;
	}
// 	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(radio_button_music_mode_play_one))) {
// 		return play_one;
// 	}
	return -1;
}

int func_radio_button_music_mode () {
	
	static gint run_time = 0;
	if (run_time > 1) {
	      run_time = run_time - 2;
	      return 2;
	}
	gint mode = get_selected_mode ();
	if (mode < 0) {
		return -1;
	}
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	switch (mode) {
		case shuffle :
			printf("change to shuffle\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_shuffle), TRUE);
			send_len = send(sock, "mocp -L 0", 10, 0);
			client_music_info.play_mode = shuffle;
			break;
		case loop_list :
			printf("change to loop_list\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_loop_list), TRUE);
			send_len = send(sock, "mocp -L 1", 10, 0);
			client_music_info.play_mode = loop_list;
			break;
		case play_list :
			printf("change to play_list\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_play_list), TRUE);
			send_len = send(sock, "mocp -L 2", 10, 0);
			client_music_info.play_mode = play_list;
			break;
		case loop_one :
			printf("change to loop_one\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_loop_one), TRUE);
			send_len = send(sock, "mocp -L 3", 10, 0);
			client_music_info.play_mode = loop_one;
			break;
		case play_one :
			printf("change to loop_one\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_loop_one), TRUE);
			send_len = send(sock, "mocp -L 4", 10, 0);
			client_music_info.play_mode = play_one;
			break;
		default :
			printf("unknow mode: %d\n", mode);
			break;
	}
// 	send(sock, "get -m", 6, 0);
// 	recv(sock, recv_buf, 1, 0);
// 	recv_buf[1] = '\0';
// 	client_music_info.play_mode = atoi(recv_buf);
	//gtk_spinner_stop (GTK_SPINNER (spinner_music_mode_changing));
	close(sock);
	return 0;
}

// int func_tree_view_music_list () {
//       printf("single clicked a item\n");
// }

int func_selection_music_dir_list_clicked() {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *name;
	char command_str[BUFSIZ];
	if (gtk_tree_selection_get_selected (selection_music_dir_list, &model, &iter)) {
		//将模型model中的迭代器iter指定的那一行的list_title（枚举值为1）那一列的变量取出放置到music_name中
		gtk_tree_model_get (model, &iter, dir_name, &name, -1);
		g_print ("%s\n",name);
		client_music_info.play_path = get_dir_list_iter_from_str(name, dir_list, music_dir_list_num);
		printf("fun_selection_music_dir_list_clicked: path_iter: %d\n", client_music_info.play_path);
		memset(command_str, '\0', BUFSIZ);
		sprintf(command_str, "set -d %d", client_music_info.play_path);
		send(sock, command_str, strlen(command_str) + 1, 0);
// 		get_music_list_from_server();
		g_thread_new(NULL, get_music_list_from_server_in_thread, NULL);
// 		gui_update_music_list();
	}
	close(sock);
}

int func_selection_music_list_clicked() {
	int sock;
	if ((sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port)) < 0) {
		printf("error: connect_server failed\n");
	} 
	GtkTreeIter iter;
	GtkTreeModel *model;
	char *music_name;
	char command_str[BUFSIZ];
// 	selection_music_list通过tree_view_music_list创建，下面将iter迭代器定位到tree_view_music_list中
// 	当前所选的项目， 并且把当前的模型填充到model中
	if (gtk_tree_selection_get_selected (selection_music_list, &model, &iter)) {
		//将模型model中的迭代器iter指定的那一行的list_title（枚举值为1）那一列的变量取出放置到music_name中
		gtk_tree_model_get (model, &iter, list_title, &music_name, -1);
		g_print ("%s\n", music_name);
		char name_iter[BUFSIZ];
		memset(name_iter, 0, BUFSIZ);
// 		sprintf(name_iter, "%d", get_list_iter_from_str(music_name, music_list, music_list_num));
		memset (command_str, 0, sizeof(command_str));
// 		strcat(command_str, "mocp -l ");
// 		strcat(command_str, path_iter);
// 		strcat(command_str, name_iter);
		sprintf(command_str, "mocp -l %d %d", client_music_info.play_path, get_list_iter_from_str(music_name, music_list, music_list_num));
		printf("func_selection_music_list_clicked sending: %s\n", command_str);
		send(sock, command_str, strlen(command_str), 0);
		
	}
	close(sock);
	return 0;
}

int get_list_iter_from_str(char *str, char *music_list[], int music_list_num) {
	int i = 0;
	while (i < music_list_num) {
		printf("get_list_iter_from_str: %d: %s\n", i, music_list[i]);
		if (!strcmp(str, music_list[i])) {
			return i;
		}
		i++;
	}
	return -1;
}

int get_dir_list_iter_from_str(char *str, char *music_list[], int music_list_num) {
	int i = 0;
	char tmp_str[BUFSIZ];
	while (i < music_list_num) {
		get_file_name(tmp_str, music_list[i]);
		printf("get_list_iter_from_str: %d: %s\n", i, tmp_str);
		if (!strcmp(str, tmp_str)) {
			return i;
		}
		i++;
	}
	return -1;
}