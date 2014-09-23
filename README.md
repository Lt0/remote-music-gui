remote-music-gui
================

  It's a remote control application which used to control the music played in raspberry by PC(linux).
  It include the music list(auto create by music folders in raspberry), 
basic control (stop, pause, play, next, pre, progress bar, volume adjustment), show music info and lyric show.
  It was written by C and GTK, compiled by gnu toolchain in linux.
  I just run it in ubuntu, cent os and openSUSE but it should be easy to compile in windows and run.

  Before compile you should make should you have installed the cmake, gnu toolchain and gtk develop toolkit in you system.
  Compiling the server:
	After download all code files, cd to the code file's folder and run the command: make server.

  Compiling the client:
	CD to the code file's folder and run command: make client


  How to use:
	Just see the install_and_config file.
