//
// Created by imanol on 27/06/19.
//

#ifndef EXPORT
#define EXPORT __attribute__((visibility("default")))
#endif

#ifndef THERMAL_THERMAL_2D_H
#define THERMAL_THERMAL_2D_H


namespace thermal_2d {
     /**
      * Differential Operator for 2D thermal conductivity problem.
      * @param N number of nodes on X-axis.
      * @param M number of nodes on Y-axis.
      * @param u NxM sized state vector.
      * @param t current state time (not used,but required for common IF).
      * @param f NxM sized vector. Contains the derivative of the problem.
      */
     void dt_cond(int N, int M, double *u, double t, double *f);

    /**
     * Set Boundary Conditions on Temperature: TS, TE, TN and TW at South, East, North and West walls.
     * @param N number of nodes along X-axis.
     * @param M number of nodes along Y-axis.
     * @param u NxM-sized state vector.
     */

    void bc_te_tn_tw_ts(int N, int M, double *u);

}

#endif //THERMAL_THERMAL_2D_H