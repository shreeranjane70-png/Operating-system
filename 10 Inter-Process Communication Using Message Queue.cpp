#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;
    message.msg_type = 1;

    printf("Enter a message: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    printf("\nMessage Sent!\n");
    return 0;
}
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("msgfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;

    msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);

    printf("\nReceived Message: %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL);  // delete queue
    return 0;
}
