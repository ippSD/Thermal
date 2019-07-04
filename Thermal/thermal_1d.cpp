//
// Created by imanol on 27/06/19.
//

#include "thermal_data.h"
#include "thermal_1d.h"
using namespace thermal_data;

void thermal_1d::dt_cond(int N, double *u, double t, double *f) {
    // Operador Diferencial del problema conductivo.
    f[0] = 0e0;
    f[N-1] = 0e0;
    for (int j = 1; j < N - 1; j++) f[j] = u[j-1] - 2e0*u[j] + u[j+1];
}

void thermal_1d::dt_cond_conv(int N, double *u, double t, double *f) {
    // Differential Operator for 1D thermal conductivity and convectivity problem.
    for (int j = 0; j < N; j++) f[j] = (u[j-1] - 2e0*u[j] + u[j+1]) / (LX * LX / N / N) * AX *KX;
    for (int j = 0; j < N; j++) f[j] -= H * P * (u[j] - T_INF);
    for (int j = 0; j < N; j++) f[j] /= AX * RHO * C;
}

void thermal_1d::bc_q1_q2(int N, double *u) {
    // Set Boundary Conditions: Q1 on u[0] and Q2 on u[N-1]
    u[0]   = u[1]   - Q1 * LX / N / AX / KX;
    u[N-1] = u[N-2] - Q2 * LX / N / AX / KX;
}
