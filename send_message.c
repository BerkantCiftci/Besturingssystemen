#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MESS_LEN 100

int main() {
    // structure for message queue
    struct mesg_buffer {
        long mesg_type;
        char mesg_text[MESS_LEN];
    } message;
    message.mesg_type = 1;
    
    // generate a unique key using user-selectable name and id
    key_t key = ftok("ipc", 1);

    // create a message queue if one with this key does not yet exist
    // 0666: give read/write permissions to all users
    int msgid = msgget(key, 0666 | IPC_CREAT);
    
    while(1) {
    	printf("Type message: ");
    	fgets(message.mesg_text, MESS_LEN, stdin);

    	// send message
    	msgsnd(msgid, &message, MESS_LEN, 0);
     	printf("Data sent is: %s\n", message.mesg_text);
    }	
    return 0;
}
