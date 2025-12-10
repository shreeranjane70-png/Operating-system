#include <stdio.h>
#include <windows.h>

#define PIPE_NAME "\\\\.\\pipe\\MyPipe"

int main() {
    HANDLE hPipe;
    char buffer[1024];
    DWORD dwWritten, dwRead;

    // Create a named pipe
    hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024,
        1024,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to create pipe.\n");
        return 1;
    }

    printf("Waiting for client to connect...\n");
    ConnectNamedPipe(hPipe, NULL);
    printf("Client connected.\n");

    // Write message to the pipe
    printf("Enter message to send: ");
    fgets(buffer, sizeof(buffer), stdin);
    WriteFile(hPipe, buffer, (DWORD)strlen(buffer) + 1, &dwWritten, NULL);
    printf("Message sent: %s\n", buffer);

    // Read message from the pipe
    ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL);
    printf("Message received: %s\n", buffer);

    CloseHandle(hPipe);
    return 0;
}

