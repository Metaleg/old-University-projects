#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>

#define SIZE 3
#define THREADS 5

int **allocate();
void create_matrix(int **mas1, int **mas2);
void multiply_matrix(int **mas1, int **mas2, int **result);
void out(int **mas);
void print_to_file(char *name, int **mas1, int **mas2, int **result);
void* work(void *arg);

int main() {
    srand((unsigned int)time(NULL));

    size_t num[THREADS];
    pthread_t threads[THREADS];
    for (size_t i = 0; i < THREADS; ++i){
        num[i] = i;
        pthread_create(&threads[i], NULL, work, &num[i]);
    }

    for (size_t i = 0; i < THREADS; ++i)
        pthread_join(threads[i], NULL);

    return 0;
}


int **allocate(){
    int **mas = (int**)malloc(SIZE * sizeof(int));
    for (size_t i = 0; i < SIZE; ++i)
        mas[i] = (int*)malloc(SIZE * sizeof(int));

    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
            mas[i][j] = 0;
    return mas;
}

void create_matrix(int **mas1, int **mas2){
    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j){
            mas1[i][j] = -9 + rand() % 19;
            mas2[i][j] = -9 + rand() % 19;
        }
}

void multiply_matrix(int **mas1, int **mas2, int **result){
    for (size_t i = 0; i < SIZE; ++i)
        for (size_t j = 0; j < SIZE; ++j)
            for (size_t k = 0; k < SIZE; ++k)
                result[i][j] += mas1[i][k] * mas2[k][j];
}

void out(int **mas){
    for (size_t i = 0; i < SIZE; ++i){
        for (size_t j = 0; j < SIZE; ++j)
            printf("%4d ", mas[i][j]);
        printf("\n");
    }
    printf("\n");
}

void print_to_file(char *name, int **mas1, int **mas2, int **result){
    FILE *fp;
    fp = fopen(name, "w");
    if (fp == NULL) exit(1);

    fprintf(fp, "\nmas1 =\n");
    for (size_t i = 0; i < SIZE; ++i){
        for (size_t j = 0; j < SIZE; ++j)
            fprintf(fp, "%4d ", mas1[i][j]);
        fprintf(fp, "\n");
    }
    fprintf(fp, "\nmas2 =\n");
    for (size_t i = 0; i < SIZE; ++i){
        for (size_t j = 0; j < SIZE; ++j)
            fprintf(fp, "%4d ", mas2[i][j]);
        fprintf(fp, "\n");
    }
    fprintf(fp, "\nresult =\n");
    for (size_t i = 0; i < SIZE; ++i){
        for (size_t j = 0; j < SIZE; ++j)
            fprintf(fp, "%4d ", result[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void* work(void *arg){
    char name[5];
    name[1] = 0;
    name[0] = *(size_t*)arg + '0';
    strcat(name, ".txt");

    int **mas1 = allocate();
    int **mas2 = allocate();
    int **result = allocate();

    create_matrix(mas1, mas2);
    multiply_matrix(mas1, mas2, result);

    out(result);

    print_to_file(name, mas1, mas2, result);

    free(mas1);
    free(mas2);
    free(result);
}