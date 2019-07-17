#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <zconf.h>

#define THINKERS_NUM 10
#define MAX_SATIETY 5
#define HUNGER 2

enum thinker_state{think, hunger, look, eat};
struct thinker{
    int satiety;
    enum thinker_state state;
    int number;
};

pthread_mutex_t mutex[THINKERS_NUM];
struct thinker thinkers[THINKERS_NUM];

long delay(int min, int max){
    return ((useconds_t)(1000*(min + rand() % (max - min + 1))));
}

void talk(enum thinker_state state, const int *num){
    switch (state){
        case think:
            printf("I am %d thinking thinker, my satiety is %d (︶︹︺)\n", *num, thinkers[*num].satiety);
            break;
        case hunger:
            printf("I am %d hungry thinker, my satiety is %d (￣﹃￣)\n", *num, thinkers[*num].satiety);
            break;
        case look:
            printf("I am %d looking thinker, my satiety is %d (↼_↼) (⇀_⇀)\n", *num, thinkers[*num].satiety);
            break;
        case eat:
            printf("I am %d eating thinker, my satiety is %d ( ˘▽˘)っ♨\n", *num, thinkers[*num].satiety);
            break;
    }
}

void* process(void *num){
    int my = *(int*) num;
    int left = (my == 0) ? (THINKERS_NUM - 1) : (my - 1);
    int right = (my == THINKERS_NUM - 1) ? 0 : (my + 1);

    thinkers[my].state = hunger;
    talk(thinkers[my].state, &my);
        while (thinkers[my].satiety < MAX_SATIETY){
        bool ate = false;
        pthread_mutex_lock(&mutex[my]);
        if (thinkers[left].state == look || thinkers[left].state == eat ||
                ((thinkers[my].satiety - thinkers[left].satiety) > HUNGER)){
            pthread_mutex_unlock(&mutex[my]);
            usleep((useconds_t) delay(50, 150));
        } else{
            int free = pthread_mutex_trylock(&mutex[right]);
                if(free != 0){
                    pthread_mutex_unlock(&mutex[my]);
                    usleep((useconds_t) delay(50, 150));
                } else{
                    thinkers[my].state = look;
                    talk(thinkers[my].state, &my);
                    pthread_mutex_unlock(&mutex[my]);
                    if(thinkers[right].state == eat || thinkers[right].state == look ||
                            (thinkers[my].satiety - thinkers[right].satiety) > HUNGER){
                        thinkers[my].state = hunger;
                        talk(thinkers[my].state, &my);
                        pthread_mutex_unlock(&mutex[right]);
                        usleep((useconds_t) delay(50, 150));
                    } else{
                        thinkers[my].state = eat;
                        ++thinkers[my].satiety;
                        talk(thinkers[my].state, &my);
                        ate = true;
                        pthread_mutex_unlock(&mutex[right]);
                        usleep((useconds_t) delay(100, 200));
                    }
                }
        }
        if(ate){
            thinkers[my].state = think;
            talk(thinkers[my].state, &my);
            usleep((useconds_t) delay(100, 200));
            if (thinkers[my].satiety < MAX_SATIETY){
                thinkers[my].state = hunger;
                talk(thinkers[my].state, &my);
            }
        }
    }

    printf("\nI am %d thinker, and I`m fed up! (っ˘ڡ˘ς)\n\n", my);
    return 0;
}

int main () {
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < THINKERS_NUM; ++i)
        pthread_mutex_init(&mutex[i], NULL);

    pthread_t thread[THINKERS_NUM];
    for (size_t i = 0; i < THINKERS_NUM; ++i) {
        thinkers[i].satiety = 0;
        thinkers[i].state = 0;
        thinkers[i].number = (int) i;
        pthread_create(&thread[i], NULL, (void *(*)(void *)) process, &thinkers[i].number);
    }

    for (size_t i = 0; i < THINKERS_NUM; ++i)
        pthread_join(thread[i], NULL);
    for (size_t i = 0; i < THINKERS_NUM; ++i)
        pthread_mutex_destroy(&mutex[i]);

    printf("\nAll thinkers are full and satisfied! (╮°-°)╮┳━━┳ (╯°□°)╯ ┻━━┻\n");
    return 0;
}
















/*

#include <unistd.h>          //Provides API for POSIX(or UNIX) OS for system calls
#include <stdio.h>           //Standard I/O Routines
#include <stdlib.h>          //For exit() and rand()
#include <pthread.h>         //Threading APIs
#include <semaphore.h>       //Semaphore APIs
#define MAX_CHAIRS 10        //No. of chairs in waiting room
#define CUT_TIME 1           //Hair Cutting Time 1 second
#define NUM_BARB 2           //No. of barbers
#define MAX_CUST 30          //Maximum no. of customers for simulation

sem_t customers;                 //Semaphore
sem_t barbers;                   //Semaphore
sem_t mutex;                     //Semaphore for providing mutially exclusive access
int numberOfFreeSeats = MAX_CHAIRS;   //Counter for Vacant seats in waiting room
int seatPocket[MAX_CHAIRS];           //To exchange pid between customer and barber
int sitHereNext = 0;                  //Index for next legitimate seat
int serveMeNext = 0;                  //Index to choose a candidate for cutting hair
int count = 0;                 //Counter of No. of customers
void barberThread(void *tmp);         //Thread Function
void customerThread(void *tmp);       //Thread Function
void wait();                          //Randomized delay function



int main()
{
    pthread_t barber[NUM_BARB], customer[MAX_CUST]; //Thread declaration
    int i, status = 0;
*/
/*Semaphore initialization*//*


    sem_init(&customers, 0, 0);
    sem_init(&barbers, 0, 0);
    sem_init(&mutex, 0, 1);
*/
/*Barber thread initialization*//*


    printf("!!Barber Shop Opens!!\n");
    for (i = 0; i<NUM_BARB; i++)                     //Creation of 2 Barber Threads
    {
        status = pthread_create(&barber[i], NULL, (void *)barberThread, (void*)&i);
        sleep(1);
        if (status != 0)
            perror("No Barber Present... Sorry!!\n");
    }
*/
/*Customer thread initialization*//*


    for (i = 0; i<MAX_CUST; i++)                     //Creation of Customer Threads
    {
        status = pthread_create(&customer[i], NULL, (void *)customerThread, (void*)&i);
        wait();                   //Create customers in random interval
        if (status != 0)
            perror("No Customers Yet!!!\n");
    }
    for (i = 0; i<MAX_CUST; i++)        //Waiting till all customers are dealt with
        pthread_join(customer[i], NULL);
    printf("!!Barber Shop Closes!!\n");
    exit(EXIT_SUCCESS);  //Exit abandoning infinite loop of barber thread
}

void customerThread(void *tmp)
*/
/*Customer Process*//*


{
    int mySeat, B;
    sem_wait(&mutex);  //Lock mutex to protect seat changes
    count++;           //Arrival of customer
    printf("Customer-%d[Id:%d] Entered Shop. ", count, pthread_self());
    if (numberOfFreeSeats > 0)
    {
        --numberOfFreeSeats;           //Sit on chairs on waiting room
        printf("Customer-%d Sits In Waiting Room.\n", count);
        sitHereNext = (++sitHereNext) % MAX_CHAIRS;  //Choose a vacant chair to sit
        mySeat = sitHereNext;
        seatPocket[mySeat] = count;
        sem_post(&mutex);                  //Release the seat change mutex
        sem_post(&barbers);                //Wake up one barber
        sem_wait(&customers);              //Join queue of sleeping customers
        sem_wait(&mutex);                  //Lock mutex to protect seat changes
        B = seatPocket[mySeat];    //Barber replaces customer PID with his own PID
        numberOfFreeSeats++;             //Stand Up and Go to Barber Room
        sem_post(&mutex);                        //Release the seat change mutex
*/
/*Customer is having hair cut by barber 'B'*//*


    }
    else
    {
        sem_post(&mutex);  //Release the mutex and customer leaves without haircut
        printf("Customer-%d Finds No Seat & Leaves.\n", count);
    }
    pthread_exit(0);
}

void barberThread(void *tmp)
*/
/*Barber Process*//*


{
    int index = *(int *)(tmp);
    int myNext, C;
    printf("Barber-%d[Id:%d] Joins Shop. ", index, pthread_self());
    while (1)
*/
/*Infinite loop*//*


    {
        printf("Barber-%d Gone To Sleep.\n", index);
        sem_wait(&barbers);          //Join queue of sleeping barbers
        sem_wait(&mutex);            //Lock mutex to protect seat changes
        serveMeNext = (++serveMeNext) % MAX_CHAIRS;  //Select next customer
        myNext = serveMeNext;
        C = seatPocket[myNext];                  //Get selected customer PID
        seatPocket[myNext] = pthread_self();     //Leave own PID for customer
        sem_post(&mutex);
        sem_post(&customers);         //Call selected customer
*/
/*Barber is cutting hair of customer 'C'*//*


        printf("Barber-%d Wakes Up & Is Cutting Hair Of Customer-%d.\n", index, C);
        sleep(CUT_TIME);
        printf("Barber-%d Finishes. ", index);
    }
}

void wait()
*/
/*Generates random number between 50000 to 250000*//*


{
    int x = rand() % (250000 - 50000 + 1) + 50000;
    srand(time(NULL));
    usleep(x);     //usleep halts execution in specified miliseconds
}
*/
