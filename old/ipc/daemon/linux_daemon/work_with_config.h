//
// Created by metalleg on 13.01.19.
//

#ifndef LINUX_DAEMON_WORK_WITH_CONFIG_H
#define LINUX_DAEMON_WORK_WITH_CONFIG_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PATH_MAX_SIZE 100

struct app_data{
    int port;
    char path[PATH_MAX_SIZE];
    int size;
};

int load_config(char *filename, struct app_data *data);
int count_strings(char *filename);

#endif //LINUX_DAEMON_WORK_WITH_CONFIG_H
