#ifndef CONTROL_MUSIC_H
#define CONTROL_MUSIC_H

#include "../raspi_server/server_control_music.h"

extern client_sock;
extern struct timeval recv_timeout;

// char music_path[BUFSIZ];
guint music_timeout;




double volume_get_value;
int volume_last_value;
int volume_cur_value;


int tmpvalue;
char tmpstr[4];
int client_sock;


//配置相关全局变量
struct config_music {
	char *music_server_ip;
	int socket_port;
	char *lyric_save_path;
} cur_config_music;
char *config_music_file_path;

//---------------------------------------------当前播放状态相关全局变量---------------------------------------------
int play_info_sock;
// int get_data_from_server;

//歌曲播放状态相关全局变量
// struct music_info {
// 	char state[13];
// 	char file[BUFSIZ];
// 	char title[BUFSIZ];
// 	char artist[BUFSIZ];
// 	char song_title[BUFSIZ];
// 	char album[BUFSIZ];
// 	char total_time[9];
// 	char time_left[9];
// 	int total_sec;
// 	char cur_time[9];
// 	int cur_sec;
// 	char bitrate[8];
// 	char avg_bitrate[8];
// 	char rate[8];
// 	int play_mode;
// 	int play_path;
// 	int play_iter;
//   
// } cur_music_info;

struct music_info client_music_info;

char *format_music_info_unsave_str;



enum music_state {
	state_play,
	state_pause,
	state_unpause,
	state_stop,
	state_server_stop,
	state_server_start
};

// enum play_mode{
// 	shuffle,
// 	loop_list,
// 	play_list,
// 	loop_one,
// 	play_one,
// };

enum music_play_mode {
	play_mode_shuffle,
	play_mode_loop_list,
	play_mode_play_list,
	play_mode_loop_one
};

char test_buf[BUFSIZ];


//---------------------------------------------当前播放状态相关全局变量---------------------------------------------

//---------------------------------------------播放列表相关全局变量---------------------------------------------
int play_list_sock;

enum {
	dir_name,
	dir_n_columns,
};

enum {
	list_index,
	list_title,
	list_total_sec,
	list_n_columns,
};
// char music_list[BUFSIZ][BUFSIZ];
char *dir_list[BUFSIZ];
// int path_iter;
char *music_list[BUFSIZ];
int music_list_num;
int music_dir_list_num;
//---------------------------------------------播放列表相关全局变量---------------------------------------------

//---------------------------------------------歌词相关全局变量---------------------------------------------
struct music_lyric_sentence {
	float time;
	char sentence[1024];
} cur_lyric[200];

struct tmp_music_lyric_sentence {
	float time;
	char *sentence;
} tmp_cur_lyric[200];

FILE *lyric_file;
char lyric_buf[1024*4];
char local_lyric_folder[BUFSIZ];
gboolean cur_lyric_file_existed;
char lyric_tags[BUFSIZ][1024];
int lyric_show_iter;
int lyric_show_iter_last;
int lyric_valid_iter;
char cur_lyric_name[BUFSIZ];

//---------------------------------------------歌词相关全局变量---------------------------------------------

GtkWidget *frame_music;
GtkWidget *hbox_bg;
GtkWidget *vbox_music_contain;
GtkWidget *vbox_info_lyric_contain;
GtkWidget *vbox_lyric_contain;
GtkWidget *hbox_info_contain;
GtkWidget *vbox_music_process;
GtkWidget *music_info_sw;
GtkWidget *separator_music_info;
GtkWidget *hbox_music2;
GtkWidget *hbox_music3;
GtkWidget *hbox_music4;
GtkWidget *hbox_music5;
GtkWidget *hbox_music6;
GtkWidget *vbox_music_info_left;
GtkWidget *vbox_music_info_right;
GtkWidget *hbox_music_list;
GtkAdjustment *music_list_sw_adj_h;
GtkWidget *music_list_sw;
GtkAdjustment *music_dir_list_sw_adj_h;
GtkWidget *music_dir_list_sw;

GtkWidget *box_music_bg;



GtkWidget *label_music_info[9];
GtkWidget *label_music_lyric[9];
GtkWidget *separator_music_lyric1;
GtkWidget *separator_music_lyric2;



GtkWidget *button_music_start_server;
GtkWidget *button_music_exit_server;

GtkWidget *button_music_play;
GtkWidget *button_music_pause;
GtkWidget *button_music_unpause;
GtkWidget *button_music_stop;
GtkWidget *button_music_next;
GtkWidget *button_music_pre;


// GtkWidget *box_music_play;
// GtkWidget *box_music_pause;
// GtkWidget *box_music_next;
// GtkWidget *box_music_pre;
// GtkWidget *box_music_pre_focus;
// GtkWidget *box_music_stop;
// GtkWidget *box_music_silence;

GtkWidget *image_music_play;
GtkWidget *image_music_play_light;
GtkWidget *image_music_pause;
GtkWidget *image_music_pause_light;
GtkWidget *image_music_unpause;
GtkWidget *image_music_stop;
GtkWidget *image_music_stop_light;
GtkWidget *image_music_next;
GtkWidget *image_music_next_light;
GtkWidget *image_music_pre;
GtkWidget *image_music_pre_light;
GtkWidget *image_music_silence;
GtkWidget *image_music_silence_light;
GtkWidget *image_music_unsilence;
GtkWidget *image_music_unsilence_light;

// GtkWidget *button_music_volume_up;
GtkWidget *button_music_silence;
GtkWidget *button_music_volume;
GtkWidget *button_music_reset_list;
GtkWidget *music_path_dialog;
GtkWidget *button_music_choose_path;
GtkWidget *button_music_delete_path;

GtkWidget *scale_music_process;
gboolean process_gui_update;

GtkWidget *label_music_cur_time;
GtkWidget *label_music_total_time;

GtkWidget *switch_music_autonext;
GtkWidget *label_music_autonext;
GtkWidget *switch_music_repeat;
GtkWidget *label_music_repeat;
GtkWidget *switch_music_shuffle;
GtkWidget *label_music_shuffle;

GtkWidget *radio_button_music_mode_shuffle;
GtkWidget *label_music_mode_shuffle;
GtkWidget *radio_button_music_mode_loop_list;
GtkWidget *label_music_mode_loop_list;
GtkWidget *radio_button_music_mode_play_list;
GtkWidget *label_music_mode_play_list;
GtkWidget *radio_button_music_mode_loop_one;
GtkWidget *label_music_mode_loop_one;
GtkWidget *spinner_music_mode_changing;

GtkTreeStore *store_music_dir_list;
GtkWidget *tree_view_music_dir_list;
GtkCellRenderer *text_renderer_music_dir_list;
GtkTreeViewColumn *column_music_dir_list;
GtkTreeSelection *selection_music_dir_list;

GtkTreeStore *store_music_list;
// GtkTreeIter iter_music_list;
GtkWidget *tree_view_music_list;
GtkCellRenderer *text_renderer_music_list;
GtkTreeViewColumn *column_music_list;
GtkTreeSelection *selection_music_list;

int music_build_element_widgets ();
int music_build_container_widgets ();
int music_arrange_widgets ();

#endif