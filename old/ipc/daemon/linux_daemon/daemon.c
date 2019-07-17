#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <syslog.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include "work_with_config.c"


int linux_daemon(int strings, struct app_data *data);
void *receive_data(void *arg);


void *receive_data(void *arg) {
    struct app_data data = *(struct app_data*) arg;
//    printf("%d %s %d\n", data.port, data.path, data.size);
    int sock, listener;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((uint16_t) (data.port));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(2);
    }
    listen(listener, 1);
    while (1) {
        sock = accept(listener, NULL, NULL);
        if (sock < 0) {
            perror("accept");
            exit(3);
        }

        while (1) {
            char input_data[data.size];
            bzero(input_data, (size_t) data.size);
            size_t bytes_read = (size_t) recv(sock, input_data, sizeof(input_data), 0);
            if (bytes_read <= 0)
                break;

//            char c = ' ';
//            char out_data[data.size + strlen(data.path)];
//            bzero(out_data, strlen(out_data));
//            strcat(out_data, data.path);
//            strcat(out_data, &c);
//            strcat(out_data, input_data);

            pid_t pid = fork();
            if (pid == 0){
                printf("%s\n", input_data);
//                system(out_data);
                execl(data.path, data.path, input_data, NULL);
                exit(pid);
            }
        }
        close(sock);
    }
}

int linux_daemon(int strings, struct app_data *data){
    pthread_t thread[strings];
    for (int i = 0; i < strings; ++i)
        pthread_create(&thread[i], NULL, receive_data, &data[i]);
    for (int i = 0; i < strings; ++i)
        pthread_join(thread[i], NULL);
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage ./daemon -d for daemon or ./daemon -i for interactive\n");
        exit(1);
    }

    char *filename = "/run/media/metalleg/Local disk/Documents/CLionProjects/linux_daemon/config.txt";
    int strings = count_strings(filename);
    struct app_data data[strings];

    if ((load_config(filename, data)) == -1)
        perror("Can not load config");



    if (strcmp(argv[1], "-i") == 0)
        linux_daemon(strings, data);

    else if (strcmp(argv[1], "-d") == 0) {
        pid_t pid = fork(), sid = 0;
        if (pid < 0) {
            printf("Start Daemon Error: %s\n", strerror(errno));
            return -1;

        } else if (pid != 0)
            exit(0);

        umask(0);
        sid = setsid();
        if (sid < 0)
            exit(EXIT_FAILURE);

        if ((chdir("/")) < 0)
            exit(EXIT_FAILURE);

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        linux_daemon(strings, data);
    } else {
        printf("Usage ./daemon -d for daemon or ./daemon -i for interactive\n");
        exit(1);
    }
    return 0;
}