#include "gtk_client.h"

int main(int argc, char *argv[]) {
//   	connect_server(server_addr);
	analy_config_all();
	if (cur_config_music.music_server_ip ==NULL || !strcmp(cur_config_music.music_server_ip, "127.0.0.1") || 				 !strcmp(cur_config_music.music_server_ip, "localhost")) {
	  printf("############run_server_in_client############\n");
	  run_server_in_client(1);
	}

	GtkWidget *window;
	GtkWidget *button_close;
	GtkWidget *hbox_close;
	GtkWidget *vbox_pre;
	GtkWidget *vbox_connect;
	//GtkWidget *frame_connect;
	GtkWidget *vbox_music;
	//GtkWidget *frame_music;
	GtkWidget *vbox_file_share;
	
	GtkWidget *note_book;
	//GtkWidget *note_book_music;
	//GtkWidget *note_book_file_share;
	
	GtkWidget *info_bar;
	GtkWidget *vbox_working_info;

	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	set_window_main(window);
	
// 	working_label = gtk_label_new (NULL);
	
	
	vbox_connect = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	set_connect_all(vbox_connect);
	//gtk_container_add(GTK_CONTAINER(frame_connect), vbox_connect);

	//frame_music = gtk_frame_new("Music Remote Control");
	vbox_music = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
// 	gtk_container_set_resize_mode (GTK_CONTAINER(vbox_music), GTK_RESIZE_IMMEDIATE);
	set_music_all(vbox_music);
	//gtk_container_add(GTK_CONTAINER(frame_music), vbox_music);

	
	vbox_file_share = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	set_file_share_all(vbox_file_share);
	//gtk_container_add(GTK_CONTAINER(frame_file_share), vbox_file_share);

	//vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	//gtk_container_set_border_width (GTK_CONTAINER (vbox), 5);
	//gtk_box_pack_start(GTK_BOX(vbox), vbox_connect, FALSE, FALSE, 5);
	//gtk_box_pack_start(GTK_BOX(vbox), frame_connect, TRUE, TRUE, 5);
	//gtk_box_pack_start(GTK_BOX(vbox), vbox_music, FALSE, FALSE, 5);
	//gtk_box_pack_start(GTK_BOX(vbox), frame_music, TRUE, TRUE, 5);
	//gtk_box_pack_start(GTK_BOX(vbox), vbox_file_share, FALSE, FALSE, 5);
	//gtk_box_pack_start(GTK_BOX(vbox), frame_file_share, TRUE, TRUE, 5);
	
	//frame = gtk_frame_new("Remote Control");
	//gtk_frame_set_label_align(GTK_FRAME(frame), 0.5, 0.5);
	//makegtk_container_add(GTK_CONTAINER(frame), vbox);
	
	/*
	note_book = gtk_notebook_new();
	gtk_notebook_set_scrollable (GTK_NOTEBOOK(note_book), TRUE);
	
	gtk_notebook_append_page(GTK_NOTEBOOK(note_book), vbox_music, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK(note_book), vbox_music, "music");
	
	gtk_notebook_append_page(GTK_NOTEBOOK(note_book), vbox_connect, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK(note_book), vbox_connect, "status");
	
	gtk_notebook_append_page(GTK_NOTEBOOK(note_book), vbox_file_share, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK(note_book), vbox_file_share, "file share");
	*/
	
// 	info_bar = gtk_info_bar_new();
// 	gtk_info_bar_set_show_close_button (GTK_INFO_BAR(info_bar), TRUE);
	
	button_close = gtk_button_new_with_label("Close");
	set_button_close(button_close);
	hbox_close = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_pack_end(GTK_BOX(hbox_close), button_close, FALSE, FALSE, 5);
	
	vbox_pre = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (vbox_pre), 0);
// 	gtk_box_pack_start(GTK_BOX(vbox_pre), note_book, FALSE, FALSE, 5);
	
	gtk_box_pack_start(GTK_BOX(vbox_pre), vbox_music, FALSE, FALSE, 5);
// 	gtk_box_pack_end(GTK_BOX(vbox_pre), working_label, FALSE, FALSE, 5);
// 	gtk_box_pack_start(GTK_BOX(vbox_pre), hbox_close, FALSE, FALSE, 5);
	
// 	gtk_box_pack_start(GTK_BOX(vbox_pre), GTK_WIDGET(info_bar), FALSE, FALSE, 5);
	
	
	gtk_container_add(GTK_CONTAINER(window), vbox_pre);
	
	
	
	gtk_widget_show_all(window);
	
// 	show_start_info (window);
	pthread_cancel(start_message_thread);
	g_thread_new(NULL, keep_connect, NULL);

	
// 	init_music_list("/home/lt/remote", music_walk_files);
	gtk_main();
	
	
	return 0;
}

int analy_config_all() {
  config_music_file_path = strdup("/etc/raspi_remote_control/config_music.txt");
  analy_config_music();
}

void show_start_info() {
//   pthread_t a_thread;
  int res;
//   char *message[3];
  memset(start_message.title, '\0', BUFSIZ);
  memset(start_message.format, '\0', BUFSIZ);
  memset(start_message.secondary, '\0', BUFSIZ);
  strcpy(start_message.title, "Connect Information");
  strcpy(start_message.format, "gtk_client");
  strcpy(start_message.secondary, "啊列？后台还没搞定的样子....");
  void *vptr = (void *)&start_message;
  res = pthread_create(&start_message_thread, NULL, show_dialog_in_thread, vptr);
//   GtkWidget *md;
// //   md = gtk_message_dialog_new (GTK_WINDOW(window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, "gtk_client");
//   md = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_NONE, "gtk_client");
//   gtk_window_set_title(GTK_WINDOW(md), "Information");
//   gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG(md), "啊列？后台还没搞定的样子....");
//   gtk_widget_show (md);
//   gtk_dialog_run (GTK_DIALOG(md));
//   
//   gtk_widget_destroy (md);
//   return &a_thread;
}

void * show_dialog_in_thread(void *arg) {
  int res;
  res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
      if (res != 0) {
      perror("Thread pthread_setcancelstate failed)");
//       pthread_exit(1);
  }
  res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
//   struct message *tmp_message;
//   tmp_message = (struct message *) arg;
  GtkWidget *md;
  md = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Connect Information");
  gtk_window_set_title(GTK_WINDOW(md), "Connect Information");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG(md), "啊列？后台还没搞定的样子....");
  gtk_widget_show (md);
//   gtk_dialog_run (GTK_DIALOG(md));
//   gtk_widget_destroy (md);
}