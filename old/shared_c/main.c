#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
#define PATH_MAX_SIZE 100

struct app_data{
    int port;
    char path[PATH_MAX_SIZE];
    int size;
};

int load_config(char *filename, struct app_data *data);
int count_strings(char *filename);
*/

int main(int argc, char *argv[]) {
    char str[] = "/home/metalleg/app1 Hello";
    system(str);
//        execl("/run/media/metalleg/Local disk/Documents/CLionProjects/rts2/a.out", "", "-pthread", NULL);

/*    char *filename = "config.txt";
    int strings = count_strings(filename);
    struct app_data data[strings];

    load_config(filename, data);
    for (int i = 0; i < strings; ++i)
        printf("%d %s %d\n", data->port, data->path, data->size);*/
    return 0;
}

/*
int count_strings(char *filename){
    FILE *config;
    if ((config = fopen(filename, "r")) == NULL){
        perror("Can not open the file");
        return -1;
    }
    int count = 1;
    while (!feof(config))
        if (fgetc(config) == '\n')
            ++count;
    fclose(config);
    return count;
}

int load_config(char *filename, struct app_data *data){
    FILE *config;
    if ((config = fopen(filename, "r")) == NULL){
        perror("Can not open the file");
        return -1;
    }
    int strings = count_strings(filename);
    char str[strings][PATH_MAX_SIZE];

    for (int i = 0; i < strings; ++i) {
        fgets(str[i], PATH_MAX_SIZE, config);
        printf("%s", str[i]);
    }

    printf("\n\n");

    for (int i = 0; i < strings; ++i) {
        bzero(data[i].path, PATH_MAX_SIZE);
        data[i].size = 0;
        data[i].port = 0;

        int flag = 0;
        char temp[5];
        int k = 0;
        for (int j = 0; j < PATH_MAX_SIZE; ++j) {
            if ((str[i][j] == 44 && str[i][j + 1] == 32) || str[i][j] == '\n' || (str[i][j] == !feof(config))){
                if (flag == 0)
                    data[i].port = atoi(temp);
                else if (flag == 2){
                    data[i].size = atoi(temp);
                }
                ++flag;
                j += 2;
                k = j;
                bzero(temp, 5);
            }

            if (flag == 0 || flag == 2)
                temp[j - k] = str[i][j];
            else if (flag == 1)
                data[i].path[j - k] = str[i][j];

        }
    }
    fclose(config);
}

*/
