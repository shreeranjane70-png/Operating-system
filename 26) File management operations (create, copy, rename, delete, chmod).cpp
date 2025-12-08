// file_ops.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int copy_file(const char *src, const char *dst){
    int in = open(src, O_RDONLY);
    if(in<0){ perror("open src"); return -1; }
    int out = open(dst, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(out<0){ perror("open dst"); close(in); return -1; }

    char buf[4096];
    ssize_t r;
    while((r = read(in, buf, sizeof(buf)))>0){
        if(write(out, buf, r) != r){ perror("write dst"); close(in); close(out); return -1; }
    }
    close(in); close(out);
    return 0;
}

int main(){
    const char *a="a.txt", *b="b.txt";
    // create a.txt
    int fd = open(a, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(fd, "Sample content for file operations\n", 34);
    close(fd);
    printf("Created %s\n", a);

    // copy a.txt -> b.txt
    if(copy_file(a,b)==0) printf("Copied %s -> %s\n", a, b);

    // rename b.txt -> c.txt
    if(rename(b,"c.txt")==0) printf("Renamed %s -> c.txt\n", b);

    // change mode of c.txt
    if(chmod("c.txt", 0600)==0) printf("Changed permissions of c.txt to 0600\n");

    // delete a.txt & c.txt
    if(unlink(a)==0) printf("Deleted %s\n", a);
    if(unlink("c.txt")==0) printf("Deleted c.txt\n");

    return 0;
}
