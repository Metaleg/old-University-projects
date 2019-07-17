/*
 * Вариант 18
 * Tasks:
 *  1.  Реализовать и распараллелить с помощью технологии OpenMP различные операции над векторами размерности N.
 *      N = 13, Целый байтовый, Определение максимального элемента.
 *
 *
 *  2.  Реализовать и распараллелить с помощью OpenMP различные алгоритмы.
 *      Размерность - 40х60, Целый байтовый, Сортировка столбцов матрицы по убыванию.
 *
 * g++ -fopenmp main.cpp -o main
 * */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <omp.h>
#include <ctime>

//#define lab4
#define lab5

int **allocate(int M, int N);
void fill_vector(int **vector, int M, int N);
void print_vector(int **vector, int M, int N);

int **allocate_mod(int threads, int N);
void fill_vector_mod(int **vector, int threads, int N);
void print_vector_mod(int **vector, int threads, int N);
void copy_vector_mod(int **src, int **dest, int N, int threads);

template<class T>void quick_sort_r(T* vector, long N);
void sort_vector(int **vector, int M, int N);


int **allocate(int M, int N){
    int **vector;
    vector = new int * [M];
    for (auto i = 0; i < M; ++i)
        vector[i] = new int[N];
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


int **allocate_mod(int threads, int N){
    int **vector;
    vector = new int * [threads];
    for (auto i = 0; i < threads; ++i)
        vector[i] = ((i == threads - 1) && ((N % threads) != 0)) ? new int[N / threads + (N % threads)] : new int[N / threads];
    return vector;
}

void fill_vector_mod(int **vector, int threads, int N){
    srand((unsigned int)time(nullptr));
    for (auto i = 0; i < threads; ++i){
        if ((i == threads - 1) && ((N % threads) != 0))
            for (auto j = 0; j < N / threads + (N % threads); ++j)
                vector[i][j] = 0 + rand() % 1000;
        else
            for (auto j = 0; j < N / threads; ++j)
                vector[i][j] = 0 + rand() % 1000;
    }
}

void print_vector_mod(int **vector, int threads, int N){
    for (auto i = 0; i < threads; ++i){
        if ((i == threads - 1) && ((N % threads) != 0))
            for (auto j = 0; j < N / threads + (N % threads); ++j)
                std::cout << std::setw(5) << vector[i][j];
        else
            for (auto j = 0; j < N / threads; ++j)
                std::cout << std::setw(5) << vector[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void copy_vector_mod(int **src, int **dest, int N, int threads){
    for (auto i = 0, k = 0; i < threads; ++i) {
        if ((i == threads - 1) && ((N % threads) != 0))
            for (auto j = 0; j < N / threads + (N % threads); ++j){
                dest[i][j] = src[0][k];
                ++k;
            }
        else
            for (auto j = 0; j < N / threads; ++j){
                dest[i][j] = src[0][k];
                ++k;
            }
        }
}


#ifdef lab4

const int N = 200000000;
const int chunk = 1;
const int threads = 4;

int main(){
    int **vector = allocate(1, N);
    fill_vector(vector, 1, N);
//    print_vector(vector, 1, N);

    int **temp_vector = allocate_mod(threads, N);
    copy_vector_mod(vector, temp_vector, N, threads);
//    print_vector_mod(temp_vector, threads, N);

    auto i = 0, j = 0;
    int **max = allocate(1, threads);

    auto start = omp_get_wtime();
#pragma omp parallel for shared(temp_vector, max) private(i, j) num_threads(threads) schedule(static, chunk)
    for (i = 0; i < threads; ++i) {
        max[0][i] = temp_vector[i][0];
        if (i == threads - 1) {
            for (j = 0; j < N / threads + (N % threads); ++j)
                if (temp_vector[i][j] > max[0][i])
                    max[0][i] = temp_vector[i][j];
        }
        else
            for (j = 0; j < N / threads; ++j)
                if (temp_vector[i][j] > max[0][i])
                    max[0][i] = temp_vector[i][j];
    }
    auto stop = omp_get_wtime();
    delete [] temp_vector;

    std::cout << "Local maximum: ";
    for (i = 0; i < threads; ++i)
        std::cout << std::setw(5) << max[0][i];
    std::cout << std::endl << "Time = " << stop - start << ", threads = " << threads << std::endl;

    auto abs_max = 0;
    for (i = 0; i < threads; ++i)
        if (max[0][i] > abs_max)
            abs_max = max[0][i];
    std::cout << "Absolute maximum = " << abs_max << std::endl;

    delete [] vector;
    delete [] max;

    return 0;
}
#endif


#ifdef lab5

const int M = 4;
const int N = 6;
const int chunk = 5;
const int threads = 1;


template<class T>
void quick_sort_r(T* vector, long N) {
    long i = 0, j = N;
    T temp, p;
    p = vector[N >> 1];
    do {
        while (vector[i] > p)
            ++i;
        while (vector[j] < p)
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



void sort_vector(int **vector, int M, int N){
    int **temp_vector;
    auto i = 0, j = 0;

    auto start = omp_get_wtime();
#pragma  omp parallel shared(vector, M, N) private(i, j, temp_vector) num_threads(threads)
    {
        temp_vector = allocate(1, M);
#pragma omp for schedule(static, chunk) nowait
        for (i = 0; i < N; ++i) {
            for (j = 0; j < M; ++j)
                temp_vector[0][j] = vector[j][i];

            quick_sort_r(temp_vector[0], M - 1);

            for (j = 0; j < M; ++j)
                vector[j][i] = temp_vector[0][j];
        }
        delete[] temp_vector;
    }
    auto stop = omp_get_wtime();

    std::cout << std::endl << "time = " << stop - start << " process " << omp_get_num_threads() << std::endl;
}


int main(){

    int **vector = allocate(M, N);
    fill_vector(vector, M, N);
    print_vector(vector, M, N);

    sort_vector(vector, M, N);
    print_vector(vector, M, N);

    delete[] vector;

    return 0;
}

#endif
