#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100

char* encrypt(char input[], int step);
char* decrypt(char input[], int step);

int main() {
    pid_t pid1 = 0, pid2 = 0;
    int st;
    int step = 0;
    int fd[2];
    char message[SIZE];

    char buf[SIZE];
    char *coded_message;
    char *decoded_message;

    pipe(fd);

    printf("Enter a step to encrypt by cesar method: ");
    scanf("%d", &step);
    getchar();
    printf("Enter a message\n");
    fgets(message, SIZE, stdin);
    fflush(stdin);

    write(fd[1], &message, strlen(message));

    pid1 = fork();
    if (pid1 == 0){
        read(fd[0], &buf, SIZE);
        coded_message = encrypt(buf, step);
        printf("%s\n", coded_message);
        write(fd[1], coded_message, strlen(coded_message));
        close(fd[1]);
        exit(pid1);
    }
    wait(&st);

    pid2 = fork();
    if (pid2 == 0){r

        read(fd[0], &buf, SIZE);
        decoded_message = decrypt(buf, step);
        printf("%s\n", decoded_message);
        write(fd[1], decoded_message, strlen(decoded_message));
        exit(pid2);
    }
    wait(&st);

    read(fd[0], &buf, SIZE);
    printf("%s\n", buf);

    if(!strcmp(message, buf))
        printf("\nSuccessful!\n");
    else
        printf("\nError!\n");

    return 0;
}

char* encrypt(char input[], int step) {
    for (int i = 0; i < strlen(input); i++)
        input[i] += (step + 26)%26;
    return input;
}

char* decrypt(char input[], int step) {
    for (int i = 0; i < strlen(input); i++)
        input[i] -= (step + 26)%26;
    return input;
}