#ifndef CONNECT_H
#define CONNECT_H

gint client_sock;

void func_button_connect_server(GtkWidget *button);
void func_button_unconnect_server(GtkWidget *button, gpointer data);
void set_button_connect(GtkWidget *button_connect);
void set_button_unconnect(GtkWidget *button_unconnect);
void set_connect_all(GtkWidget *vbox_connect);
static GtkTreeModel *Create_store_server_addr(void);

#endif