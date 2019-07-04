//
// Created by imanol on 27/06/19.
//

/*#if defined(_MSC_VER)
    //  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC*/
#define EXPORT __attribute__((visibility("default")))
//#define IMPORT
/*#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif*/

#ifndef THERMAL_THERMAL_1D_H
#define THERMAL_THERMAL_1D_H

namespace thermal_1d{
    /**
    * Differential Operator for 1D thermal conductivity problem.
    * @param N number of nodes / state vector.
    * @param u N-sized state vector.
    * @param t current state time (not used,but required for common IF).
    * @param f N-sized array. Contains the derivative of the problem.
    */
    EXPORT void dt_cond(int N, double *u, double t, double *f);

    /**
     * Differential Operator for 1D thermal conductivity and convectivity problem.
     * @param N number of nodes / state vector.
     * @param u N-sized state vector.
     * @param t current state time (not used,but required for common IF).
     * @param f N-sized array. Contains the derivative of the problem.
     */
    EXPORT void dt_cond_conv(int N, double *u, double t, double *f);

    /**
     * Set Boundary Conditions: Q1 on u[0] and Q2 on u[N-1]
     * @param N number of nodes / state vector.
     * @param u N-sized state vector.
     */
    EXPORT void bc_q1_q2(int N, double *u);
}



#endif //THERMAL_THERMAL_1D_H