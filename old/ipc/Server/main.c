#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#define SIZE 5
void reset_the_columns(int a[SIZE][SIZE]){
    int even = 0;
    int odd = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j)
            (a[j][i] % 2 == 0) ? ++even : ++odd;
        if (even > odd)
            for (int j = 0; j < SIZE; ++j)
                a[j][i] = 0;
        even = 0;
        odd = 0;
    }
}

int main(){
    int array[SIZE][SIZE];
    int sock, listener;
    struct sockaddr_in addr;
    int bytes_read;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0){
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind");
        exit(2);
    }
    listen(listener, 1);
    while(1){
        sock = accept(listener, NULL, NULL);
        if(sock < 0){
            perror("accept");
            exit(3);
        }

        while(1){
            bytes_read = recv(sock, array, sizeof(array), 0);
            reset_the_columns(array);
            if(bytes_read <= 0) break;
            send(sock, array, bytes_read, 0);
        }
        close(sock);
    }
    return 0;
}