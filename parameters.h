//
// Created by imanol on 27/06/19.
//

#ifndef THERMAL_PARAMETERS_H
#define THERMAL_PARAMETERS_H
const int N = 20;
const int NX = 50;
const int NY = 50;
const int ITERS = 250000;
const int STEPS =  10000;
const int M = 2;
const double CFL = 5e-1;
const double DT = 0.0982049e0;
const double T_0 = 1e0;
const double T_F = 15e-2;
const double T_INIT = 298e0;
const char *PIPE_PARAMS = (char*) "/tmp/myinpt";
const char *PIPE_DATA = (char*) "/tmp/myfifo";
#define PIPES
#endif //THERMAL_PARAMETERS_H
