
#include "directory.h"


//  AS DISCUSSED IN WORKSHOP-7 :
#define	CHECK_ALLOC(p) if(p == NULL) { perror(__func__); exit(EXIT_FAILURE); }

FILES           *files  = NULL;
int             nfiles  = 0;
char absolute_path[MAXPATHLEN];
bool is_deletion;

void build_hashtable(char *filename, HASHTABLE *h, int word_length, bool is_deletion){
//  ATTEMPT TO OPEN THE FILE FOR READ-ONLY ACCESS

    struct stat     stat_info;

    int fd    = open(filename, O_RDONLY);

    if(fd == -1) {
        printf("cannot open '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    

    char   buffer[10000];
    size_t got;
    int file_size = 0;
    
    while((got = read(fd, buffer, sizeof buffer)) > 0) {
        file_size += got;
    }
    close(fd);
    
    char buff[MAXPATHLEN];
    int j;
    for(int i=0; i < file_size; i++){
        while(buffer[i] == '\n' || buffer[i] == '\r'){i++;}

        //memset(buff, 0, sizeof buff); //Reset buff array
        j = 0;
        while(buffer[i] != '\n' && buffer[i] != '\r' && i < file_size){
            buff[j] = buffer[i];
            i++;
            j++;
        }
        buff[j] = '\0';

        //convert to absolute path
        realpath(buff, absolute_path);

        stat(absolute_path, &stat_info);
		
        if(!S_ISREG(stat_info.st_mode)){
            
            scan_directory(absolute_path, h, word_length, is_deletion);
        }
        else {

            scan_file(absolute_path, h, word_length, is_deletion);
        }
  
    }
}


void scan_directory(char dirname[MAXPATHLEN], HASHTABLE *h, int word_length, bool is_deletion){
    DIR             *dirp;
    struct dirent   *dp;

//  ENSURE THAT WE CAN OPEN (read-only) THE REQUIRED DIRECTORY
    dirp       = opendir(dirname);
    if(dirp == NULL) {
        perror( dirname );
        exit(EXIT_FAILURE);
    }

//  READ FROM THE REQUIRED DIRECTORY, UNTIL WE REACH ITS END
    while((dp = readdir(dirp)) != NULL) {  
        struct stat     stat_info;
        char            pathname[MAXPATHLEN];

		
		sprintf(pathname, "%s/%s", dirname, dp->d_name);
        

        stat(pathname, &stat_info);
		if(!strcmp(".", dp->d_name) || !strcmp("..", dp->d_name)){
             continue;
        }
		else{
			if(!S_ISREG(stat_info.st_mode)){
				
				scan_directory(pathname, h, word_length, is_deletion);
			}
			else {

				scan_file(pathname, h, word_length, is_deletion);
            }
				
		}
    }
    closedir(dirp);
}

void scan_file(char *pathname, HASHTABLE *h, int word_length, bool is_deletion){
    //  ATTEMPT TO OPEN THE FILE FOR READ-ONLY ACCESS
    int fd    = open(pathname, O_RDONLY);

//  CHECK TO SEE IF FILE COULD BE OPENED
    if(fd == -1) {
        printf("scan_file: cannot open '%s'\n", pathname);
        exit(EXIT_FAILURE);
    }

    //store the filename and it's reference key into struct
    files = realloc(files, (nfiles + 1) * sizeof(files[0]));
    CHECK_ALLOC(files); 

    files[nfiles].pathname = strdup(pathname);
    CHECK_ALLOC(files[nfiles].pathname); 

    files[nfiles].RK = nfiles;
    // printf("path name is %s\n", files[nfiles].pathname);
    // printf("reference key = %d\n", files[nfiles].RK);

//  DEFINE A CHARACTER ARRAY TO HOLD THE FILE'S CONTENTS
    unsigned char   buffer[10000];
    size_t got;
    int file_size = 0;

    
//  PERFORM MULTIPLE READs OF FILE UNTIL END-OF-FILE REACHED  
    while((got = read(fd, buffer, sizeof buffer)) > 0) {
        file_size += got;
    }


//  INDICATE THAT THE PROCESS WILL NO LONGER ACCESS FILE
    close(fd);


    char buff[500];
    int j;
    int ndir = 0;

    for(int i=0; i < file_size; i++){

        while(!isalnum(buffer[i]) && i < file_size){i++;}

        //memset(buff, 0, sizeof buff); //Reset buff array
        j = 0;
        while(isalpha(buffer[i]) && i < file_size){
            buff[j] = buffer[i];
            i++;
            j++;
        }
        buff[j] = '\0';

        if(!is_deletion){
            if(j >= word_length){
                //printf("%s\n", buff);
                hashtable_add(h, buff, pathname);
            }
        }else{
            hashtable_delete(h, buff, pathname);
        }
        
        ndir++;
    }
    ++nfiles;//increment for next file
}