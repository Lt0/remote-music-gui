#ifndef COMMON_H
#define COMMON_H

//gint client_sock = client_sock;

gint client_sock;
gint music_data_client_sock;
//gint *client_sock_ptr;

fd_set recv_readfd;

char split_words_buf[BUFSIZ];

//recv_timeout.tv_sec = 2;
//recv_timeout.tv_usec = 200;

gchar recv_buf[BUFSIZ], send_buf[BUFSIZ];
char *p_recv_buf;
char *p_send_buf;
static gint recv_len, send_len;
char server_addr[BUFSIZ];
// gchar *server_addr;
const gchar *tmp_server_addr_str;
//gint connect_status = 0;

void func_close_window(GtkWidget *window, gpointer data);
void set_window_main(GtkWidget *window);
void set_button_close(GtkWidget *button);

int connect_server(char *server_addr, int port);
int check_connection(int sock);
gpointer keep_connect(gpointer data);
void show_connect_failed();
void *connect_func(void *arg);

#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));};

GtkWidget *working_label;
GtkWidget* button_with_image_and_text(gchar *filename, gchar *text);
GtkWidget* button_with_image(gchar *filename);

#endif