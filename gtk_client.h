#ifndef GTK_CLIENT_H
#define GTK_CLIENT_H

#include <gtk/gtk.h>
#include <pthread.h>
#include "control_music.h"
#include "control_file_share.h"
#include "connect.h"
#include "common.h"
#include "control_music_config.h"
#include "../raspi_server/server_common.h"

pthread_t start_message_thread;

struct message {
  char title[BUFSIZ];
  char format[BUFSIZ];
  char secondary[BUFSIZ];
} start_message;

int analy_config_all();
void show_start_info();
void * show_dialog_in_thread(void *arg);


#endif