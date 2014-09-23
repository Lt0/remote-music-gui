PKG_CONFIG_PATH=/usr/include/gtk-3.0
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/gtk3.0

gtk_client: gtk_client.o common.o common_string.o connect.o control_music.o control_music_gui.o control_music_data.o control_music_common.o  control_music_func.o control_music_set.o control_music_config.o control_file_share.o server_control_music.o server_control_local.o server_common_string.o server_common_config.o server_common_run.o server_common.o
	gcc -g -o gtk_client gtk_client.o common.o common_string.o connect.o control_music.o control_music_gui.o control_music_data.o control_music_common.o control_music_func.o control_music_set.o control_music_config.o control_file_share.o server_control_music.o server_control_local.o server_common_string.o server_common_config.o server_common_run.o server_common.o -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`

gtk_client.o: gtk_client.c
	gcc -c -g gtk_client.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`
	
common.o: common.c
	gcc -c -g common.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`

common_string.o: common_string.c
	gcc -c -g common_string.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`

connect.o: connect.c
	gcc -c -g connect.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`
	
control_music.o: control_music.c
	gcc -c -g control_music.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`
	
control_music_gui.o: control_music_gui.c
	gcc -c -g control_music_gui.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`

control_music_data.o: control_music_data.c
	gcc -c -g control_music_data.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`

control_music_common.o: control_music_common.c
	gcc -c -g control_music_common.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`
	
control_music_func.o: control_music_func.c
	gcc -c -g control_music_func.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`

control_music_set.o: control_music_set.c
	gcc -c -g control_music_set.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`

control_music_config.o: control_music_config.c
	gcc -c -g control_music_config.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`
	
control_file_share.o: control_file_share.c
	gcc -c -g control_file_share.c -DGDK_VERSION_MAX=GDK_VERSION_3.4 `pkg-config --cflags --libs gtk+-3.0`
	
	

server_control_music.o: ../raspi_server/server_control_music.c
	gcc -c ../raspi_server/server_control_music.c

server_control_local.o: ../raspi_server/server_control_local.c 
	gcc -c ../raspi_server/server_control_local.c 
	
server_common_string.o: ../raspi_server/server_common_string.c
	gcc -c ../raspi_server/server_common_string.c
	
server_common_config.o: ../raspi_server/server_common_config.c
	gcc -c ../raspi_server/server_common_config.c
	
server_common_run.o: ../raspi_server/server_common_run.c
	gcc -c ../raspi_server/server_common_run.c
	
server_common.o: ../raspi_server/server_common.c
	gcc -c ../raspi_server/server_common.c

clean:
	-rm -rf *.o gtk_client
	
release:
	echo $0
	echo $1
	echo $2
	mkdir ../release-$2
	cp -r ./* ../release-$2/
	tar -cvzf ../release-$2.tar.gz ../release$2
