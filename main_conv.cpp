#include "parameters.h"
#include "Thermal/thermal.cpp"
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

int fib(int i) {
    int c1 = 0, c2 = 1, j = 0, k;
    while (j < i) {
        j++;
        k = c2;
        c2 += c1;
        c1 = k;
    }
    return c2;
}

int main() {
    double u[M][N];
    double t = 0e0;

    int k;
    int kk;
    int counter = 0;
#ifdef PIPES
    int fd;
    int fi;
    const char *myinpt = PIPE_PARAMS;
    const char *myfifo = PIPE_DATA;
    char buffer_data[6*N+10];
    char buffer_params[12];

    while (fib(counter) <= ITERS) counter++;

    mkfifo(myinpt, 0666);
    fi = open(myinpt, O_WRONLY);

    snprintf(buffer_params, 6, "%5d", counter);
    snprintf(buffer_params+6, 6, "%5d", N);
    write(fi, buffer_params, 12);
    close(fi);

    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_WRONLY);
#endif

    counter = 1;

    for (int i = 0; i < N; i++) u[0][i] = T_INIT;

    for (int i = 0; i < ITERS - 1; i++) {
        k = i % M;
        kk = (i+1) % M;
        t += DT;

        thermal_1d::bc_q1_q2_1d(N, u[k]);
        thermal_1d::dt_cond_conv_1d(N, u[k], t, u[kk]);
        for (int j = 0; j < N; j++) u[kk][j] = u[k][j] + DT * u[kk][j];
        thermal_1d::bc_q1_q2_1d(N, u[kk]);

        fflush(stdout);

#ifdef PIPES
        if (i >= fib(counter)) {
            snprintf(buffer_data, 11, "%10f", t);
            for (int j = 0; j < N; j++) snprintf(buffer_data+6*j+10, 6*N, "%6f", u[kk][j]);
            write(fd, buffer_data, 6*N+10);
            counter ++;
        }
#endif
    }
#ifdef PIPES
    close(fd);
#endif
    return 0;
}
