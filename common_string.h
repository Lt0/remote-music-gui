#ifndef _COMMON_STRING_H
#define _COMMON_STRING_H
#define split_pattern "{!?!}"
int split_words(char *buf, char *words[], int words_num);
int split_words_from_file(char *path, char *words[], int words_num);
int split_lines(char *buf, char *lines[]);
int split_array_by_pattern(char *str, char *array[], char *pattern);

#endif