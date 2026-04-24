#include "pi_algorithms.h"

double pi_integral_partial(long long start, long long end, long long N) {
    double h = 1.0 / (double)N;
    double sum = 0.0;

    for (long long i = start; i < end; i++) {
        double x = h * ((double)i + 0.5);
        sum += 4.0 / (1.0 + x * x);
    }

    return sum * h;
}
