#include "control_music_gui.h"

int gui_update_music_state_change (int state) {
	switch (state) {
		case state_play:
		      gui_update_music_info(state_play);
		      gui_update_music_process(state_play);
		      break;
		case state_pause:
		      gui_update_music_info (state_pause);
		      gui_update_music_process(state_pause);
		      break;
		case state_unpause:
		      gui_update_music_info (state_unpause);
		      //gui_update_music_process(state_unpause);
		      break;
		case state_stop:
		      gui_update_music_info (state_stop);
		      gui_update_music_process(state_stop);
		      break;
		case state_server_stop:
		       gui_update_music_info (state_server_stop);
		       gui_update_music_process(state_server_stop);
		      break;
		case state_server_start:
		      gui_update_music_info (state_server_start);
		      break;
		default:
// 		      printf("gui_update_music_state_change: unknow state\n");
		      return -1;
	}
	return 0;
}

int gui_update_play_mode(int mode) {
	switch (mode) {
		case shuffle :
// 			printf("update shuffle\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_shuffle), TRUE);
			break;
		case loop_list :
// 			printf("change to loop_list\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_loop_list), TRUE);
			break;
		case play_list :
// 			printf("change to play_list\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_play_list), TRUE);
			break;
		case loop_one :
// 			printf("change to loop_one\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_loop_one), TRUE);
			break;
		case play_one :
// 			printf("change to loop_one\n");
			gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radio_button_music_mode_loop_one), TRUE);
			break;
		default :
			printf("unknow mode: %d\n", mode);
			return -1;
	}
	return 0;
}

int gui_update_music_control() {
	GtkWidget *tmp_image;
	tmp_image = gtk_button_get_image (GTK_BUTTON(button_music_play));
	if (!strcmp(client_music_info.state, "PLAY")) {
		if (tmp_image != image_music_pause) {
			g_object_ref(image_music_play);
			gtk_button_set_image(GTK_BUTTON(button_music_play), image_music_pause);
		} 
	} else {
		if (tmp_image != image_music_play) {
			g_object_ref(image_music_pause);
			gtk_button_set_image(GTK_BUTTON(button_music_play), image_music_play);
		}
	}
}

int gui_update_music_info() {
	static char last_state[BUFSIZ];
	static char last_file[BUFSIZ];
	if (!strcmp(last_state, client_music_info.state) && !strcmp (last_file, client_music_info.file)) {
// 		printf("ignore info_labels update\n");
		return 0;
	}
	
	char *tmp_info_str;
	tmp_info_str = malloc(BUFSIZ);
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "State: ");
	gtk_label_set_label(GTK_LABEL(label_music_info[0]), strcat(tmp_info_str, client_music_info.state));
	
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "File: ");
	char file_name[BUFSIZ];
	get_file_name (file_name, client_music_info.file);
	strcat(tmp_info_str, file_name);
	gtk_label_set_label(GTK_LABEL(label_music_info[1]), tmp_info_str);
// 	printf("tmp_gui_update_music_info: %s\n", client_music_info.file);
	
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "Title: ");
	gtk_label_set_label(GTK_LABEL(label_music_info[2]), g_locale_to_utf8 (strcat(tmp_info_str, client_music_info.title), -1, NULL, NULL, NULL));
	
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "Artist: ");
	gtk_label_set_label(GTK_LABEL(label_music_info[3]), g_locale_to_utf8 (strcat(tmp_info_str, client_music_info.artist), -1, NULL, NULL, NULL));
	
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "Song title: ");
	gtk_label_set_label(GTK_LABEL(label_music_info[4]), g_locale_to_utf8 (strcat(tmp_info_str, client_music_info.song_title), -1, NULL, NULL, NULL));
	
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "Total time: ");
	gtk_label_set_label(GTK_LABEL(label_music_info[5]), g_locale_to_utf8 (strcat(tmp_info_str, client_music_info.total_time), -1, NULL, NULL, NULL));
	
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "Bitrate: ");
	gtk_label_set_label(GTK_LABEL(label_music_info[6]), g_locale_to_utf8 (strcat(tmp_info_str, client_music_info.bitrate), -1, NULL, NULL, NULL));
	
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "Avg bitrate: ");
	gtk_label_set_label(GTK_LABEL(label_music_info[7]), g_locale_to_utf8 (strcat(tmp_info_str, client_music_info.avg_bitrate), -1, NULL, NULL, NULL));
	
	memset(tmp_info_str, '\0', sizeof(BUFSIZ));
	strcat (tmp_info_str, "Rate: ");
	gtk_label_set_label(GTK_LABEL(label_music_info[8]), g_locale_to_utf8 (strcat(tmp_info_str, client_music_info.rate), -1, NULL, NULL, NULL));
	
	free(tmp_info_str);
	
	strcpy (last_state, client_music_info.state);
	strcpy (last_file, client_music_info.file);
	return 0;
}

int gui_update_music_info_play () {
	char tmp_info_str[BUFSIZ+1];
	
	
	memset(tmp_info_str, 0, sizeof(tmp_info_str));
	strcat(tmp_info_str, "State: ");
	strcat(tmp_info_str, client_music_info.state);
	return 0;
}

int gui_update_music_info_pause () {

}

int gui_update_music_info_unpause () {
}

int gui_update_music_info_stop () {
}

int gui_update_music_info_server_stop () {
}

int gui_update_music_info_server_start () {
// 	gtk_label_set_label(GTK_LABEL(label_music_info_state), "State: Server Start");
}

int gui_update_music_volume () {
	volume_last_value = 100;
	gtk_scale_button_set_value (GTK_SCALE_BUTTON(button_music_volume), 5);
	return 0;
}

int gui_update_music_process() {
	int gui_process;
	int data_process;
	int event;
	double process_set_value;
	gui_process =  gtk_scale_get_digits(GTK_SCALE(scale_music_process));
	event = gtk_widget_get_events (scale_music_process);
// 	printf("cur_process_event: %d\n", event);
// 	printf("cur_gui_process: %d\n", gui_process);
	process_set_value = ((double)client_music_info.cur_sec) / ((double)client_music_info.total_sec) * 100 ;
	// 	printf("process_set_value is: %lf\n", process_set_value);
	gtk_range_set_value(GTK_RANGE(scale_music_process), process_set_value);
	gtk_label_set_label(GTK_LABEL(label_music_cur_time), client_music_info.cur_time);
	//printf("total_time is: %s\n", client_music_info_ptr->total_time);
	gtk_label_set_label(GTK_LABEL(label_music_total_time), client_music_info.total_time);
	return 0;
 }
 
 int gui_update_music_dir_list(int force_update) {
	static int updated_dir_list_gui;
	if (force_update == 0) {
		if (updated_dir_list_gui != 0) {
// 		  printf("Ignore update dir_list gui\n");
		  return 0;
		}
	}
	if (get_music_dirs_from_server(1) < 0) {
		return -1;
	}
	GtkTreeIter list_iter;
// 	printf("gui_update_music_dir_list: music_dir_list_num is: %d\n", music_dir_list_num);
	int i = 0;
// 	char path_name[BUFSIZ];
	char *path_name = malloc(1024);
	while (i < music_dir_list_num) {
// 		      printf("%d: %s\n", i, dir_list[i]);
// 		      sprintf(file_index, "%d", i + 1);
		      gtk_tree_store_append(store_music_dir_list, &list_iter, NULL);
		      memset(path_name, '\0', 1024);
		      get_file_name(path_name, dir_list[i]);
		      printf("%s\n", path_name);
		      gtk_tree_store_set (store_music_dir_list, &list_iter, dir_name, path_name);
// 		      gtk_tree_store_set (store_music_dir_list, &list_iter, dir_name, dir_list[i]);
		      i++;
	}
	free(path_name);
	gtk_tree_view_column_set_title(column_music_dir_list, "文件夹");
	gtk_tree_view_column_set_max_width(column_music_dir_list, 60);
	updated_dir_list_gui = 1;
	return 0;
 }
 
 int gui_update_music_list() {
	static int last_play_path = -1;
	if (last_play_path == client_music_info.play_path) {
// 	  printf("Ignore update music_list\n");
	  return 0;
	}
	get_music_list_from_server();
	gtk_tree_store_clear(store_music_list);
	char file_index[BUFSIZ];
	GtkTreeIter list_iter;
// 	printf("gui_update_music_ligt: music_list_num is: %d\n", music_list_num);
	int i = music_list_num;
// 	printf("");
	if (i < 1) {
	  return 0;
	}
	int j = 1;
   	while (i--) {
// 		printf("%d: %s\n", i, music_list[i]);
		sprintf(file_index, "%d", j);
		gtk_tree_store_append(store_music_list, &list_iter, NULL);
		gtk_tree_store_set (store_music_list, &list_iter, list_index, file_index, list_title, music_list[i], -1);
// 		i++;
		j++;
	}
	gtk_tree_view_column_set_title(column_music_list, dir_list[client_music_info.play_path]);
	last_play_path = client_music_info.play_path;
	return 0;
 }

gpointer gui_update_music_lyric_for_thread(gpointer data) {
	while (1) {
		if (cur_lyric_file_existed == TRUE) {
			gui_update_music_lyric();
		} else  {
			int i = 0;
			for (; i < 9; i++) {
				 gtk_label_set_label(GTK_LABEL(label_music_lyric[i]), "");
			}
			gtk_label_set_label(GTK_LABEL(label_music_lyric[4]), "lyric file is not existed!");
			return NULL;
		}
		g_usleep(20000);
	}
	return NULL;
}

int gui_update_music_lyric_int_thread() {
	g_thread_new (NULL,gui_update_music_lyric_for_thread , NULL);
	return 0;
}

int gui_update_music_lyric() {
	int label_iter;
	if (lyric_check_data() < 0) {
		return -1;
	}
	float cur_sec_float = (float)client_music_info.cur_sec + 1;
	for (lyric_show_iter = 0; lyric_show_iter < lyric_valid_iter && tmp_cur_lyric[lyric_show_iter].time <= cur_sec_float; lyric_show_iter++) {
	}
	if (lyric_show_iter != lyric_show_iter_last) {
		lyric_show_iter_last = lyric_show_iter;
		for (label_iter = -4; label_iter < 5; label_iter++) {
			if (lyric_show_iter - label_iter < 0) {
				continue;
			}
			gtk_label_set_label(GTK_LABEL(label_music_lyric[label_iter + 4]), tmp_cur_lyric[lyric_show_iter + label_iter - 1].sentence);
		}
	} else {
		return -1;
	}
	return 0;
}

int lyric_check_data() {
	char cur_music_name[BUFSIZ];
	char cur_file_name[BUFSIZ];
	char tmp_file_name[BUFSIZ];
	memset(tmp_file_name, 0, BUFSIZ);
	get_file_name (tmp_file_name, client_music_info.file);
// 	char *tmp_file_name;
// 	tmp_file_name = tmp_get_file_name(tmp_file_name, client_music_info.file);
// 	if (tmp_file_name == NULL) {
// 		printf("can not get the tmp_file_name\n");
// 		return -1;
// 	}
// 	printf("client_music_info.file: %s\n", client_music_info.file);
	if (!strcmp(tmp_file_name, "")) {
// 		printf("can not get the tmp_file_name\n");
		return -1;
	}
	get_file_name_without_extension (cur_file_name, tmp_file_name);
// 	printf("cur file name: %s\n", cur_file_name);
	get_file_name_without_extension (cur_music_name, cur_lyric_name);
// 	printf("cur_music_name: %s\n", cur_music_name);
	if (!strcmp (cur_music_name, cur_file_name)) {
// 		printf("lyric_data_checked\n");
		return 0;
	}
// 	printf("reload the lyric\n");
	
	if (load_cur_lyric() < 0) {
		return -1;
	}
	sort_lyric_data();
	return 0;
}


int music_gui_update_all() {
// 	data_update_client_music_info_in_thread (&client_music_info);
	static update_time = 0;
	if (update_time < 3) {
// 		printf("update_time is : %d\n", update_time);
		gui_update_music_volume ();
		update_time ++;
// 		printf("update_time is : %d\n", update_time);
	}
	gui_update_music_control();

	gui_update_music_process();
	
	gui_update_play_mode(client_music_info.play_mode);
	
	gui_update_music_info();
	
// 	g_thread_new (NULL, gui_update_music_lyric_for_thread, NULL);
	if (cur_lyric_file_existed == FALSE) {
		lyric_check_data();
		if (cur_lyric_file_existed == TRUE) {
			gui_update_music_lyric_int_thread();
		}
	}
	gui_update_music_dir_list(0);
	gui_update_music_list();
// 	printf("gui_updated\n");
	return 1;
}

gpointer music_gui_update_all_for_thread() {
	while (1) {
		music_gui_update_all();
		g_usleep(100000);
	}
	return NULL;
}

int music_gui_update_all_in_thread() {
	g_thread_new(NULL, music_gui_update_all_for_thread, NULL);
}

