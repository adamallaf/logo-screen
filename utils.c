#include "utils.h"


char *get_path(const char *path){
    char *npath = NULL;
    int i = 0, j = 0, last_sep_idx = 0;
    for(i = 0; path[i] != '\0'; i++){
        if(path[i] == '/')
            last_sep_idx = i;
    }
    npath = (char *)malloc(last_sep_idx + 1);
    for(j = 0; j <= last_sep_idx; j++)
        npath[j] = path[j];
    npath[j] = '\0';
    return npath;
}


char* concat(const char *s1, const char *s2){
    char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
