#define _POSIX_C_SOURCE     200809L
#define _XOPEN_SOURCE 500

#include  <limits.h>
#include  <stdio.h>
#include  <stdbool.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <dirent.h>
#include  <sys/param.h>
#include  <time.h>
#include  <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#include "hashtable.h"

typedef struct {
    char        *pathname;
    int         RK;//reference key for pathname
} FILES;

//Builds hashtable based on filelist content
extern void build_hashtable(char *filename, HASHTABLE *, int word_length, bool is_deletion);

//Deletes from hashtable based on filelist content
// void delete_from_hashtable(char *filename, HASHTABLE *h);

//Traverses all folders and subfolders for files in given directory
// void scan_directory_delete(char dirname[MAXPATHLEN], HASHTABLE *h);

//Traverses all folders and subfolders for files in given directory
extern  void scan_directory(char dirname[MAXPATHLEN], HASHTABLE *, int word_length, bool is_deletion);

//Read all individual word above givven length in givven file
extern void scan_file(char *filename, HASHTABLE *, int word_length, bool is_deletion);