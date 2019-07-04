#include "parameters.h"
#include <thermal_1d.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

int main() {
    double u[M][N];

    int k;
    int kk;
#ifdef PIPES
    int fd;
    int fi;
    const char *myinpt = PIPE_PARAMS;
    const char *myfifo = PIPE_DATA;
    char buffer_data[6*N];
    char buffer_params[12];

    mkfifo(myinpt, 0666);
    fi = open(myinpt, O_WRONLY);

    snprintf(buffer_params, 6, "%5d", int(ITERS/STEPS));
    snprintf(buffer_params+6, 6, "%5d", N);
    write(fi, buffer_params, 12);
    close(fi);

    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_WRONLY);
#endif

    for (int i = 0; i < N; i++) u[0][i] = 1e0;
    u[0][0] = T_0;
    u[0][N-1] = T_F;

    for (int i = 0; i < ITERS - 1; i++) {
        k = i % M;
        kk = (i+1) % M;

        u[kk][0] = T_0;
        u[kk][N-1] = T_F;
        thermal_1d::dt_cond(N, u[k], 0e0, u[kk]);
        for (int j = 0; j < N; j++) u[kk][j] = u[k][j] + CFL * (u[kk][j]);

        fflush(stdout);

#ifdef PIPES
        if (! (i % STEPS)) {
            for (int j = 0; j < N; j++) snprintf(buffer_data+6*j, 6*N, "%5.4f", u[kk][j]);
            write(fd, buffer_data, 6*N);
        }
#endif
    }
#ifdef PIPES
    close(fd);
#endif
    return 0;
}
