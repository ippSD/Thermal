#include "parameters.h"
#include "Thermal/thermal.cpp"
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>

int main() {
    double u[M][NX*NY];
    double t = 0e0;

    int k;
    int kk;
#ifdef PIPES
    int fd;
    int fi;
    const char *myinpt = PIPE_PARAMS;
    const char *myfifo = PIPE_DATA;
    char buffer_data[6*N+10];
    char buffer_params[18];

    mkfifo(myinpt, 0666);
    fi = open(myinpt, O_WRONLY);

    snprintf(buffer_params, 6, "%5d", int(ITERS/STEPS));
    snprintf(buffer_params+6, 6, "%5d", NX);
    snprintf(buffer_params+12, 6, "%5d", NY);
    write(fi, buffer_params, 18);
    close(fi);

    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_WRONLY);
#endif

    for (int i = 0; i < NX*NY; i++) u[0][i] = 300e0;

    for (int i = 0; i < ITERS - 1; i++) {
        k = i % M;
        kk = (i+1) % M;
        t += DT;

        thermal_2d::bc_te_tn_tw_ts_2d(NX, NY, u[k]);
        thermal_2d::dt_cond_2d(NX, NY, u[k], t, u[kk]);
        for (int j = 0; j < NX*NY; j++) u[kk][j] = u[k][j] + DT * u[kk][j];
        thermal_2d::bc_te_tn_tw_ts_2d(NX, NY, u[kk]);

        fflush(stdout);

#ifdef PIPES
        if (! (i % STEPS)) {
            snprintf(buffer_data, 11, "%10f", t);
            for (int j = 0; j < NX*NY; j++) snprintf(buffer_data+6*j+10, 6*NX*NY, "%6f", u[kk][j]);
            write(fd, buffer_data, 6*NX*NY+10);
        }
#endif
    }
#ifdef PIPES
    close(fd);
#endif
    return 0;
}
