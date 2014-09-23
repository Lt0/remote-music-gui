#include <gtk/gtk.h>
//#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "control_music.h"
#include "common_string.h"

struct timeval recv_timeout = {0,200};

void func_close_window(GtkWidget *window, gpointer data) {
	printf("Sending quit message to server....\n");
	send(client_sock, "quit", 4, 0);
	send(play_info_sock, "quit", 4, 0);
	printf("Closing client_sock: %d\n", client_sock);
	close(client_sock);
	printf("Closing play_info_sock: %d\n", play_info_sock);
	close(play_info_sock);
	printf("closed client socket.\n");
	printf("Closing window....\n");
	gtk_main_quit();
}

void set_window_main(GtkWidget *window) {
	gtk_window_set_title(GTK_WINDOW(window), "pc client gtk");
	gtk_window_set_default_size(GTK_WINDOW(window), 700, 400);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	//gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
	g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(func_close_window), NULL);
}

void set_button_close(GtkWidget *button) {
	g_signal_connect(button, "clicked", G_CALLBACK(func_close_window), NULL);
}

int check_connection(int sock) {
	
	if(sock == 0) {
		
		//printf("Unconnected.\nReconnecting....\n");
		close(sock);
		//connect_server(server_addr);
		printf("sock: %d error\n", sock);
		perror("check_connection");
		return -1;
	}
	return 0;
}

int connect_server(char *server_addr, int port) {
	struct sockaddr_in remote_addr;
	int tmp_client_sock;
	//const char *server_addr = "192.168.10.1";
	//printf("Server address: %s\n", server_addr);
	
	memset(&remote_addr, 0, sizeof(remote_addr));
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_addr.s_addr = inet_addr(server_addr);
	remote_addr.sin_port = htons(port);

	if ((tmp_client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return -1;

	}
	
	if (connect(tmp_client_sock, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) < 0) {
		perror("connect");
		return -1;

	}
	//client_sock_ptr = &client_sock;
	printf("connected to server: %s\ncurrent client sock is: %d\n", server_addr, tmp_client_sock);
	recv_len = recv(tmp_client_sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	//printf("%s", recv_buf);
	return tmp_client_sock;

}

gpointer keep_connect(gpointer data) {
  while (1) {
//     printf("keep_connect checking connect : %d\n", play_info_sock);
    if (play_info_sock <= 0) {
//       close();
//       show_connect_failed();
      printf("reconnecting play_info_sock\n");
      play_info_sock = connect_server(cur_config_music.music_server_ip, cur_config_music.socket_port);
      printf("new play_info_sock: %d\n", play_info_sock);
      get_music_dirs_from_server(1);
      gui_update_music_dir_list(1);
    }
    sleep (1);
  }
}

void show_connect_failed() {
  GtkWidget *md;
  md = gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Connect Information");
  gtk_window_set_title(GTK_WINDOW(md), "Connect Information");
  gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG(md), "啊列？后台还没搞定的样子....");
  gtk_widget_show (md);
//   gtk_widget_destroy(md);
}


GtkWidget* button_with_image_and_text(gchar *filename, gchar *text) {
	GtkWidget *box;
	GtkWidget *label;
	GtkWidget *image;
	
	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	
	image = gtk_image_new_from_file(filename);
	label = gtk_label_new(text);
	
	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);
	
	gtk_widget_show(image);
	gtk_widget_show(label);
	
	return box;
}

GtkWidget* button_with_image(gchar *filename) {
	GtkWidget *box;
	GtkWidget *image;
	
	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	
	image = gtk_image_new_from_file(filename);
	
	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 5);
	
	gtk_widget_show(image);
	
	return box;
}