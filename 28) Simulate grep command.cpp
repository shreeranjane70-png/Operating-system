// grep_sim.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 3){
        fprintf(stderr, "Usage: %s pattern filename\n", argv[0]);
        return 1;
    }
    char *pattern = argv[1];
    FILE *f = fopen(argv[2], "r");
    if(!f){ perror("fopen"); return 1; }
    char line[1024];
    int lineno = 0;
    while(fgets(line, sizeof(line), f)){
        lineno++;
        if(strstr(line, pattern)){
            printf("%s:%d:%s", argv[2], lineno, line);
        }
    }
    fclose(f);
    return 0;
}
