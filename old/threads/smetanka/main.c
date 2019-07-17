#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 200

struct file{
    char buf[SIZE];
    char filename[SIZE];
};

void read_file(struct file f);
void purge(struct file f);
void emplace_to(struct file f);
void* stream1();
void* stream2();

int main() {
    int status = 0;
    pthread_t fucking_thread1 = 0;
    pthread_t fucking_thread2 = 0;

    status = pthread_create(&fucking_thread1, NULL, stream1, NULL);
    status = pthread_create(&fucking_thread2, NULL, stream2, NULL);

    if (status != 0)
        printf("main error: can't create thread, status = %d\n", status);
    status = pthread_join(fucking_thread1, NULL);
    if (status != 0)
        printf("main error: can't create thread, status = %d\n", status);
    status = pthread_join(fucking_thread2, NULL);

    return 0;
}

void read_file(struct file f){
    FILE *fp;
    fp = fopen(f.filename, "r");
    fgets(f.buf, sizeof(f.buf), fp);
    fclose(fp);


void purge(struct file f){
    remove(f.filename);
}

void emplace_to(struct file f){
    FILE *fp;
    fp = fopen(f.filename, "w");
    fprintf(fp, f.buf);
    fclose(fp);
}

void* stream1(){
    DIR *dir;
    struct dirent *ent;
    struct file f;

    if ((dir = opendir("/home/metalleg/CLionProjects/smetanka/list")) != NULL) {
        while ((ent = readdir(dir)) != NULL)
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..") && strlen(ent->d_name) < 10){
                    strcpy(f.filename, "/home/metalleg/CLionProjects/smetanka/list/");
                    strcat(f.filename, ent->d_name);

                    read_file(f);
                    //purge(f);

                    strcpy(f.filename, "/home/metalleg/CLionProjects/smetanka/a_catalog/");
                    strcat(f.filename, ent->d_name);
                    printf("move %s to /home/metalleg/CLionProjects/smetanka/a_catalog/\n", ent->d_name);

                    emplace_to(f);
                    sleep(1);

            }
        closedir(dir);
    }
    else {
        printf("Error! Directory not found!\n");
        return 0;
    }
}


void* stream2(){
    DIR *dir;
    struct dirent *ent;
    struct file f;

    if ((dir = opendir("/home/metalleg/CLionProjects/smetanka/list")) != NULL) {
        while ((ent = readdir(dir)) != NULL)
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..") && strlen(ent->d_name) >= 10){
                    strcpy(f.filename, "/home/metalleg/CLionProjects/smetanka/list/");
                    strcat(f.filename, ent->d_name);

                    read_file(f);
                    //purge(f);

                    strcpy(f.filename, "/home/metalleg/CLionProjects/smetanka/b_catalog/");
                    strcat(f.filename, ent->d_name);
                    printf("move %s to /home/metalleg/CLionProjects/smetanka/b_catalog/\n", ent->d_name);

                    emplace_to(f);
                    sleep(2);
            }
        closedir(dir);
    }
    else {
        printf("Error! Directory not found!\n");
        return 0;
    }
}
