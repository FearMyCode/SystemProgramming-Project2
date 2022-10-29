#define _POSIX_C_SOURCE     200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include  <sys/param.h>

//  A HELPFUL PREPROCESSOR MACRO TO CHECK IF ALLOCATIONS WERE SUCCESSFUL
#define CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }


//  OUR SIMPLE LIST DATATYPE - A DATA ITEM, AND A POINTER TO ANOTHER LIST
typedef struct _list {
     char           *string;
     char           *pathname[MAXPATHLEN];
     int            npath;
     struct _list   *next;
} LIST;


//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN list.c :

//  'CREATE' A NEW, EMPTY LIST
extern	LIST	*list_new(void);

//   CHECK IF IDENTICAL LIST ITEM EXISTS 
extern    int list_check_existence(LIST *list, char *wanted_word, char *wanted_path);

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
extern	LIST	*list_add(  LIST *list, char *newstring, char *path);

//  DELETE A NEW (STRING) ITEM FROM AN EXISTING LIST
extern	void list_delete(  LIST *list, char *oldstring, char *path);

//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
extern	bool	 list_find (LIST *list, char *wanted);

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
extern	void	 list_print(LIST *list);
