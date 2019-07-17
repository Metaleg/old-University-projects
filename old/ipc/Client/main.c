#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <time.h>
#define SIZE 5

void print(int a[SIZE][SIZE]){
    printf("\n");
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    printf("\n");
}

void create_array(int a[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            a[i][j] = 0 + rand() % 9;
}

int main(){
    srand(time(NULL));
    int init_array[SIZE][SIZE];
    int proc_array[SIZE][SIZE];
    int sock;
    struct sockaddr_in addr;
    create_array(init_array);
    print(init_array);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("connect");
        exit(2);
    }
    send(sock, init_array, sizeof(init_array), 0);
    close(sock);
    return 0;
}