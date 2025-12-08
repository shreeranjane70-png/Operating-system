// ls_sim.c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    const char *path = (argc>1) ? argv[1] : ".";
    DIR *d = opendir(path);
    if(!d){ perror("opendir"); return 1; }
    struct dirent *e;
    while((e = readdir(d))!=NULL){
        struct stat st;
        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", path, e->d_name);
        if(stat(full, &st)==0){
            char type = S_ISDIR(st.st_mode) ? 'd' : '-';
            printf("%c %10lld %s\n", type, (long long)st.st_size, e->d_name);
        } else {
            printf("? %10s %s\n", "?", e->d_name);
        }
    }
    closedir(d);
    return 0;
}
