

#include "list.h"

//  'CREATE' A NEW, EMPTY LIST - JUST A NULL POINTER
LIST *list_new(void)
{
    return NULL;
}

//  DETERMINE IF A REQUIRED ITEM (A STRING) IS STORED IN A GIVEN LIST
bool list_find(LIST *list, char *wanted)
{
    bool flag = false;
    while(list != NULL) {
        if(strcmp(list->string, wanted) == 0) {
            for(int i = 0; i <= list->npath; i++){
                printf("%s\n", list->pathname[i]);
            }
            flag = true;
        }
        list	= list->next;
    }
    return flag;
}

//0 = neither word or path exist; 1 = word exist, but not path; 2 = both word and path exist
int list_check_existence(LIST *list, char *wanted_word, char *wanted_path)
{
    while(list != NULL) {
        if(!strcmp(list->string, wanted_word)){
            for(int i = 0; i <= list->npath; i++){
                if(!strcmp(list->pathname[i], wanted_path)) {
                    return 2;
                }
            }
            return 1;
        }
        list	= list->next;
    }
    return 0;
}

//  ALLOCATE SPACE FOR A NEW LIST ITEM, TESTING THAT ALLOCATION SUCCEEDS
LIST *list_new_item(char *newstring, char *path)
{
    LIST *new       = calloc(1, sizeof(LIST) );
    CHECK_ALLOC(new);
    new->string     =  strdup(newstring);
    new->pathname[0]   =  strdup(path);
    new->npath = 0;
    CHECK_ALLOC(new->string);
    new->next       =  NULL;
    return new;
}

//  FIND AND UPDATE EXISTING LIST ITEM
bool list_update_item(LIST *list, char *newstring, char *path){

    
    while(list != NULL) {
        if(!strcmp(list->string, newstring)){
            list->npath = list->npath + 1;
            int i = list->npath;
            list->pathname[i] = strdup(path);
            return 1;
        }
        list	= list->next;
    }
    return 0;
}

//  ADD A NEW (STRING) ITEM TO AN EXISTING LIST
LIST *list_add(LIST *list, char *newstring, char *path)
{
    int c = list_check_existence(list, newstring, path);

    if(c == 2) {            // only add each item once
        return list;
    }
    else if(c == 1){
        list_update_item(list, newstring, path);
        return list;
    }
    else {                                      // add new item to head of list
        LIST *new   = list_new_item(newstring, path);
        new->next   = list;
        return new;
    }
}

//  DELETE AN ITEM FROM AN EXISTING LIST
void list_delete(  LIST *list, char *oldstring, char *path){
    LIST *head_list = list;//list = curr_list
    LIST *prev_list = list;

    bool head  = true;

    while(list != NULL) {
        if(strcmp(list->string, oldstring) == 0){
            for(int i = 0; i <= list->npath; i++){                        
                if(strcmp(list->pathname[i], path) == 0){
                    for(i = i; i < list->npath; i++){
                        list->pathname[i] = strdup(list->pathname[i+1]);
                    }
                    list->npath--;
                    break;
                }
            }
        }
        if(list->npath < 0){
            if(head){
                head_list = head_list->next;
            }
            else{
                prev_list->next = list->next;
            }
        }
        
        prev_list = list;
        list	= list->next;
        head = false; //We are no longer working with the head list
    }
    
}

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
void list_print(LIST *list)
{
    if(list != NULL) {
        while(list != NULL) {
	    printf("%s", list->string);
	    if(list->next != NULL) {
	        printf(" -> ");
            }
	    list	= list->next;
        }
	printf("\n");
    }
}
