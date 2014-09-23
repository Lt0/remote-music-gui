#ifndef CONTROL_FILE_H
#define CONTROL_FILE_H



void func_button_nfs_start(GtkWidget *button);
void func_button_nfs_stop(GtkWidget *button);
void func_button_nfs_restart(GtkWidget *button);
void func_button_smb_start(GtkWidget *button);
void func_button_smb_stop(GtkWidget *button);
void func_button_smb_restart(GtkWidget *button);
void set_button_nfs_start(GtkWidget *button);
void set_button_nfs_stop(GtkWidget *button);
void set_button_nfs_restart(GtkWidget *button);
void set_button_smb_start(GtkWidget *button);
void set_button_smb_stop(GtkWidget *button);
void set_button_smb_restart(GtkWidget *button);
void set_file_share_all(GtkWidget *vbox_file_share);

#endif