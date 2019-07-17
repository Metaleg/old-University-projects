#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
///#include <jmorecfg.h>

//gcc -pthread main.c
//./a.out

/*
Вариант     Порядок     Y   P   R   F     A   B   J   S   L


2       9.2.6.1.3.5     6   7   1   *    13   40  7    8



1)Создать Y потоков с одинаковым набором атрибутов и приоритетом P (можно использовать цикл, в котором будет производиться вызов требуемой функции).
2)Создать R потоков с приоритетом F, отличных по подаваемой функции от потоков, создаваемых в пункте 1.
3)Каждый поток, созданный в пункте 1, меняет себе приоритет на A, затем выводит B раз свой номер и приоритет, и “засыпает” после каждых J раз.
Y потоков, созданных в пункте 1, создают потоки, аналогичные  по атрибутам и подаваемой функции, так, чтобы созданный поток далее не создавал свою копию (во входных параметрах передавать ему специальный флаг)  и в случае отсутствия последующих действий (после данного пункта не выполняется 3-ий) поток-создатель “умирает”.
5)Основной поток ожидает завершения выполнения потоков, созданных в пункте 2.

6)Основной поток изменяет себе приоритет на S.

8)Поток из пункта 2 выводит свой номер и приоритет L раз.
9)Создать поток, который будет ожидать завершение основного потока, и после этого выводить прощальную фразу.


*/

#define Y  6  // Число потоков 1 типа
#define P 7  // Приоритет потоков 1 типа
#define R 1  // Число потоков 2 типа
#define F  12  // Приоритет потоков 2 типа
#define A 13
#define B 40 //l/,/30
#define J 7
#define S 8

struct Flag
{
    int Num;
    int flag;
};

void* func_P_threed(void *arg){
    struct Flag int_arg = *(struct Flag*)arg;
    int int_arg1=int_arg.Num;
    printf("-P- Hi! I am P threed %d, - %ld!\n", int_arg1, pthread_self());

    int sched;
    struct sched_param param;

    pthread_getschedparam(pthread_self(), &sched, &param);
    param.sched_priority = A;
    pthread_setschedparam(pthread_self(), &sched, &param);

//цикл вывода  3

    for (int i = 0; i < B; ++i)
    { if (i % J!=0)
        {
            sleep(0.5);
        }
        printf("-P- I am %d, -nomer potoka %ld, my priority - %d!\n", int_arg1, pthread_self(), param.sched_priority);
    }



    printf("-P- I P threed %d, - %ld! Goodbye!\n", int_arg1, pthread_self());
    return 0;
}

void* func_F_threed(void *arg){
    int int_arg1 = *(int*)arg;
    printf("-F- Hi! I am F threed %d, - %ld!\n", int_arg1, pthread_self());


    printf("-F- I F threed %d, - %ld! Goodbye!\n", int_arg1, pthread_self());
    return 0;
}

void* func_end_threed(void *arg){
    pthread_t main_thread = (pthread_t)arg;
    printf("-X- Hi! I am exit threed! I wait %ld!\n", main_thread);

    pthread_join( main_thread , NULL);
    printf("-X- I tyred and want to eat;)\n");
    pthread_exit(0);
}

int main (){
    //Declarations - F
    pthread_t thread_F[R];
    pthread_attr_t attr_F;
    struct sched_param param_F;

    //Declarations - P
    pthread_t thread_P[Y];
    pthread_attr_t attr_P;
    struct sched_param param_P;

    //Declarations - X
    pthread_t thread_end;

    //Initialization - F
    pthread_attr_init(&attr_F);
    param_F.sched_priority = F;
    pthread_attr_setschedpolicy(&attr_F, SCHED_FIFO);
    pthread_attr_setschedparam(&attr_F, &param_F);
    pthread_attr_setinheritsched(&attr_F, PTHREAD_EXPLICIT_SCHED);

    //Initialization - P
    pthread_attr_init(&attr_P);
    param_P.sched_priority = P;
    pthread_attr_setschedpolicy(&attr_P, SCHED_FIFO);
    pthread_attr_setschedparam(&attr_P, &param_P);
    pthread_attr_setinheritsched(&attr_P, PTHREAD_EXPLICIT_SCHED);





//9
    pthread_create(&thread_end, NULL, func_end_threed, (void*)pthread_self());


//2
    int number_F[R];
    for(int i = 0; i < R; ++i) {
        number_F[i] = i + 1;
        pthread_create(&thread_F[i], &attr_F, func_F_threed, &number_F[i]);
    }

    // 6
    printf("I main, am - %ld, my priority - %d!\n", pthread_self(), getpriority(PRIO_PROCESS, 0));
    setpriority(PRIO_PROCESS, 0, S);
    printf("I main, am - %ld, my priority - %d!\n", pthread_self(), getpriority(PRIO_PROCESS, 0));

    // 1
    int number_P[Y];
    for(int i = 0; i < Y; ++i) {
        number_P[i] = i + 1;
        pthread_create(&thread_P[i], &attr_P, func_P_threed, &number_P[i]);
    }
    // 5
    for(int i = 0; i < R; ++i)
        pthread_join(thread_F[i], NULL);

    pthread_attr_destroy(&attr_F);
    pthread_attr_destroy(&attr_P);
    int g = 345;
    pthread_exit ((void *) &g);

}