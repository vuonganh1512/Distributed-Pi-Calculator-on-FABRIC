#include <stdio.h>
#include <math.h>
#include "utils.h"

double abs_error(double estimate) {
    const double pi_ref = 3.14159265358979323846;
    return fabs(estimate - pi_ref);
}

void print_usage(const char *progname) {
    fprintf(stderr, "Usage: %s <num_intervals>\n", progname);
}
