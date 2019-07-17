/*
18.  В векторе элементами являются или числа, или строки символов. Если встретилось число - вернуть строку символов такой длины, если встретилась строка символов - вернуть ее длину. Результат вывести на экран.
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define SIZE 10
#define SEND_TO_CHECK 0
#define SEND_TO_PRINT_CHAR 1
#define SEND_TO_PRINT_INT 2

int main(int argc, char** argv){
    srand((unsigned int)time(NULL));
    int my_rank, size, count;
    char data[SIZE];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (size != 2){
        if (my_rank == 0)
            printf("Error: two processes required instead of %d, abort\n", size );

        MPI_Barrier( MPI_COMM_WORLD );
        MPI_Abort(MPI_COMM_WORLD, MPI_ERR_OTHER );
        return -1;
    }

    if (my_rank == 0){
        for (size_t i = 0; i < 10; ++i)
            data[i] = 53 + rand() % 37;

        printf("Source string:\n%s\n", data);
        MPI_Send(&data, SIZE, MPI_CHAR, 1, SEND_TO_CHECK, MPI_COMM_WORLD);

        for (size_t i = 0; i < 10; ++i)
            data[i] = 0;

        MPI_Probe(1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == SEND_TO_PRINT_CHAR){
            MPI_Get_count(&status, MPI_CHAR, &count);
            MPI_Recv(data, count, MPI_CHAR, 1, SEND_TO_PRINT_CHAR, MPI_COMM_WORLD, &status);
            printf("\nProcessed string:\n%s\n", data);
        }
        else if (status.MPI_TAG == SEND_TO_PRINT_INT){
            int len;
            MPI_Get_count(&status, MPI_INT, &count);
            MPI_Recv(&len, count, MPI_INT, 1, SEND_TO_PRINT_INT, MPI_COMM_WORLD, &status);
            printf("\nString lenght: %d\n", len);
        }
    }
    else{
        MPI_Recv(&data, SIZE, MPI_CHAR, 0, SEND_TO_CHECK, MPI_COMM_WORLD, &status);
        for (size_t i = 0; i < SIZE; ++i){
            for (size_t j = 48; j < 58; ++j){
                if ((data[i]) == j){
                    MPI_Send(&data, j - 48, MPI_CHAR, 0, SEND_TO_PRINT_CHAR, MPI_COMM_WORLD);
                    MPI_Finalize();
                    return;
                }
            }
        }
        int len = strlen(data);
        MPI_Send(&len, 1, MPI_INT, 0, SEND_TO_PRINT_INT, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
