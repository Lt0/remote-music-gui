#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "common.h"

extern client_sock;

void func_button_nfs_start(GtkWidget *button) {
	check_connection(client_sock);
	printf("sending control message....\n");
	char *command_str = "sudo service nfs-kernel-server start";
	send(client_sock,command_str , strlen(command_str), 0);
	recv_len = recv(client_sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
}

void func_button_nfs_stop(GtkWidget *button) {
	check_connection(client_sock);
	printf("sending control message....\n");
	char *command_str = "sudo service nfs-kernel-server stop";
	send(client_sock,command_str , strlen(command_str), 0);
	recv_len = recv(client_sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
}

void func_button_nfs_restart(GtkWidget *button) {
	check_connection(client_sock);
	printf("sending control message....\n");
	char *command_str = "sudo service nfs-kernel-server restart";
	send(client_sock,command_str , strlen(command_str), 0);
	recv_len = recv(client_sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
}

void func_button_smb_start(GtkWidget *button) {
	check_connection(client_sock);
	printf("sending control message....\n");
	char *command_str = "sudo service samba start";
	send(client_sock,command_str , strlen(command_str), 0);
	recv_len = recv(client_sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
}

void func_button_smb_stop(GtkWidget *button) {
	check_connection(client_sock);
	printf("sending control message....\n");
	char *command_str = "sudo service samba stop";
	send(client_sock,command_str , strlen(command_str), 0);
	recv_len = recv(client_sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
}

void func_button_smb_restart(GtkWidget *button) {
	check_connection(client_sock);
	printf("sending control message....\n");
	char *command_str = "sudo service samba restart";
	send(client_sock,command_str , strlen(command_str), 0);
	recv_len = recv(client_sock, recv_buf, BUFSIZ, 0);
	recv_buf[recv_len] = '\0';
	printf("%s\n", recv_buf);
}

void set_button_nfs_start(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_nfs_start), NULL);
}

void set_button_nfs_stop(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_nfs_stop), NULL);
}

void set_button_nfs_restart(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_nfs_restart), NULL);
}

void set_button_smb_start(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_smb_start), NULL);
}

void set_button_smb_stop(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_smb_stop), NULL);
}

void set_button_smb_restart(GtkWidget *button) {
	g_signal_connect((button), "clicked", G_CALLBACK(func_button_smb_restart), NULL);
}

void set_file_share_all(GtkWidget *vbox_file_share) {
	GtkWidget *frame_file_share;
	GtkWidget *vbox_contain;
	GtkWidget *frame_nfs;
	GtkWidget *vbox_nfs;
	GtkWidget *frame_smb;
	GtkWidget *vbox_smb;
	GtkWidget *hbox_nfs1;
	GtkWidget *hbox_nfs2;
	GtkWidget *hbox_smb1;
	GtkWidget *hbox_smb2;
	
	//GtkWidget *label_file_share;
	//GtkWidget *label_nfs;
	//GtkWidget *label_smb;
	GtkWidget *button_nfs_start;
	GtkWidget *button_nfs_stop;
	GtkWidget *button_nfs_restart;
	GtkWidget *button_smb_start;
	GtkWidget *button_smb_stop;
	GtkWidget *button_smb_restart;
	
	//Creating file_share labels
	//label_file_share = gtk_label_new("File Share Remote Control In Server");
	
	//Creating and setting file_share buttons
	//label_nfs = gtk_label_new("NFS Remote Control:");
	//label_smb = gtk_label_new("Samba Remote Control:");
	
	button_nfs_start = gtk_button_new_with_label("start");
	set_button_nfs_start(button_nfs_start);	
	
	button_nfs_stop = gtk_button_new_with_label("stop");
	set_button_nfs_stop(button_nfs_stop);
	
	button_nfs_restart = gtk_button_new_with_label("restart");
	set_button_nfs_restart(button_nfs_restart);
	
	button_smb_start = gtk_button_new_with_label("start");
	set_button_smb_start(button_smb_start);
	
	button_smb_stop = gtk_button_new_with_label("stop");
	set_button_smb_stop(button_smb_stop);
	
	button_smb_restart = gtk_button_new_with_label("restart");
	set_button_smb_restart(button_smb_restart);
	
	//Creating containers
	
	vbox_nfs = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width (GTK_CONTAINER (vbox_nfs), 5);
	vbox_smb = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width (GTK_CONTAINER (vbox_smb), 5);
	hbox_nfs1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	hbox_nfs2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	hbox_smb1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	hbox_smb2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	
	//Arranging file_shre widgets
	//gtk_box_pack_start(GTK_BOX(vbox_file_share), label_file_share, FALSE, FALSE, 0);
	gtk_container_set_border_width (GTK_CONTAINER (vbox_file_share), 5);
	//gtk_box_pack_start(GTK_BOX(vbox_file_share), vbox_nfs, FALSE, FALSE, 0);
	//gtk_box_pack_start(GTK_BOX(vbox_file_share), vbox_smb, FALSE, FALSE, 0);

	
	
	gtk_box_pack_start(GTK_BOX(vbox_nfs), hbox_nfs1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_nfs), hbox_nfs2, FALSE, FALSE, 0);
	
	//gtk_box_pack_start(GTK_BOX(hbox_nfs1), label_nfs, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_nfs2), button_nfs_start, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_nfs2), button_nfs_stop, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_nfs2), button_nfs_restart, FALSE, FALSE, 0);
	
	gtk_box_pack_start(GTK_BOX(vbox_smb), hbox_smb1, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_smb), hbox_smb2, FALSE, FALSE, 0);
	
	//gtk_box_pack_start(GTK_BOX(hbox_smb1), label_smb, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_smb2), button_smb_start, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_smb2), button_smb_stop, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_smb2), button_smb_restart, FALSE, FALSE, 0);
	
	frame_nfs = gtk_frame_new("NFS");
	gtk_container_set_border_width (GTK_CONTAINER (frame_nfs), 5);
	frame_smb = gtk_frame_new("Samba");
	gtk_container_set_border_width (GTK_CONTAINER (frame_smb), 5);
	
	gtk_container_add(GTK_CONTAINER(frame_nfs), vbox_nfs);
	gtk_container_add(GTK_CONTAINER(frame_smb), vbox_smb);
	
	//gtk_box_pack_start(GTK_BOX(vbox_file_share), frame_nfs, FALSE, FALSE, 0);
	//gtk_box_pack_start(GTK_BOX(vbox_file_share), frame_smb, FALSE, FALSE, 0);
	
	vbox_contain = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(vbox_contain), frame_nfs, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox_contain), frame_smb, FALSE, FALSE, 0);
	
	frame_file_share = gtk_frame_new("File Share remote control");
	gtk_container_add(GTK_CONTAINER(frame_file_share), vbox_contain);
	//gtk_container_add(GTK_CONTAINER(frame_file_share), frame_smb);
	gtk_box_pack_start(GTK_BOX(vbox_file_share), frame_file_share, FALSE, FALSE, 0);


}
