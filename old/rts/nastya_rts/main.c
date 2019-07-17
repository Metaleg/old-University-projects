/*
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <zconf.h>


#define thread_num 10
#define max_meals 30

*/
/* первоначальный статус палочки для еды *//*

*/
/* 1 - имеется палочка для еды *//*

*/
/* 0 - палочка для еды не доступна *//*

int chopstick[thread_num]={1,1,1,1,1,1,1,1,1,1};

*/
/* блокировки мьютекса для каждой палочки для еды *//*

pthread_mutex_t m[thread_num];

*/
/* идентификатор философа *//*

int p[thread_num]={0,1,2,3,4,5,6,7,8,9};

*/
/* количество блюд, потребляемых каждым философом *//*

int numMeals[thread_num]={0,0,0,0,0,0,0,0,0,0};

*/
/* счетчик для количества съеденных блюд *//*

int mealCount = 0;


void *philosopher(void *); */
/* prototype of philosopher routine *//*



int main()
{
    pthread_t tid[thread_num];
    int i,j;

    srand( (long)time(NULL) );

    */
/* создать 10 потоков, представляющих 10 dinning philosopher *//*

    for (i = 0; i < thread_num; i++)
    {
        if(pthread_create( tid + i, 0, philosopher, p + i ) != 0)
        {
            perror("pthread_create() failure.");
            exit(1);
        }
    }

    */
/* Дождаться соединения 10 потоков *//*

    for (i = 0; i < thread_num; i++)
    {
        if(!pthread_join(tid[i], NULL )==0)
        {
            perror("thr_join() failure.");
            exit(1);
        }
    }

    printf("\n");
    for(i=0; i<thread_num; i++)
        printf("Philosopher %d ate %d meals.\n", i, numMeals[i]);

    printf("\nmain(): The philosophers have left. I am going to exit!\n\n");

    return (0);
}


void *philosopher(void  *arg)
{
    int  sub = *(int*)arg;

    while( mealCount < max_meals )
    {
        printf("philosopher %d: I am going to eat!\n", sub);

        */
/* заблокировать левую палочку для еды *//*

        pthread_mutex_lock( m + sub );

        if( chopstick[sub] == 1 )
        { */
/* левая доступна *//*

            printf("philosopher %d: left=%d\n",sub,chopstick[sub]);
            printf("Philosopher %d: I got the left one!\n", sub);

            chopstick[sub]=0; */
/* установить левую палочку для еды недоступной *//*


            pthread_mutex_unlock( m + sub ); */
/* разблокировать левую палочку *//*
             */
/* заблокировать правую палочку для еды *//*

            pthread_mutex_lock( m + ((sub+1)%thread_num) );

            if( chopstick[(sub+1)%thread_num]==1 )
            { */
/* правая доступна *//*

                printf("philosopher %d: right=%d\n", sub,
                       chopstick[(sub+1)%thread_num]);

                */
/* установить правую палочку для еды недоступно *//*

                chopstick[(sub+1)%thread_num]=0;

                */
/* разблокировать правую палочку *//*

                pthread_mutex_unlock( m + ( (sub+1) % thread_num) );

                printf("Philosopher %d: I got two chopsticks!\n", sub);
                printf("philosopher %d: I am eating!\n\n", sub);

                numMeals[sub]++;
                mealCount++;
                usleep(rand() % 3000000); */
/* время еды *//*


                */
/* заблокировать левую и правую палочки для еды *//*

                pthread_mutex_lock( m + sub );
                pthread_mutex_lock( m + ( (sub+1) % thread_num) );

                */
/* установите правую палочку для еды *//*

                chopstick[(sub+1)%thread_num]=1;

                chopstick[sub]=1;   */
/* установите левую палочку для еды *//*



                */
/* разблокировать левую и правую палочки для еды *//*

                pthread_mutex_unlock ( &m[sub]);
                pthread_mutex_unlock (&m[(sub+1)%thread_num]);

                usleep(rand() % 3000000); */
/* время установления питания *//*

            }
            else
            { */
/* правая недоступна *//*

                printf("philosopher %d: right=%d\n",
                       sub, chopstick[(sub+1)%thread_num]);
                printf("Philosopher %d: I cannot get the right one!\n\n", sub);

                */
/* разблокировать правую палочку *//*

                pthread_mutex_unlock( &m[(sub+1)%thread_num] );

                */
/* заблокировать левую палочку для еды *//*

                pthread_mutex_lock( &m[sub] );

                */
/* установите левую палочку для еды (положите левую) *//*
                chopstick[sub]=1;

                */
/* разблокировать левую палочку *//*

                pthread_mutex_unlock( &m[sub] );

                */
/* Подождите некоторое время и повторите попытку позже *//*

                usleep(rand() % 3000000);
            }
        }
        else
        { */
/* левая палочка недоступна *//*

            printf("philosopher %d: left=%d\n",sub,chopstick[sub]);
            printf("Philosopher %d: I cannot even get the left chopstick!\n\n",
                   sub);

            */
/* разблокировать левую палочку *//*

            pthread_mutex_unlock( &m[sub] );

            */
/* Подождите некоторое время и повторите попытку позже *//*


            usleep(rand() % 3000000);
        }

        sched_yield();  */
/* for LINUX you may also use pthread_yield(); *//*

    }
    printf("Philosopher %d has finished the dinner and is leaving!\n", sub);
    pthread_exit(0);
}*/




#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SHARED_MEMORY_OBJECT_NAME "my_shared_memory"
#define SHARED_MEMORY_OBJECT_SIZE 17

void reverse(char *s);
void itoa(int n, char *s);

int main() {
    int fd_shm;
    char *addr = NULL;

    if ((fd_shm = shm_open (SHARED_MEMORY_OBJECT_NAME, O_RDWR | O_CREAT | O_EXCL, 0777)) == -1) {
        if((fd_shm = shm_open (SHARED_MEMORY_OBJECT_NAME, O_RDWR, 0777)) == -1){
            perror("shm");
            return 1;
        }
        addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE + 1,PROT_WRITE|PROT_READ, MAP_SHARED, fd_shm, 0);
        if (addr == (char*)-1) {
            perror("mmap");
            return 1;
        }
        printf("%s\n", addr);

//        munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
//        close(fd_shm);
        shm_unlink(SHARED_MEMORY_OBJECT_NAME);
        return 0;
    }

    if (ftruncate(fd_shm, SHARED_MEMORY_OBJECT_SIZE + 1) == -1) {
        perror("ftruncate");
        return 1;
    }

    addr = mmap(0, SHARED_MEMORY_OBJECT_SIZE + 1, PROT_WRITE|PROT_READ, MAP_SHARED, fd_shm, 0);
    if (addr == (char*)-1) {
        perror("mmap");
        return 1;
    }

    char str[SHARED_MEMORY_OBJECT_SIZE] = "Hello! I am ";
    char pid[6];
    itoa(getpid(), pid);
    strcat(str, pid);

    memcpy(addr, str, SHARED_MEMORY_OBJECT_SIZE);
    sleep(1);
    printf("%s\n", addr);


//    munmap(addr, SHARED_MEMORY_OBJECT_SIZE);
//    close(fd_shm);
//    shm_unlink(SHARED_MEMORY_OBJECT_NAME);

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








