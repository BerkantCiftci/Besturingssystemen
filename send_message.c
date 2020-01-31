/*
 * Berkant Ciftci
 * 0979368
 * TI1D
 * Opdracht Signal
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MESS_LEN 100

int main()
{
    struct mesg_buffer
    {
        long mesg_type;
        char mesg_text[MESS_LEN];
    } message;
    message.mesg_type = 1;
    key_t key = ftok("ipc", 1);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    while (1)
    {
        printf("Type message: ");
        fgets(message.mesg_text, MESS_LEN, stdin);
        msgsnd(msgid, &message, MESS_LEN, 0);
        printf("Data sent is: %s\n", message.mesg_text);
    }
    return 0;
}