#include <iostream>
#include <iomanip>
#include <mpi.h>

const int N = 5;
const int M = 7;

template<class T>
void quick_sort_r(T* vector, long N) {
    long i = 0, j = N;
    T temp, p;
    p = vector[N >> 1];
    do {
        while (vector[i] < p)
            ++i;
        while (vector[j] > p)
            --j;

        if (i <= j) {
            temp = vector[i];
            vector[i] = vector[j];
            vector[j] = temp;
            ++i;
            --j;
        }
    } while (i <= j);

    if (j > 0)
        quick_sort_r(vector, j);
    if (N > i)
        quick_sort_r(vector + i, N - i);
}

void print_vector(int **vector, int M, int N){
    for (auto i = 0; i < M; ++i){
        for (auto j = 0; j < N; ++j)
            std::cout << std::setw(5) << vector[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int **allocate(int M, int N){
    int **vector;
    vector = new int * [M];
    vector[0] = new int[N * M];
    for (auto i = 1; i < M; ++i)
        vector[i] = vector[i - 1] + N;
    return vector;
}

void fill_vector(int **vector, int M, int N){
    srand((unsigned int)time(nullptr));
    for (auto i = 0; i < M; ++i)
        for (auto j = 0; j < N; ++j)
            vector[i][j] = 0 + rand() % 1000;
}

int main(int argc, char **argv) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int **vector = allocate(M, N);
    int *buf, *buf1;

    if (rank == 0){
        fill_vector(vector, M, N);
        print_vector(vector, M, N);
    }

    if (M / size > 0) {
        buf = new int[(M / size) * N];
        MPI_Scatter(*vector, (M / size) * N, MPI_INT, buf, (M / size) * N, MPI_INT, 0, MPI_COMM_WORLD);
        for (int i = 0; i < (M / size); ++i)
            quick_sort_r( (buf + i * N), N - 1);
        MPI_Gather(buf, ((M / size) * N), MPI_INT, *vector, ((M / size) * N), MPI_INT, 0, MPI_COMM_WORLD);
        delete[] buf;
    }

    if (M % size > 0) {
        buf = new int[N];
        MPI_Scatter(*vector + ((M - M % size) * N), N, MPI_INT, buf, N, MPI_INT, 0, MPI_COMM_WORLD);
        quick_sort_r((buf), N - 1);

        buf1 = new int[size * N];

        MPI_Gather(buf, N, MPI_INT, buf1, N, MPI_INT, 0, MPI_COMM_WORLD);
        for (int i = 0; i < M % size; ++i)
            for (int j = 0; j < N; ++j)
                if((M / size) > 0)
                    vector[((M / size) * size) + i][j] = buf1[i * N + j];
                else
                    vector[i][j] = buf1[i * N + j];

        delete[] buf1;
        delete[] buf;
    }

    if (rank == 0)
        print_vector(vector, M, N);

    delete[] vector;

    MPI_Finalize();
    return 0;
}