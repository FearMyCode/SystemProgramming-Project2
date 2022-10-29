#include "hashtable.h"


//  FUNCTION hash_string() ACCEPTS A STRING PARAMETER,
//  AND RETURNS AN UNSIGNED 32-BIT INTEGER AS ITS RESULT
//
//  see:  https://en.cppreference.com/w/c/types/integer

uint32_t hash_string(char *string)
{
    uint32_t hash = 0;

    while(*string != '\0') {
        hash = hash*33 + *string;
        ++string;
    }
    return hash;
}

//  ALLOCATE AND INITIALISE SPACE FOR A NEW HASHTABLE (AN ARRAY OF LISTS)
HASHTABLE *hashtable_new(void)
{
    HASHTABLE   *new = calloc(HASHTABLE_SIZE, sizeof(LIST *));

    CHECK_ALLOC(new);
    return new;
}

//  ADD A NEW STRING TO A GIVEN HASHTABLE
void hashtable_add(HASHTABLE *hashtable, char *string, char *path)
{
    uint32_t h   = hash_string(string) % HASHTABLE_SIZE;    // choose list

    hashtable[h] = list_add(hashtable[h], string, path);
    // printf("%s --> %d\n", path, h);
}

// DELETE PATHS
void hashtable_delete( HASHTABLE *hashtable, char *string, char *path){

    // for(int h = 0; h < HASHTABLE_SIZE; h++){
    //     list_delete(hashtable[h], path);
    // }

    //printf("the file need to be deleted: %s\n", path);
    uint32_t h   = hash_string(string) % HASHTABLE_SIZE; 

    list_delete(hashtable[h], string, path);
}

//  DETERMINE IF A REQUIRED STRING ALREADY EXISTS IN A GIVEN HASHTABLE
bool hashtable_find(HASHTABLE *hashtable, char *string)
{
    uint32_t h	= hash_string(string) % HASHTABLE_SIZE;     // choose list

    return list_find(hashtable[h], string);
}

void hashtable_export2csv(HASHTABLE *hashtable, char *filename){
    FILE *fp;
    LIST *list;

    fp = fopen(filename, "w+");


    for(int h = 0; h < HASHTABLE_SIZE; h++){
        list = hashtable[h];
        while(list != NULL) {
            fprintf(fp, "%s", list->string);
                for(int p = 0; p <= list->npath; p++){
                    fprintf(fp, ",%s", list->pathname[p]);
                }
                if(list->next != NULL) {
                    fprintf(fp, "\n");
                }
            list	= list->next;
            fprintf(fp, "\n");
        }
    }
    fclose(fp);

    switch( fork() ){
        case -1:
            printf("fork() failed\n");
            break;

        case 0: //Child
            execl(GZIP_PATH, GZIP_PATH, "-f", filename, (char*) NULL);
            exit(EXIT_SUCCESS);
        
        default: //Parent
            break;
            
    }
}

void hashtable_importfromcsv(HASHTABLE *hashtable, const char *filename){
    
    char *word, *path;

    char absolute_path[MAXPATHLEN];
    realpath(filename, absolute_path);
    //printf("trove file is %s\n", absolute_path);

    char zpath[MAXPATHLEN];
    sprintf(zpath, "%s.gz", filename);

    int status;
    switch( fork() ){
        case -1:
            printf("fork() failed\n");
            break;

        case 0: //Child
            execl(GZIP_PATH, GZIP_PATH, "-d", zpath, (char*) NULL);
            exit(EXIT_SUCCESS);
        
        default: //Parent
            
            wait(&status);
            break;
            
    }

    int fd = open(filename, O_RDONLY);
    if(fd == -1) {
        printf("hashtable_importfromcsv: cannot open '%s'\n", filename);
        exit(EXIT_FAILURE);
    }


    char   line[500000];
    size_t got;
    int file_size = 0;//in bytes
    
    while((got = read(fd, line, sizeof line)) > 0) {
        // printf("got is %ld\n", got);
        file_size += got;
    }
    close(fd);

    // printf("file_size is %d\n", file_size);
    char buff[500];
    int i, j;

    for(i = 0; i < file_size; i++){
        while(line[i] == '\n' || line[i] == '\r'){i++;}
        if(i > file_size){break;}
        
        // Find word
        //memset(buff, 0, sizeof buff); //Reset buff array
        j = 0;
        while(line[i] != ',' && i < file_size){

            buff[j] = line[i];
            i++;
            j++;
    
        }
        buff[j] = '\0'; //make it to a string
        word = strdup(buff);
        //printf("WORD: %s\n", word);

        // Find paths
        //memset(buff, 0, sizeof buff); //Reset buff array
        j = 0;
        i++;
        
        while(line[i] != '\r' && line[i] != '\n' && i < file_size){
            
            if(line[i] == ','){// if there is more than 1 path for the word
                buff[j] = '\0';
                path = strdup(buff);
                // printf("testing\n");
                // printf("PATH: %s\n", line);
                // printf("PATH: %s\n", path);
                
                hashtable_add(hashtable, word, path);     
                
                //memset(buff, 0, sizeof buff); //Reset buff array
                j = 0;
                i++;
                
                continue;
            }
            buff[j] = line[i];
            i++;
            j++;
        }
        buff[j] = '\0';
        path = strdup(buff);
        //printf("PATH: %s\n", path);
        hashtable_add(hashtable, word, path);
    }

    switch( fork() ){
        case -1:
            printf("fork() failed\n");
            break;

        case 0: //Child
            execl(GZIP_PATH, GZIP_PATH, "-f", filename, (char*) NULL);
            exit(EXIT_SUCCESS);
        
        default: //Parent
            wait(&status);
            break;
            
    }

    // for(int i = 0; i < HASHTABLE_SIZE; i++){
    //     list_print(hashtable[i]);
    // }
}
