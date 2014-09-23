#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "common.h"
#include "connect.h"

extern client_sock;

void func_button_connect_server(GtkWidget *button) {
// 	connect_server(server_addr);
}

void func_button_unconnect_server(GtkWidget *button, gpointer data) {
	//check_connection();
	printf("%s\n", (char *)data);
	printf("Sending quit message to server....\n");
	send(client_sock, "This client quit.", 17, 0);
	close(client_sock);
	
	client_sock = 0;
	printf("finish.\n");	
}

void set_button_connect(GtkWidget *button_connect) {
	g_signal_connect((button_connect), "clicked", G_CALLBACK(func_button_connect_server), NULL);
}

void set_button_unconnect(GtkWidget *button_unconnect) {
	g_signal_connect((button_unconnect), "clicked", G_CALLBACK(func_button_unconnect_server), "Unconnecting....");
}

void set_connect_all(GtkWidget *vbox_connect) {
	GtkWidget *hbox_connect;
	//GtkWidget *vbox_contain_frame;
	GtkWidget *frame_connect;
	GtkWidget *button_connect;
	GtkWidget *button_unconnect;
	
	//Creating and setting connect buttons
	button_connect = gtk_button_new_with_label("Connect");
	set_button_connect(button_connect);
	
	button_unconnect = gtk_button_new_with_label("Unconnect");
	set_button_unconnect(button_unconnect);
	
	//Creating connect container
	hbox_connect = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_set_border_width (GTK_CONTAINER (hbox_connect), 5);
	
	//Arranging connect widgets
	gtk_box_pack_start(GTK_BOX(hbox_connect), button_connect, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(hbox_connect), button_unconnect, FALSE, FALSE, 0);

	frame_connect = gtk_frame_new("Connect");
	gtk_container_add(GTK_CONTAINER(frame_connect), hbox_connect);
	gtk_container_set_border_width (GTK_CONTAINER (vbox_connect), 5);
	gtk_box_pack_start(GTK_BOX(vbox_connect), frame_connect, FALSE, FALSE, 0);
	
	
	
	
	
	GtkWidget *entry_server_addr;
	entry_server_addr = gtk_entry_new();
	gtk_entry_set_text (GTK_ENTRY(entry_server_addr), "192.168.10.1");
// 	gtk_entry_set_text (GTK_ENTRY(entry_server_addr), "127.0.0.1");
	gtk_entry_set_max_length (GTK_ENTRY(entry_server_addr), 15);
	gtk_container_add (GTK_CONTAINER (hbox_connect), entry_server_addr);
	
	tmp_server_addr_str = gtk_entry_get_text (GTK_ENTRY(entry_server_addr));
	printf("tmp_server_addr_str: %s\n", tmp_server_addr_str);
	//server_addr = strcpy(server_addr, tmp_server_addr_str);
	strcpy(server_addr, tmp_server_addr_str);
	//server_addr = tmp_str;
	
	/*
	GtkEntryBuffer *buffer_server_addr;
	
	
	
	GtkListStore *lstore_server_addr;
	GtkTreeIter iter;
	
	//GtkTreeModel *model;
	GtkWidget *combo;
	
	GtkCellRenderer *renderer;
	
	gtk_tree_store_append (lstore_server_addr, &iter, NULL);
	gtk_tree_store_set (lstore_server_addr, &iter, 0, "192.168.10.1", -1);
	
	combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL (lstore_server_addr));
	
	//renderer = gtk_cell_renderer_text_new ();
	//gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (combo), renderer, FALSE);
	//gtk_cell_layout_add_attributes (GTK_CELL_LAYOUT (combo), renderer,0, "text", NULL);

	


	gtk_container_add (GTK_CONTAINER (vbox_connect), combo);
	*/
}


