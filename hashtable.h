#define _POSIX_C_SOURCE     200809L
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/param.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include  <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "list.h"

// Defines where the location of gzip is, as this can vary from LINUX and windows
#define GZIP_PATH "C:/usr/bin/gzip"

//  RESEARCH SHOWS THAT USING PRIME-NUMBERS CAN IMPROVE PERFORMANCE
//  c.f.  https://www.quora.com/Why-should-the-size-of-a-hash-table-be-a-prime-number
#define	HASHTABLE_SIZE		977


//  WE DEFINE A HASHTABLE AS A (WILL BE, DYNAMICALLY ALLOCATED) ARRAY OF LISTs
typedef	LIST * HASHTABLE;



//  THESE FUNCTIONS ARE DECLARED HERE, AND DEFINED IN hashtable.c :

//  ALLOCATE SPACE FOR A NEW HASHTABLE (AND ARRAY OF LISTS)
extern	HASHTABLE	*hashtable_new(void);

//  ADD A NEW STRING TO A GIVEN HASHTABLE
extern	void		 hashtable_add( HASHTABLE *hashtable, char *string, char *path);

//  DELETE PATHS
extern	void		 hashtable_delete( HASHTABLE *hashtable, char *string, char *path);

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
extern	bool		 hashtable_find(HASHTABLE *, char *string);


extern  void hashtable_export2csv(HASHTABLE *hashtable, char *filename);


extern  void hashtable_importfromcsv(HASHTABLE *hashtable, const char *filename);
