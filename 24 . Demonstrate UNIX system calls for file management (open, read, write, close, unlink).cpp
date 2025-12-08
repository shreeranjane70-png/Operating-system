// file_syscalls_demo.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(){
    const char *fname = "demo.txt";
    int fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(fd < 0){ perror("open"); return 1; }

    const char *text = "Hello from syscalls\nLine2\n";
    ssize_t w = write(fd, text, strlen(text));
    if(w < 0){ perror("write"); close(fd); return 1; }
    close(fd);
    printf("Wrote %zd bytes to %s\n", w, fname);

    fd = open(fname, O_RDONLY);
    if(fd < 0){ perror("open read"); return 1; }
    char buf[100];
    ssize_t r = read(fd, buf, sizeof(buf)-1);
    if(r < 0){ perror("read"); close(fd); return 1; }
    buf[r]=0;
    printf("Read %zd bytes:\n%s", r, buf);
    close(fd);

    if(unlink(fname)==0) printf("%s removed\n", fname);
    else perror("unlink");

    return 0;
}
