#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

int split_words_from_file(char *path, char *words[], int words_num) {
	FILE *file;
	char *buf;
	int num;
	if (access(path, F_OK) != 0) {
		printf("split_words_from_file error: File not found: %s.\n", path);
		return -1;
	}
	file = fopen(path, "r");
	if ((buf = malloc(1024*4)) == NULL) {
		return -1;
	}
	memset(buf, '\0', 1024 * 4);
	fread(buf, 1024, 4, file);
	fclose(file);
	num = split_words(buf, words, words_num);
	free(buf);
	return num;
}

int split_lines(char *buf, char *lines[]) {
// 	printf("buf: %s\n", buf);
	char *split_lines_tmp_str;
	int i, j, k, changed;
	j = 0;
	k = 0;
	changed = 0;
	if ((split_lines_tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
// 	for (i = 0; i<sizeof(split_lines_buf) && *(buf + i) != '\0'; i++) {
	for (i = 0; i<strlen(buf) && *(buf + i) != '\0'; i++) {
// 		printf("i: %d\n", i);
// 		printf("split_lines_buf[%d]: %c\n", i, *(buf + i));
		while ( *(buf + i) != '\n' && *(buf + i) != '\0') {
// 			printf("split_lines_buf[%d]: %c\n", i, *(buf + i));
			*(split_lines_tmp_str + j) = *(buf + i);
// 			printf("split_lines_tmp_str[%d]: %c\n", j, split_lines_tmp_str[j]);
			i++;
			j++;
			changed = 1;
		}
		if (changed != 0) {
// 			printf("changed: %d\n", changed);
			if ((lines[k] = malloc(strlen(split_lines_tmp_str) + 1)) == NULL) {
				printf("error: malloc for lines[%d] failed\n", k);
				free(split_lines_tmp_str);
				return k;
			}
// 			printf("malloc for lines[%d]\n", k);
			*(split_lines_tmp_str + j) = '\0';
			memset (lines[k], '\0', (strlen(split_lines_tmp_str) + 1));
// 			printf("split_lines_tmp_str: %s\n", split_lines_tmp_str);
			strcpy(lines[k], split_lines_tmp_str);
// 			printf("lines[%d]: %s\n", k, lines[k]);
			memset (split_lines_tmp_str, '\0', BUFSIZ);
			j = 0;
			k++;
			changed = 0;
		}
	}
	free(split_lines_tmp_str);
// 	printf("split_lines finished\n");
	return k;
}


int split_words(char *buf, char *words[], int words_num) {
// 	printf("buf: %s\n", buf);
	char *split_words_tmp_str;
	int i, j, k, changed;
	j = 0;
	k = 0;
	changed = 0;
	if ((split_words_tmp_str = malloc(BUFSIZ)) == NULL) {
		return -1;
	}
// 	for (i = 0; i<sizeof(split_words_buf) && *(buf + i) != '\0'; i++) {
	for (i = 0; i<strlen(buf) && *(buf + i) != '\0'; i++) {
// 		printf("i: %d\n", i);
// 		printf("split_words_buf[%d]: %c\n", i, *(buf + i));
		while (*(buf + i) != ' ' && *(buf + i) != '\n' && *(buf + i) != '\0') {
// 			printf("split_words_buf[%d]: %c\n", i, *(buf + i));
			*(split_words_tmp_str + j) = *(buf + i);
// 			printf("split_words_tmp_str[%d]: %c\n", j, split_words_tmp_str[j]);
			i++;
			j++;
			changed = 1;
		}
		if (changed != 0 && k < words_num) {
			words[k] = strdup(split_words_tmp_str);
// 			printf("words[%d]: %s\n", k, words[k]);
			memset (split_words_tmp_str, '\0', BUFSIZ);
			j = 0;
			k++;
			changed = 0;
		} else if (k >= words_num) {
			return k;
		}
	}
	free(split_words_tmp_str);
// 	printf("split_words finished\n");
	return k;
}

int split_array_by_pattern(char *str, char *array[], char *pattern) {
//   printf("split_array_by_pattern str: %s\n", str);
//   printf("pattern: %s\n", pattern);
  char *tmp_char;
  int num = 0;
  tmp_char = strtok(str, pattern);
  if (tmp_char == NULL) {
    return num;
  }
  if ((array[num] = malloc(strlen(tmp_char) + 1)) == NULL ) {
    printf("ERROR: split_array_by_pattern:");
    return -1;
  }
  
  strcpy(array[num], tmp_char);
//   printf("splited: array[%d]: %s\n",num, array[num]);
  num++;
  while (tmp_char != NULL) {
    tmp_char = strtok(NULL, pattern);
    if (tmp_char != NULL) {
      if ((array[num] = malloc(strlen(tmp_char) + 1)) == NULL ) {
	printf("ERROR: split_array_by_pattern:");
	return num;
      }
      strcpy(array[num], tmp_char);
//       printf("splited: array[%d]: %s\n",num, array[num]);
      num++;
    }
  }
//   printf("split_array_by_pattern str: %s\n", str);
//   printf("pattern: %s\n", pattern);
  return num;
}
