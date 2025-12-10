#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int src, dest;
    char buffer[1024];
    ssize_t bytesRead;

    // Open the source file
    src = open("source.txt", O_RDONLY);
    if (src < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Open/create destination file
    dest = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening destination file");
        close(src);
        return 1;
    }

    // Copy contents
    while ((bytesRead = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytesRead);
    }

    // Close files
    close(src);
    close(dest);

    printf("File copied successfully.\n");
    return 0;
}

