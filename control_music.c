#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include "control_music.h"
#include "control_music_gui.h"
#include "control_music_common.h"
#include "control_music_func.h"
#include "control_music_set.h"
#include "common.h"


int music_build_element_widgets () {
	int i = 0;
	for (i = 0; i < 9; i++) {
		label_music_info[i] = gtk_label_new(NULL);
		gtk_label_set_width_chars(GTK_LABEL(label_music_info[i]), 15);
		gtk_label_set_max_width_chars(GTK_LABEL(label_music_info[i]), 150);
		gtk_label_set_line_wrap(GTK_LABEL(label_music_info[i]), TRUE);
	}
	separator_music_info = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	
	for (i = 0; i < 9; i++) {
		label_music_lyric[i] = gtk_label_new(NULL);
		gtk_label_set_max_width_chars(GTK_LABEL(label_music_lyric[i]), 305);
// 		gtk_label_set_line_wrap(GTK_LABEL(label_music_lyric[i]), TRUE);
	}
	gtk_label_set_selectable(GTK_LABEL(label_music_lyric[4]), TRUE);
	gtk_label_set_use_underline (GTK_LABEL(label_music_lyric[4]), TRUE);
	gtk_label_set_use_markup (GTK_LABEL(label_music_lyric[4]), TRUE);
	gtk_label_set_pattern (GTK_LABEL(label_music_lyric[4]), "________");
	separator_music_lyric1 =  gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	separator_music_lyric2 =  gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);

	button_music_start_server = gtk_button_new_with_label("启动服务器");
// 	set_button_music_start_server(button_music_start_server);
	
	button_music_exit_server = gtk_button_new_with_label("关闭服务器");
// 	set_button_music_exit_server(button_music_exit_server);
	
	
	button_music_play = gtk_button_new();
// 	box_music_play = button_with_image("/usr/share/raspi_remote_control/ui_images/ui_images_music/play.png");
// 	box_music_pause = button_with_image("/usr/share/raspi_remote_control/ui_images/ui_images_music/pause.png");
	image_music_play = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/play.png");
	image_music_play_light = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/play_light.png");
	image_music_pause = gtk_image_new_from_file ("/usr/share/raspi_remote_control/ui_images/ui_images_music/pause.png");
	image_music_pause_light = gtk_image_new_from_file ("/usr/share/raspi_remote_control/ui_images/ui_images_music/pause_light.png");
	gtk_button_set_relief(GTK_BUTTON(button_music_play), GTK_RELIEF_NONE);
	set_button_music_play(button_music_play);
	
	button_music_pause = gtk_button_new_with_label("暂停");
// 	set_button_music_pause(button_music_pause);
	
	button_music_unpause = gtk_button_new_with_label("取消暂停");
// 	set_button_music_unpause(button_music_unpause);
	
// 	button_music_stop = gtk_button_new_with_label("停止");
	button_music_stop = gtk_button_new();
	image_music_stop = gtk_image_new_from_file ("/usr/share/raspi_remote_control/ui_images/ui_images_music/stop.png");
	image_music_stop_light = gtk_image_new_from_file ("/usr/share/raspi_remote_control/ui_images/ui_images_music/stop_light.png");
	gtk_button_set_image(GTK_BUTTON(button_music_stop), image_music_stop);
	gtk_button_set_relief(GTK_BUTTON(button_music_stop), GTK_RELIEF_NONE);
	set_button_music_stop(button_music_stop);
	
// 	button_music_next = gtk_button_new_with_label("下一首");
	button_music_next = gtk_button_new();
	image_music_next = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/next.png");
	image_music_next_light = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/next_light.png");
	gtk_button_set_image(GTK_BUTTON(button_music_next), image_music_next);
	gtk_button_set_relief(GTK_BUTTON(button_music_next), GTK_RELIEF_NONE);
	set_button_music_next(button_music_next);
	
// 	button_music_pre = gtk_button_new_with_label("上一首");
	button_music_pre = gtk_button_new();
	image_music_pre = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/pre.png");
	image_music_pre_light = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/pre_light.png");
	gtk_button_set_image (GTK_BUTTON(button_music_pre), image_music_pre);
	gtk_button_set_relief(GTK_BUTTON(button_music_pre), GTK_RELIEF_NONE);
	set_button_music_pre(button_music_pre);
	

	
	
// 	button_music_volume_up = gtk_button_new_with_label("音量+");
// 	set_button_music_volume_up(button_music_volume_up);
	
// 	button_music_volume_silence = gtk_button_new_with_label("静音");
	button_music_silence = gtk_button_new();
	image_music_silence = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/silence.png");
	image_music_silence_light = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/silence_light.png");
	image_music_unsilence = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/unsilence.png");
	image_music_unsilence_light = gtk_image_new_from_file("/usr/share/raspi_remote_control/ui_images/ui_images_music/unsilence_light.png");
	gtk_button_set_image (GTK_BUTTON(button_music_silence), image_music_silence);
	gtk_button_set_relief(GTK_BUTTON(button_music_silence), GTK_RELIEF_NONE);
	set_button_music_silence(button_music_silence);
	
	button_music_volume = gtk_volume_button_new();
	set_button_music_volume( button_music_volume);
	
	button_music_reset_list = gtk_button_new_with_label("重设列表");
	set_button_music_reset_list(button_music_reset_list);
	
// 	button_music_choose_path = gtk_button_new_with_label("添加路径");
// 	set_button_music_choose_path(button_music_choose_path);
// 	music_path_dialog = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	music_path_dialog = gtk_file_chooser_dialog_new ("test_title", NULL, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, "test_button_text", NULL);
	button_music_choose_path = gtk_file_chooser_button_new_with_dialog (music_path_dialog);
	gtk_file_chooser_button_set_title (GTK_FILE_CHOOSER_BUTTON(button_music_choose_path), "添加路径");
// 	gtk_file_chooser_set_select_multiple (music_path_dialog, TRUE);
	
	
	button_music_delete_path = gtk_button_new_with_label("删除当前路径");
	set_button_music_delete_path(button_music_delete_path);
	
	scale_music_process = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
	set_scale_music_process(scale_music_process);
	
	label_music_cur_time = gtk_label_new ("--:--:--");
	label_music_total_time = gtk_label_new ("--:--:--");
	
	switch_music_autonext = gtk_switch_new ();
	set_switch_music_autonext ();
	label_music_autonext = gtk_label_new ("AutoNext: ");
	
	switch_music_repeat = gtk_switch_new ();
	set_switch_music_repeat ();
	label_music_repeat = gtk_label_new ("Repeat: ");
	
	switch_music_shuffle = gtk_switch_new ();
	set_switch_music_shuffle ();
	label_music_shuffle = gtk_label_new ("Shuffle: ");
	
	radio_button_music_mode_shuffle = gtk_radio_button_new (NULL);
	label_music_mode_shuffle = gtk_label_new ("随机:");
	radio_button_music_mode_loop_list = gtk_radio_button_new_from_widget (GTK_RADIO_BUTTON (radio_button_music_mode_shuffle));
	label_music_mode_loop_list = gtk_label_new ("列表循环:");
	radio_button_music_mode_play_list = gtk_radio_button_new_from_widget (GTK_RADIO_BUTTON (radio_button_music_mode_shuffle));
	label_music_mode_play_list = gtk_label_new ("播放列表:");
	radio_button_music_mode_loop_one = gtk_radio_button_new_from_widget (GTK_RADIO_BUTTON (radio_button_music_mode_shuffle));
	label_music_mode_loop_one = gtk_label_new ("单曲:");
	spinner_music_mode_changing = gtk_spinner_new ();
	
	set_radio_button_music_mode ();
	
	
	store_music_dir_list = gtk_tree_store_new(dir_n_columns, G_TYPE_STRING);
	tree_view_music_dir_list = gtk_tree_view_new_with_model (GTK_TREE_MODEL(store_music_dir_list));
	text_renderer_music_dir_list = gtk_cell_renderer_text_new ();
	column_music_dir_list = gtk_tree_view_column_new_with_attributes (NULL, text_renderer_music_dir_list, "text", dir_name, NULL);
	gtk_tree_view_column_set_fixed_width(column_music_dir_list, 100);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view_music_dir_list), column_music_dir_list);
	music_dir_list_sw_adj_h = gtk_adjustment_new(100, 0, 100, 1, 1, 50);
	music_dir_list_sw = gtk_scrolled_window_new(NULL, music_dir_list_sw_adj_h);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(music_dir_list_sw), 330);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(music_dir_list_sw), 100);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(music_dir_list_sw), GTK_SHADOW_NONE);
// 	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(music_dir_list_sw), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(music_dir_list_sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(music_dir_list_sw), tree_view_music_dir_list);
	
	selection_music_dir_list = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view_music_dir_list));
	set_tree_view_music_dir_list ();
	

	store_music_list = gtk_tree_store_new(list_n_columns, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
// 	char file_index[BUFSIZ];
// 	printf("music_list_num is: %s\n", music_list_num);
// 	while (i < music_list_num) {
// // 		printf("%d: %s\n", i, music_list[i]);
// 		sprintf(file_index, "%d", i + 1);
// 		gtk_tree_store_append(store_music_list, &iter_music_list, NULL);
// 		gtk_tree_store_set (store_music_list, &iter_music_list, list_index, file_index, list_title, music_list[i], list_total_sec, "03:00", -1);
// 		i++;
// 	}
// 	
	tree_view_music_list = gtk_tree_view_new_with_model (GTK_TREE_MODEL(store_music_list));
	
	text_renderer_music_list = gtk_cell_renderer_text_new ();
	column_music_list = gtk_tree_view_column_new_with_attributes (NULL, text_renderer_music_list, "text", list_index, NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view_music_list), column_music_list);
	
	gtk_tree_view_column_set_title(column_music_list, "序号");
	
	text_renderer_music_list = gtk_cell_renderer_text_new ();
	column_music_list = gtk_tree_view_column_new_with_attributes (NULL, text_renderer_music_list, "text", list_title, NULL);
	gtk_tree_view_column_set_fixed_width(column_music_list, 100);
	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view_music_list), column_music_list);
	
// 	text_renderer_music_list = gtk_cell_renderer_text_new ();
// 	column_music_list = gtk_tree_view_column_new_with_attributes (NULL, text_renderer_music_list, "text", list_total_sec, NULL);
// 	gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view_music_list), column_music_list);
	
	
	
	music_list_sw_adj_h = gtk_adjustment_new(100, 0, 100, 1, 1, 50);
	music_list_sw = gtk_scrolled_window_new(NULL, music_list_sw_adj_h);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(music_list_sw), 370);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(music_list_sw), 200);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(music_list_sw), GTK_SHADOW_NONE);
// 	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(music_list_sw), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(music_list_sw), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(music_list_sw), tree_view_music_list);
	
	selection_music_list = gtk_tree_view_get_selection (GTK_TREE_VIEW (tree_view_music_list));
	set_tree_view_music_list ();
	return 1;
}

int music_build_container_widgets () {
	
	hbox_bg = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
// 	gtk_container_set_resize_mode (GTK_CONTAINER(hbox_bg), GTK_RESIZE_IMMEDIATE);
	frame_music = gtk_frame_new("Music Remote Control");
	vbox_music_contain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	box_music_bg = button_with_image("/usr/share/raspi_remote_control/ui_images/ui_images_music/bg2.jpg");
	gtk_container_set_border_width (GTK_CONTAINER (vbox_music_contain), 0);
	vbox_music_process = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	
	vbox_info_lyric_contain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	vbox_lyric_contain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_set_homogeneous (GTK_BOX(vbox_info_lyric_contain), TRUE);
	gtk_container_set_resize_mode (GTK_CONTAINER(vbox_info_lyric_contain), GTK_RESIZE_PARENT);

	hbox_music2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	hbox_music3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	hbox_music4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	hbox_music5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	hbox_music6 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	hbox_music_list = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	vbox_info_lyric_contain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
// 	gtk_container_set_resize_mode (GTK_CONTAINER(vbox_info_lyric_contain), GTK_RESIZE_IMMEDIATE);
	hbox_info_contain = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_set_homogeneous (GTK_BOX(hbox_info_contain), FALSE);
	vbox_music_info_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	vbox_music_info_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	return 1;
}

int music_arrange_widgets () {
	int i = 0;
	for (i = 0;i < 5; i++) {
		gtk_box_pack_start(GTK_BOX(vbox_music_info_left), label_music_info[i], FALSE, FALSE, 0);
	}
	for (i = 5;i < 9; i++) {
		gtk_box_pack_start(GTK_BOX(vbox_music_info_right), label_music_info[i], FALSE, FALSE, 0);
	}
	gtk_box_pack_start(GTK_BOX(hbox_info_contain), vbox_music_info_left, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_info_contain), separator_music_info, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_info_contain), vbox_music_info_right, FALSE, FALSE, 0);
// 	gtk_box_pack_start(GTK_BOX(hbox_music2), button_music_start_server, FALSE, FALSE, 0);
// 	gtk_box_pack_start(GTK_BOX(hbox_music2), button_music_exit_server, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music3), button_music_pre, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music3), button_music_play, FALSE, FALSE, 0);
// 	gtk_box_pack_start(GTK_BOX(hbox_music3), button_music_pause, FALSE, FALSE, 0);
// 	gtk_box_pack_start(GTK_BOX(hbox_music3), button_music_unpause, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music3), button_music_stop, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music3), button_music_next, FALSE, FALSE, 0);
// 	gtk_box_pack_start(GTK_BOX(hbox_music4), button_music_volume_up, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music3), button_music_silence, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music4), button_music_volume, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(hbox_music4), button_music_reset_list, FALSE, FALSE, 0);
// 	gtk_box_pack_end(GTK_BOX(hbox_music4), button_music_choose_path, FALSE, FALSE, 0);
// 	gtk_box_pack_end(GTK_BOX(hbox_music4), button_music_delete_path, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music5), label_music_cur_time, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(hbox_music5), label_music_total_time, FALSE, FALSE, 0);
	
	/*
	gtk_box_pack_start(GTK_BOX(hbox_music6), label_music_autonext, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), switch_music_autonext, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), label_music_repeat, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), switch_music_repeat, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), label_music_shuffle, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), switch_music_shuffle, FALSE, FALSE, 0);
	*/
	gtk_box_pack_start(GTK_BOX(hbox_music6),label_music_mode_shuffle, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), radio_button_music_mode_shuffle, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6),label_music_mode_loop_list, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), radio_button_music_mode_loop_list, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6),label_music_mode_play_list, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), radio_button_music_mode_play_list, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6),label_music_mode_loop_one, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music6), radio_button_music_mode_loop_one, FALSE, FALSE, 0);
// 	gtk_box_pack_end(GTK_BOX(hbox_music6), spinner_music_mode_changing, FALSE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(vbox_music_process), scale_music_process, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_music_process), hbox_music5, FALSE, FALSE, 0);
	
// 	gtk_box_pack_start(GTK_BOX(vbox_music_list), view, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music_list), music_dir_list_sw, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_music_list), music_list_sw, FALSE, FALSE, 0);

	
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[0], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[1], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[2], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[3], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), separator_music_lyric2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[4], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), separator_music_lyric1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[5], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[6], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[7], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_lyric_contain), label_music_lyric[8], FALSE, FALSE, 0);

	
	gtk_container_add(GTK_CONTAINER(vbox_music_contain), music_info_sw);
// 	gtk_box_pack_start(GTK_BOX(vbox_music_contain), hbox_music1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_music_contain), hbox_music2, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_music_contain), hbox_music3, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_music_contain), hbox_music4, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_music_contain), vbox_music_process, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_music_contain), hbox_music6, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_music_contain), hbox_music_list, FALSE, FALSE, 0);
	//gtk_box_pack_start(GTK_BOX(vbox_music_contain), button_music_volume, FALSE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(vbox_info_lyric_contain), hbox_info_contain, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(vbox_info_lyric_contain), vbox_lyric_contain, FALSE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(hbox_bg), vbox_music_contain, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_bg), vbox_info_lyric_contain, FALSE, FALSE, 0);
	
// 	gtk_container_add(GTK_CONTAINER(frame_music), hbox_bg);

	
	return 1;
}

void set_music_all(GtkWidget *vbox_music) {
	init_music();
	int res;
	res = music_build_element_widgets ();
	if (res != 1) {
		perror ("music_build_element_widgets");
	}
	
	res = 0;
	//Creating music container widgets
	res = music_build_container_widgets ();
		if (res != 1) {
		perror ("music_build_container_widgets");
	}
	
	res = 0;
	//Arranging music widgets
	res = music_arrange_widgets ();
		if (res != 1) {
		perror ("music_arrange_widgets");
	}
	gtk_container_set_border_width (GTK_CONTAINER (vbox_music), 5);
	
	gtk_container_add(GTK_CONTAINER(vbox_music), hbox_bg);
	
// 	gui_update_music_dir_list();
// 	gui_update_music_list();
// 	gui_update_music_lyric_int_thread();
	guint timeout_source = g_timeout_add (1000, (GSourceFunc)music_gui_update_all, NULL);
	
// 	guint timeout_source1 = g_timeout_add (50, (GSourceFunc)test_func, NULL);
// 	music_gui_update_all_in_thread();
}
