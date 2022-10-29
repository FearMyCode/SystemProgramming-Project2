//  CITS2002 Project 2 2022
//  Student1:   23745035   Klüver   Jonas Hoel   50
//  Student2:   23268041   Yip   Kang Chau   50

#include "directory.h"

int main(int argc, char *argv[])
{
    int promptn = 1, len = 4;
    char command[50], trfile[50], promptc[3];
    strcpy(trfile, "./tmp/trove");//default name should be /tmp/trove
    for(int i = 1; i < argc; i++){
        
        if(!strcmp(argv[i], "-f")){strcpy(trfile, argv[i+1]);}
        if(!strcmp(argv[i], "-l")){len = atoi(argv[i+1]);}
        if(!strcmp(argv[i], "-b") || !strcmp(argv[i], "-r") || !strcmp(argv[i], "-u")){
            //Prompt must be of type 2
            promptn = 2;
            strcpy(promptc, argv[i]);
        }
        
    } 
    strcpy(command, argv[argc-1]);//Last part is word or filelist
    if(!promptn){
        printf("EXIT STATUS: Wrong input\n");
        printf("Prompt 1: ./trove  [-f trovefile]  word\n");
        printf("Prompt 2: ./trove  [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist\n");
        exit(EXIT_FAILURE);
    }

    //printf("promptn:%d, len:%d, command:%s, trfile:%s, promptc:%s\n", promptn, len, command, trfile, promptc);

    HASHTABLE *hash_table = hashtable_new();

    //Prompt 1: ./trove  [-f trovefile]  word
    if(promptn == 1) {
        printf("    Search indexfile: %s\n", command);
        hashtable_importfromcsv(hash_table, trfile);
        if(hashtable_find(hash_table, command)){
            exit(EXIT_SUCCESS);
        }
        else{exit(EXIT_FAILURE);}
    }

    //Prompt 2: ./trove  [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist
    bool is_deletion;
    if(promptn == 2) {
        if(!strcmp(promptc, "-b")){
            printf("    Build new indexfile\n");
            is_deletion = false;
            build_hashtable(command, hash_table, len, is_deletion);
            hashtable_export2csv(hash_table, trfile);
            exit(EXIT_SUCCESS);       
        }
        else if(!strcmp(promptc, "-r")){
            printf("    Remove item from indexfile\n");
            hashtable_importfromcsv(hash_table, trfile);
            is_deletion = true;
            build_hashtable(command, hash_table, len, is_deletion);
            hashtable_export2csv(hash_table, trfile);
            exit(EXIT_SUCCESS);       
        }
        else if(!strcmp(promptc, "-u")){
            printf("    Update indexfile\n");
            hashtable_importfromcsv(hash_table, trfile);
            is_deletion = true;
            build_hashtable(command, hash_table, len, is_deletion);
            is_deletion = false;
            build_hashtable(command, hash_table, len, is_deletion);
            hashtable_export2csv(hash_table, trfile);
            exit(EXIT_SUCCESS);
        }
        else{
            printf("ERROR: Please provide correct option for command\n");
            printf("Prompt 1: ./trove  [-f trovefile]  word\n");
            printf("Prompt 2: ./trove  [-f trovefile]  [-b  |  -r  |  -u]  [-l length]  filelist\n");
            exit(EXIT_FAILURE);
        }
    }
    
}