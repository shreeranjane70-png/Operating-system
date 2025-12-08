// unix_calls_demo_fixed.c
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){
    const char *fname = "stat_demo.txt";
    int fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); return 1; }

    ssize_t w = write(fd, "0123456789\n", 11);
    if (w < 0) { perror("write"); close(fd); unlink(fname); return 1; }

    /* fcntl: get flags */
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) perror("fcntl");
    else printf("File flags: 0x%x\n", flags);

    /* lseek: move to offset 5 and write */
    off_t off = lseek(fd, 5, SEEK_SET);
    if (off == (off_t)-1) perror("lseek");
    else {
        ssize_t w2 = write(fd, "ABC", 3);
        if (w2 < 0) perror("write at offset");
        else printf("Wrote %zd bytes at offset %ld\n", w2, (long)off);
    }

    /* stat */
    struct stat st;
    if (stat(fname, &st) == 0) {
        printf("File %s size = %lld bytes\n", fname, (long long)st.st_size);
    } else perror("stat");

    close(fd);

    /* opendir & readdir on current directory */
    DIR *d = opendir(".");
    if (!d) { perror("opendir"); unlink(fname); return 1; }
    printf("Directory listing (name : type):\n");
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        const char *type_str;
        switch (entry->d_type) {
            case DT_REG: type_str = "file"; break;
            case DT_DIR: type_str = "dir"; break;
            case DT_LNK: type_str = "link"; break;
            case DT_FIFO: type_str = "fifo"; break;
            case DT_SOCK: type_str = "sock"; break;
            case DT_CHR: type_str = "chr"; break;
            case DT_BLK: type_str = "blk"; break;
            case DT_UNKNOWN: type_str = "unknown"; break;
            default: type_str = "other"; break;
        }
        printf("%s : %s (%d)\n", entry->d_name, type_str, (int)entry->d_type);
    }
    closedir(d);

    /* cleanup */
    if (unlink(fname) != 0) perror("unlink");
    return 0;
}
