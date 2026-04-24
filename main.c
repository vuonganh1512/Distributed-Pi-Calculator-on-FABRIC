#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "pi_algorithms.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    int rank, size;
    long long N;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            fprintf(stderr, "Error: missing required argument.\n");
            print_usage(argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    N = atoll(argv[1]);
    if (N <= 0) {
        if (rank == 0) {
            fprintf(stderr, "Error: number of intervals must be positive.\n");
            print_usage(argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    long long chunk = N / size;
    long long remainder = N % size;

    long long start, end;

    if (rank < remainder) {
        start = rank * (chunk + 1);
        end = start + (chunk + 1);
    } else {
        start = rank * chunk + remainder;
        end = start + chunk;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    double t0 = MPI_Wtime();

    double local_pi = pi_integral_partial(start, end, N);
    double global_pi = 0.0;

    MPI_Reduce(&local_pi, &global_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double t1 = MPI_Wtime();

    if (rank == 0) {
        printf("Algorithm: numerical_integration\n");
        printf("Processes: %d\n", size);
        printf("Intervals: %lld\n", N);
        printf("Estimated Pi: %.12f\n", global_pi);
        printf("Absolute Error: %.12e\n", abs_error(global_pi));
        printf("Runtime (s): %.6f\n", t1 - t0);
    }

    MPI_Finalize();
    return 0;
}
