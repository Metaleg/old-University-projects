//
// Created by metalleg on 10.03.19.
//

#include "mpi.h"
#include <stdio.h>
#include <math.h>
double f( double a );

double f( double a )
 Функция интеграла

{
    return (4.0 / (1.0 + a*a));
}

int main( int argc, char *argv[])
{
 Объявление переменных:
- флаг окончания вычислений
- параметр погрешности вычисления
- порядковый номер задачи
- общее количество задач
- параметр цикла


    int done = 0, n, myid, numprocs, i;

 Эталонное значение П

    double PI25DT = 3.141592653589793238462643;

- текущее значение П
- эталонное значение П
- шаг интеграла
- сумма при вычислении интеграла
- текущий аргумент подынтегральной функции


    double mypi, pi, h, sum, x;

- начальное и конечное время вычисления интеграла


    double startwtime = 0.0, endwtime;

 Инициализация библиотеки

    MPI_Init(&argc,&argv);
 Получаем общее количество запущенных процессов

    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
 Получаем порядковый номер текущего процесса

    MPI_Comm_rank(MPI_COMM_WORLD,&myid);

    n = 0;
    while (!done)
    {
        if (myid == 0)    {
            if (n==0) n=100; else n=0;
 Засекаем время начала вычисления

            startwtime = MPI_Wtime();
        }
 Рассылаем содержимое буфера задачи во все остальные

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)  done = 1;
        else {
            h   = 1.0 / (double) n;
            sum = 0.0;
            for (i = myid + 1; i <= n; i += numprocs)
            {
                x = h * ((double)i - 0.5);     sum += f(x);
            }
            mypi = h * sum;
 Массив с результатами размещается в данной задаче

            MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            if (myid == 0)    {
                printf("pi is approximately %.16f, Error is %.16f\n",
                       pi, fabs(pi - PI25DT));
                endwtime = MPI_Wtime();
Засекаем время окончания вычисления

 Вывод общего времени вычисления

                printf("wall clock time = %f\n", endwtime-startwtime);
            }
        }
    }
    MPI_Finalize();
 Нормальное закрытие библиотеки

    return 0;
}
