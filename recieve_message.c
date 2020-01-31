/*
 * Berkant Ciftci
 * 0979368
 * TI1D
 * Opdracht Signal
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#define MESS_LEN 100
int main()
{
    struct mesg_buffer
    {
        long mesg_type;
        char mesg_text[MESS_LEN];

    } message;
    key_t key = ftok("ipc", 1);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    while (1)
    {
        msgrcv(msgid, &message, MESS_LEN, 0, 0);
        printf("Data recieved is: %s\n", message.mesg_text);
        if (message.mesg_text[1] == "")
        {
            printf("No message in queue.");
        }
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
