#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 5
#define SAMPLE "THE_HERETICS_MUST_DIE._FOR_THE_EMPEROR!"

int main() {

    int fd_shm;
    if ((fd_shm = shm_open (SHARED_MEMORY_OBJECT_NAME, O_RDWR | O_CREAT, 0777)) == -1) {
        perror ("error create shm");
        return 1;
    }

    if (ftruncate(fd_shm, SHARED_MEMORY_OBJECT_SIZE + 1) == -1) {
        perror("ftruncate");
        return 1;
    }

    char *addr;
    addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE + 1, PROT_WRITE|PROT_READ, MAP_SHARED, fd_shm, 0);
    if (addr == (char*)-1) {
        perror("mmap");
        return 1;
    }

    memcpy(addr, SAMPLE, SHARED_MEMORY_OBJECT_SIZE);

    while(true){
        if (strcmp(addr, SAMPLE)){
            printf("%s\n", addr);
            memcpy(addr, SAMPLE, SHARED_MEMORY_OBJECT_SIZE);
            printf("%s\n", addr);
        }
        sleep(1);
    }

    return 0;
}