#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char input[10];
    printf("Enter process number: ");
    int processNo = atoi(fgets(input, 10, stdin));
    printf("Sending signal SIGINT to process %d.\n", processNo);
    kill(processNo, SIGINT);
    return EXIT_SUCCESS;
}
