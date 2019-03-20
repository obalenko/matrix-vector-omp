#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "math.h"

/*****************************************************
 ****************************************************/
void matrix_gen(int size, double **matrix){
    for (int count = 0; count < size; count++) {
        matrix[count] = (double*)malloc(sizeof(double)*size*size);
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = sin(i) + cos(i);
        }
    }
}

void vector_gen(int size, double *vector){
    int i;
    for(i=0; i<size; i++)
        vector[i] = sin(i)*cos(i);
}

/****************************************************
 ***************************************************/
void matrix_mult_sq(int size, double **matrix1_in,
                    double *matrix2_in){
    double *Res = new double[size];
    for (int i = 0; i < size; i++) {
        Res[i] = 0;
        for (int j = 0; j < size; j++) {
            Res[i] += matrix1_in[i][j] * matrix2_in[j];
        }
    }
}

/****************************************************
 ***************************************************/
void matrix_mult_pl(int size, double **matrix1_in,
                    double *matrix2_in){
    double time_pl;
    int num_threads = 0;
    double *Res = new double[size];
    #pragma omp parallel num_threads(2)
    {
        time_pl = omp_get_wtime();
        #pragma omp for

        for (int i = 0; i < size; i++) {
            Res[i] = 0;
            for (int j = 0; j < size; j++) {
                Res [i] += matrix1_in[i][j] * matrix2_in[j];
            }
        }
        num_threads = omp_get_num_threads();
    }
    time_pl = omp_get_wtime() - time_pl;
    printf("PARALLEL EXECUTION WITH %d (threads) ON %d (processors): %f (sec)\n",
           num_threads, omp_get_num_procs(), time_pl);
}


int main(){
    int size = 6000;

    double **matrix1 = (double **)malloc(sizeof(double)*size*size);
    double *matrix2 = (double *)malloc(sizeof(double)*size*size);

    matrix_gen(size, matrix1);
    vector_gen(size, matrix2);

    double time_sq = 0;

    time_sq = omp_get_wtime();
    matrix_mult_sq(size, matrix1, matrix2);
    time_sq = omp_get_wtime() - time_sq;

    printf("SEQUENTIAL EXECUTION: %f (sec)\n", time_sq);

    matrix_mult_pl(size, matrix1, matrix2);


    free(matrix1);
    free(matrix2);
    return 1;
}