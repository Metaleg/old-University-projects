/*
 * Вариант 18
 * Tasks:
 * 1    Переслать вектор, размерности M, N процессам, используя различные виды связи между процессами.
 *      Элементы вектора задаются произвольно. Элементы вектора пересылаемого и принятого вектора,
 *      а также время выполнения должны быть выведены на экран.
 *      M = 15, N = 5, MPI_Bcast
 *
 *
 *  2   Сгенерировать в каждом из N процессов вектор чисел. Размерность вектора – М.
 *      Произвести поэлементную обработку всех векторов и поместить результирующий вектор в каком-либо процессе.
 *      В работе использовать средства MPI для организации распределенных вычислений.
 *      N = 5, M = 50, Целый байтовый, Поэлементное умножение.
 *
 *
 *  3   Произвести сортировку элементов в столбцах (или строках) матрицы размерности MxN,
 *      с использованием распределения вычислений между процессами средствами MPI.
 *      N = 4, M = 5, Целый байтовый, по возрастанию.
 * */
//#define lab1
//#define lab2
#define lab3


#include <iostream>
#include <iomanip>
#include <mpi.h>
#include <cstdlib>
#include <thread>


#ifdef lab1

const int M = 15;
const int src = 0;

int main(int argc, char **argv){
    srand((unsigned int)time(nullptr));
    MPI_Init(&argc, &argv);
    int my_rank, size;
    char *vector;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    std::cout << "My rank = " << my_rank << ", My vector = ";
    if (my_rank == src){
        vector = new char[M];
        for (auto i = 0; i < M; ++i){
            vector[i] = static_cast<char>(53 + rand() % 37);
            std::cout << vector[i];
        }
        std::cout << std::endl;
        MPI_Bcast(vector, M, MPI_CHAR, src, MPI_COMM_WORLD);
        delete[] vector;
    }
    else{
        vector = new char[M];
        for (auto i = 0; i < M; ++i)
            std::cout << vector[i];
        std::cout << std::endl;
        MPI_Bcast(vector, M, MPI_CHAR, src, MPI_COMM_WORLD);
        for (auto i = 0; i < M; ++i)
            std::cout << vector[i];
        std::cout << std::endl;
        delete[] vector;
    }

    MPI_Finalize();

    return 0;
}

#endif



#ifdef lab2

const int M = 15;
const int src = 0;

int main(int argc, char **argv){
    srand((unsigned int)time(nullptr));
    MPI_Init(&argc, &argv);
    int my_rank, size;
    int *vector = nullptr;
    int *res_vector = nullptr;
    res_vector = new int[M];

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    std::cout << "My rank = " << my_rank << ", My vector = ";

    vector = new int[M];
    for (auto i = 0; i < M; ++i){
        vector[i] = ((0 + rand() % 9) + my_rank);
        std::cout << std::setw(6) << vector[i];
    }
    std::cout << std::endl;
    MPI_Reduce(vector, res_vector, M, MPI_INT, MPI_PROD, src, MPI_COMM_WORLD);
    delete[] vector;

    if (my_rank == 0) {
        std::cout << "\t Result vector = ";
        for (auto i = 0; i < M; ++i)
            std::cout << std::setw(6) << res_vector[i];
        std::cout << std::endl;
    }

    delete[] res_vector;
    MPI_Finalize();

    return 0;
}

#endif

#ifdef lab3

int **allocate(int M, int N);
void fill_vector(int **vector, int M, int N);
void print_vector(int **vector, int M, int N);
template<class T>void quick_sort_r(T* vector, long N);


int **allocate(int M, int N){
    int **vector;
    vector = new int * [M];
        vector[0] = new int[N * M];
    for (auto i = 1; i < M; ++i)
        vector[i] = vector[i - 1] + N;
//    for (auto i = 0; i < M; ++i)
//        vector[i] = new int[N];
    return vector;
}

void fill_vector(int **vector, int M, int N){
    srand((unsigned int)time(nullptr));
    for (auto i = 0; i < M; ++i)
        for (auto j = 0; j < N; ++j)
            vector[i][j] = 0 + rand() % 1000;
}

void print_vector(int **vector, int M, int N){
    for (auto i = 0; i < M; ++i){
        for (auto j = 0; j < N; ++j)
            std::cout << std::setw(5) << vector[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


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


const int N = 5;
const int M = 7;


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

#endif