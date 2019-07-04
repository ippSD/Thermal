//
// Created by imanol on 27/06/19.
//

#ifndef THERMAL_THERMAL_DATA_H
#define THERMAL_THERMAL_DATA_H

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

#endif //THERMAL_THERMAL_DATA_H