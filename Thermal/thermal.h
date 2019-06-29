//
// Created by imanol on 27/06/19.
//

#ifndef THERMAL_THERMAL_H
#define THERMAL_THERMAL_H

namespace thermal_data {
    /** \brief Al density [kg/m^3].*/
    const double RHO = 27e2;
    /** \brief Al specific heat [J/(K m)].*/
    const double C = 896e0;
    /** \brief Al Honeycomb equivalent conductivity on X axis [W/(K m)].*/
    const double KX = 60.63e0;
    /** \brief Al Honeycomb equivalent conductivity on Y axis [W/(K m)].*/
    const double KY = 60.24e0;
    /** \brief Air equivalent convectivity [W/(m^2 K)].*/
    const double H = 1e1;
    /** \brief X-Axis Transversal Surface [m^2].*/
    const double AX = 3e-3;
    /** \brief Y-Axis Transversal Surface [m^2].*/
    const double AY = 1.188e-3;
    /** \brief Z-Axis Transversal Surface [m^2].*/
    const double AZ = 99e-3;
    /** \brief Perimeter exposed to to air [m].*/
    const double P = 5e-1;
    /** \brief Environment temperature [K].*/
    const double T_INF = 298e0;
    /** \brief X-Axis length [m].*/
    const double LX = 198e-3;
    /** \brief Y-Axis length [m].*/
    const double LY = 500e-3;
    /** \brief Z-Axis length [m].*/
    const double LZ = 6e-3;
    /** \brief Exiting heat on leftmost node [W].*/
    const double Q1 = -35e0;
    /** \brief Exiting heat on rightmost node [W].*/
    const double Q2 = 0e0;
    /** \var Temperature at East wall [K]. */
    const double TE = 298e0;
    /** \var Temperature at North wall [K]. */
    const double TN = 256e0;
    /** \var Temperature at West wall [K]. */
    const double TW = 298e0;
    /** \var Temperature at South wall [K]. */
    const double TS = 256e0;
}

namespace thermal_1d {
    /**
     * Differential Operator for 1D thermal conductivity problem.
     * @tparam T type of the state vector.
     * @param N number of nodes / state vector.
     * @param u N-sized state vector.
     * @param t current state time (not used,but required for common IF).
     * @param f N-sized array. Contains the derivative of the problem.
     */
    template <class T>
    void dt_cond_1d(int N, T *u, T t, T *f);

    /**
     * Differential Operator for 1D thermal conductivity and convectivity problem.
     * @tparam T type of the state vector.
     * @param N number of nodes / state vector.
     * @param u N-sized state vector.
     * @param t current state time (not used,but required for common IF).
     * @param f N-sized array. Contains the derivative of the problem.
     */
    template <class T>
    void dt_cond_conv_1d(int N, T *u, T t, T *f);

    /**
     * Set Boundary Conditions: Q1 on u[0] and Q2 on u[N-1]
     * @tparam T type of the state vector.
     * @param N number of nodes / state vector.
     * @param u N-sized state vector.
     */
    template <class T>
    void bc_q1_q2_1d(int N, T *u);

}

namespace thermal_2d {
     /**
      * Differential Operator for 2D thermal conductivity problem.
      * @tparam T type of the state vector.
      * @tparam N number of nodes on X-axis/ rows of state matrix.
      * @tparam M number of nodes on Y-axis/ columns of state matrix.
      * @param u N by M sized state matrix.
      * @param t current state time (not used,but required for common IF).
      * @param f N by M sized matrix. Contains the derivative of the problem.
      */
     template <class T>
     void dt_cond_2d(int N, int M, T *u, T t, T *f);

    /**
     * Differential Operator for 2D thermal conductivity and convectivity problem.
     * @tparam T type of the state vector.
     * @param N number of nodes on X-axis/ rows of state matrix.
     * @param M number of nodes on Y-axis/ columns of state matrix.
     * @param u N by M sized state matrix.
     * @param t current state time (not used,but required for common IF).
     * @param f N by M sized matrix. Contains the derivative of the problem.
     */
    template <class T>
    void dt_cond_conv_1d(int N, T *u, T t, T *f);

    /**
     * Set Boundary Conditions: Q1 on u[0] and Q2 on u[N-1]
     * @tparam T type of the state vector.
     * @param N number of nodes / state vector.
     * @param u N-sized state vector.
     */
    template <class T>
    void bc_q1_q2_2d(int N, T *u);

     /**
      * Set Boundary Conditions: TE at East, TN at North, TW at West and TS at South.
      * @tparam T type of the state vector.
      * @tparam N number of nodes on X-axis/ rows of state matrix.
      * @tparam M number of nodes on Y-axis/ columns of state matrix.
      * @param u N by M sized state matrix.
      */
    template <class T>
    void bc_te_tn_tw_ts_2d(int N, int M, T *u);

}

#endif //THERMAL_THERMAL_H