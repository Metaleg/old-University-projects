#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <pthread.h>
#include "time.h"

#include "/run/media/metalleg/Local disk/Documents/CLionProjects/linux_daemon/work_with_config.c"


void reverse(char *s);
void itoa(int n, char *s);
void *send_data(void *arg);


int main(){
    srand((unsigned int) time(NULL));
    char *filename = "/run/media/metalleg/Local disk/Documents/CLionProjects/linux_daemon/config.txt";
    int strings = count_strings(filename);
    struct app_data data[strings];

    if ((load_config(filename, data)) == -1)
        perror("Can not load config");

    pthread_t thread[strings];
    for (int i = 0; i < strings; ++i)
        pthread_create(&thread[i], NULL, send_data, &data[i]);
    for (int i = 0; i < strings; ++i)
        pthread_join(thread[i], NULL);
    return 0;
}

void reverse(char *s){
    char c;
    for (size_t i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char *s){
    int sign;
    if ((sign = n) < 0)
        n = -n;
    int i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void *send_data(void *arg){
    struct app_data data = *(struct app_data*) arg;
//    printf("%d %s %d\n", data.port, data.path, data.size);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t) (data.port));
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("connect");
        exit(2);
    }
    char haha[] = "Hello!_I_am_";
    char input_data[data.size];
    bzero(input_data, (size_t) data.size);
    strcpy(input_data, haha);
    char pid[6];
    itoa(getpid() + 0 + rand() % 1000, pid);
    strcat(input_data, pid);

    send(sock, input_data, sizeof(input_data), 0);
    printf("%s\n", input_data);
    close(sock);
}