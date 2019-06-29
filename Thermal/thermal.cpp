//
// Created by imanol on 27/06/19.
//

#include <cstddef>
#include "thermal.h"
using namespace thermal_data;

template <class T>
void thermal_1d::dt_cond_1d(int N, T *u, T t, T *f) {
    // Operador Diferencial del problema conductivo.
    f[0] = (T) 0e0;
    f[N-1] = (T) 0e0;
    for (int j = 1; j < N - 1; j++) f[j] = (T) (u[j-1] - 2e0*u[j] + u[j+1]);
}

template <class T>
void thermal_1d::dt_cond_conv_1d(int N, T *u, T t, T *f) {
    // Differential Operator for 1D thermal conductivity and convectivity problem.
    for (int j = 0; j < N; j++) f[j] = (T) ((u[j-1] - 2e0*u[j] + u[j+1]) / (LX * LX / N / N) * AX *KX);
    for (int j = 0; j < N; j++) f[j] -= (T) (H * P * (u[j] - T_INF));
    for (int j = 0; j < N; j++) f[j] /= (T) (AX * RHO * C);
}

template <class T>
void thermal_1d::bc_q1_q2_1d(int N, T *u) {
    // Set Boundary Conditions: Q1 on u[0] and Q2 on u[N-1]
    u[0]   = u[1]   - Q1 * LX / N / AX / KX;
    u[N-1] = u[N-2] - Q2 * LX / N / AX / KX;
}

template <class T>
void thermal_2d::dt_cond_2d(int N, int M, T *u, T t, T *f) {
    // 2D Thermal Conductivity Differential Operator.
    T *pu[N][M];
    T *pf[N][M];
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

template <class T>
void thermal_2d::bc_te_tn_tw_ts_2d(int N,int M, T *u) {
    T *pu[N][M];
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