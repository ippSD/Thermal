//
// Created by imanol on 27/06/19.
//

#include "thermal_data.h"
#include "thermal_2d.h"
using namespace thermal_data;

void thermal_2d::dt_cond(int N, int M, double *u, double t, double *f) {
    // 2D Thermal Conductivity Differential Operator.
    double *pu[N][M];
    double *pf[N][M];
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) pu[i][j] = &u[i*M+j];
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) pf[i][j] = &f[i*M+j];
    double delta_x = LX / N;
    double delta_y = LY / M;
    double delta_v = delta_x * delta_y * LZ;
    for (int i = 0; i < N; i = i + N - 1) {
        for (int j = 0; j < M; j = j + M - 1) {
            *pf[i][j] = 0e0;
        }
    }
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < M - 1; j++) {
            *pf[i][j]  = (*pu[i-1][j] - 2e0 * *pu[i][j] + *pu[i+1][j]) / (delta_x * delta_x) * delta_v * KX;
            *pf[i][j] += (*pu[i][j-1] - 2e0 * *pu[i][j] + *pu[i][j+1]) / (delta_y * delta_y) * delta_v * KY;
        }
    }
}

void thermal_2d::bc_te_tn_tw_ts(int N,int M, double *u) {
    double *pu[N][M];
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) pu[i][j] = &u[i*M+j];
    for (int i = 0; i < N; i++) *pu[i][M-1] = TE;
    for (int j = 0; j < M; j++) *pu[0][j] = TN;
    for (int i = 0; i < N; i++) *pu[i][0] = TW;
    for (int j = 0; j < M; j++) *pu[N-1][j] = TS;

    *pu[0][0]     = 5e-1 * (TN + TW);
    *pu[0][M-1]   = 5e-1 * (TN + TE);
    *pu[N-1][0]   = 5e-1 * (TS + TW);
    *pu[N-1][M-1] = 5e-1 * (TS + TE);
}