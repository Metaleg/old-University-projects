//
// Created by metalleg on 13.01.19.
//

#include "work_with_config.h"

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
                else if (flag == 2)
                    data[i].size = atoi(temp);

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